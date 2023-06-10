#include "logowidget.h"

#include <QtGui>

LogoWidget::LogoWidget(QWidget* parent) : QWidget(parent) {}

LogoWidget::~LogoWidget() {}

void LogoWidget::paintEvent(QPaintEvent* event) {
    int hCenter = this->size().width() / 2;
    int vCenter = this->size().height() / 2;
    QPainter painter(this);

    size_t transX = hCenter - 50, transY = vCenter - 50;

    QPolygon poly;

    poly << QPoint(32, 62) << QPoint(57, 67) << QPoint(70, 31)
         << QPoint(45, 30);

    poly.translate(transX, transY);

    QBrush brush;
    brush.setColor(QColor(148, 242, 224));
    brush.setStyle(Qt::SolidPattern);
    QPen pen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawPolygon(poly);

    poly = QPolygon();
    brush = QBrush();
    poly << QPoint(63, 86) << QPoint(77, 72) << QPoint(88, 35) << QPoint(82, 22)
         << QPoint(70, 31) << QPoint(57, 67);

    poly.translate(transX, transY);

    brush.setColor(QColor(93, 236, 206));

    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.drawPolygon(poly);

    poly = QPolygon();
    brush = QBrush();
    poly << QPoint(63, 86) << QPoint(57, 67) << QPoint(32, 62) << QPoint(17, 73)
         << QPoint(17, 87) << QPoint(48, 97);

    poly.translate(transX, transY);

    brush.setColor(QColor(67, 204, 174));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.drawPolygon(poly);

    poly = QPolygon();
    brush = QBrush();
    poly << QPoint(17, 73) << QPoint(17, 60) << QPoint(32, 31) << QPoint(42, 22)
         << QPoint(45, 30) << QPoint(32, 62);

    poly.translate(transX, transY);
    brush.setColor(QColor(148, 242, 224));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.drawPolygon(poly);

    poly = QPolygon();
    brush = QBrush();
    poly << QPoint(17, 73) << QPoint(17, 60) << QPoint(32, 31) << QPoint(45, 20)
         << QPoint(45, 30) << QPoint(32, 62);
    poly.translate(transX, transY);

    brush.setColor(QColor(212, 249, 242));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.drawPolygon(poly);

    poly = QPolygon();
    brush = QBrush();
    poly << QPoint(45, 30) << QPoint(45, 20) << QPoint(58, 10) << QPoint(77, 10)
         << QPoint(82, 21) << QPoint(70, 31);
    poly.translate(transX, transY);

    brush.setColor(QColor(212, 249, 242));
    brush.setStyle(Qt::SolidPattern);

    painter.setBrush(brush);
    painter.drawPolygon(poly);

    QPen textPen(QColor(50, 100, 90), 5, Qt::SolidLine, Qt::RoundCap,
                 Qt::RoundJoin);
    painter.setPen(textPen);
    //    painter.drawText(hCenter - 30, vCenter + 60, "Diamonds");
}
