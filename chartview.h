#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>

class ChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ChartView(QWidget *parent = 0,
                       QMap<QChar, QList<QPair<size_t, double>>> *data = nullptr);

private:
    QMap<QChar, QList<QPair<size_t, double>>> *data;
};

#endif // CHARTVIEW_H
