#ifndef LOGOWIDGET_H
#define LOGOWIDGET_H

#include <QWidget>

class QPaintEvent;

class LogoWidget : public QWidget {
    Q_OBJECT

   public:
    LogoWidget(QWidget* parent = nullptr);
    ~LogoWidget();
    virtual void paintEvent(QPaintEvent* event);
};

#endif // LOGOWIDGET_H
