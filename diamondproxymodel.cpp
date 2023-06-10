#include "diamondproxymodel.h"

#include <iostream>

#include "diamondstable.h"

DiamondSortFilterProxyModel::DiamondSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

int DiamondSortFilterProxyModel::encodeStringCell(
    const QModelIndex &cell) const {
    QVariant data = sourceModel()->data(cell);

    if (cell.column() == 2)
        return Diamond::cutList.indexOf(data);
    else if (cell.column() == 4)
        return Diamond::clarityList.indexOf(data);

    return -1;
}

void DiamondSortFilterProxyModel::setFilter(double fromFilter,
                                            double toFilter) {
    from = fromFilter;
    to = toFilter;
}

bool DiamondSortFilterProxyModel::lessThan(const QModelIndex &left,
                                           const QModelIndex &right) const {
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    int column = left.column();
    if (left.column() == 2 || left.column() == 4)
        return encodeStringCell(left) < encodeStringCell(right);

    if (left.column() == 3)
        return leftData.toChar().unicode() < rightData.toChar().unicode();

    if (left.column() == right.column())
        return leftData.toDouble() < rightData.toDouble();

    return false;
}

bool DiamondSortFilterProxyModel ::filterAcceptsRow(
    int sourceRow, const QModelIndex &sourceParent) const {
    QModelIndex indexPrice = sourceModel()->index(sourceRow, 5, sourceParent);

    return indexPrice.data().toDouble() >= from &&
           indexPrice.data().toDouble() <= to;
}
