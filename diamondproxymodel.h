#ifndef DIAMONDPROXYMODEL_H
#define DIAMONDPROXYMODEL_H

#include <QModelIndex>
#include <QSortFilterProxyModel>

class DiamondSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    DiamondSortFilterProxyModel(QObject *parent = nullptr);
    int encodeStringCell(const QModelIndex &cell) const;
    void setFilter(double from, double to);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    double from = 0;
    double to = 100000000;
};

#endif // DIAMONDPROXYMODEL_H
