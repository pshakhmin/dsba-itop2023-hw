#include "diamondstable.h"
#include <QFile>
#include <iostream>

DiamondsTable::DiamondsTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    _headers = {};
}

QVariant DiamondsTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    if (role == Qt::DisplayRole)
        if (orientation == Qt::Horizontal)
            if (section == 5)
                return _headers[7];
            else
                return _headers[section];

    return QVariant();
}

int DiamondsTable::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return _data.size();

    // FIXME: Implement me!
    return _data.size();
}

int DiamondsTable::columnCount(const QModelIndex &parent) const { return 6; }

QVariant DiamondsTable::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) return _data[index.row()][index.column()];

    return QVariant();
}

void DiamondsTable::readData(QString fp)
{
    QFile inputFile(fp);
    QTextStream inputStream(&inputFile);

    bool headerRow = false;
    inputFile.open(QFile::ReadOnly | QFile::Text);

    while (!inputStream.atEnd()) {
        QString line = inputStream.readLine();
        line = line.replace("\"", "");
        if (!headerRow) {
            _headers = line.split(",");
            headerRow = true;
        } else
            _data.append(Diamond{line});
    }
}

Diamond DiamondsTable::getDiamondByIndex(size_t index) {
    for (const Diamond &curDiamond : _data)
        if (curDiamond.index == index) return curDiamond;
    return Diamond();
}

void DiamondsTable::saveDiamond(const Diamond &diamond) {
    for (size_t i = 0; i < _data.size(); ++i)
        if (_data[i].index == diamond.index) _data[i] = diamond;
}

Diamond DiamondsTable::getAvgDiamond() {
    Diamond avg{};
    QMap<QString, size_t> cutMap;
    QMap<QChar, size_t> colorMap;
    QMap<QString, size_t> clarityMap;

    for (const QString &clarity : Diamond::clarityList) clarityMap[clarity] = 0;
    for (const QString &cut : Diamond::cutList) clarityMap[cut] = 0;
    for (int i = 68; i <= 74; ++i) colorMap[QChar(i)] = 0;

    for (const Diamond &curDiamond : _data) {
        avg.carat += curDiamond.carat;
        avg.price += curDiamond.price;
        cutMap[curDiamond.cut]++;
        clarityMap[curDiamond.clarity]++;
        colorMap[curDiamond.color]++;
    }

    avg.carat /= _data.size();
    avg.price /= _data.size();

    size_t maxCut = 0, maxColor = 0, maxClarity = 0;
    for (const QPair<QString, size_t> &curCut : cutMap.toStdMap())
        if (curCut.second > maxCut) {
            avg.cut = curCut.first;
            maxCut = curCut.second;
        }

    for (const QPair<QChar, size_t> &curColor : colorMap.toStdMap())
        if (curColor.second > maxColor) {
            avg.color = curColor.first;
            maxColor = curColor.second;
        }

    for (const QPair<QString, size_t> &curClarity : clarityMap.toStdMap())
        if (curClarity.second > maxClarity) {
            avg.clarity = curClarity.first;
            maxClarity = curClarity.second;
        }

    return avg;
}

void DiamondsTable::getDataForGraph(
    QMap<QChar, QList<QPair<size_t, double>>> *data) {
    for (const Diamond &curDiamond : _data) {
        if (!data->contains(curDiamond.color)) (*data)[curDiamond.color] = {};
        (*data)[curDiamond.color].push_back(
            {curDiamond.price, curDiamond.carat});
    }
}

bool DiamondsTable::removeRow(int index, const QModelIndex &modelIndex) {
    qInfo() << "removing" << index;
    beginRemoveRows(modelIndex, index, index + 1);
    for (size_t i = 0; i < _data.size(); ++i)
        if (_data[i].index == index) {
            _data.removeAt(i);
        }
    endRemoveRows();

    return true;
}

void DiamondsTable::saveAs(QString fp) {
    QFile file(fp);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        for (const QString header : _headers) {
            for (int i = 0; i < 10; ++i) stream << header << ',';
            stream << '\n';
        }

        for (const Diamond &diamond : _data) {
            for (int i = 0; i < 10; ++i) stream << diamond[i].toString() << ',';
            stream << '\n';
        }
    }
}

Diamond::Diamond(const QString &line) {
    QList<QString> items = line.split(',');
    for (QString &item : items) item = item.replace("\"", "");

    index = items[0].toULongLong();
    carat = items[1].toDouble();
    cut = items[2];

    if (!cutList.contains(cut))
        throw std::invalid_argument("Cut argument is invalid.");

    color = items[3][0];
    if ((color.unicode() < 68) || (color.unicode() > 74))
        throw std::invalid_argument("Color argument is invalid.");

    clarity = items[4];
    if (!clarityList.contains(clarity))
        throw std::invalid_argument("Clarity argument is invalid.");

    depth = items[5].toDouble();
    table = items[6].toDouble();
    price = items[7].toUInt();
    length = items[8].toDouble();
    width = items[9].toDouble();
}

Diamond::Diamond()
    : index(0),
      carat(0),
      cut("Fair"),
      color('D'),
      clarity("I3"),
      depth(0),
      table(0),
      price(0),
      length(0),
      width(0) {}

QVariant Diamond::operator[](size_t i) const {
    switch (i) {
        case 0:
            return QVariant::fromValue(index);
        case 1:
            return carat;
        case 2:
            return cut;
        case 3:
            return color;
        case 4:
            return clarity;
        case 5:
            return QVariant::fromValue(price);
        case 6:
            return depth;
        case 7:
            return table;
        case 8:
            return length;
        case 9:
            return width;
    }
    throw std::invalid_argument("Incorrect Diamond index.");
}
