#ifndef DIAMONDSTABLE_H
#define DIAMONDSTABLE_H

#include <QAbstractTableModel>

struct Diamond
{
    unsigned long index;
    double carat;
    QString cut;
    QChar color;
    QString clarity;
    unsigned long price;
    double depth;
    double table;
    double length;
    double width;

    Diamond(const QString &line);
    Diamond();

    QVariant operator[](size_t i) const;

    const inline static QStringList cutList{"Fair", "Good", "Very Good", "Premium", "Ideal"};
    const inline static QStringList
        clarityList{"I3", "I2", "I1", "SI2", "SI1", "VS2", "VS1", "VVS2", "VVS1", "IF", "FL"};
};

class DiamondsTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DiamondsTable(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void readData(QString fp = "");
    Diamond getDiamondByIndex(size_t index);
    void saveDiamond(const Diamond &diamond);
    Diamond getAvgDiamond();
    void getDataForGraph(QMap<QChar, QList<QPair<size_t, double>>> *data);
    void removeDiamondByIndex(size_t index, const QModelIndex &modelIndex);
    void addDiamond(const Diamond &diamond);
    int modelIndexByDiamondIndex(int diamondIndex);
    bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
    void saveAs(QString fp = "");

private:
    QList<Diamond> _data;
    QList<QString> _headers;
};

#endif // DIAMONDSTABLE_H
