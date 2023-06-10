#include "chartview.h"

#include <QtCharts/QLegendMarker>
#include <QtCharts/QScatterSeries>
#include <QtCore/QtMath>
#include <QtGui/QImage>
#include <QtGui/QPainter>

ChartView::ChartView(QWidget *parent,
                     QMap<QChar, QList<QPair<size_t, double>>> *dataIn)
    : QChartView(new QChart(), parent) {
    data = dataIn;

    QList<QScatterSeries *> colorSeries;
    for (int i = 68; i <= 74; ++i) {
        QScatterSeries *series = new QScatterSeries();
        series->setName(QChar(i));
        series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        QColor color(255 - (i - 67) * 7, 255 - (i - 67) * 7, 0);
        series->setColor(color);
        series->setMarkerSize(12.0);
        for (const QPair<size_t, double> &pair : (*dataIn)[QChar(i)])
            series->append(pair.first, pair.second);
        colorSeries.push_back(series);
    }

    for (QScatterSeries *series : colorSeries) chart()->addSeries(series);

    chart()->setTitle("Graph");
    chart()->createDefaultAxes();
    chart()->setDropShadowEnabled(false);
}
