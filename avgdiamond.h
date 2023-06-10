#ifndef AVGDIAMOND_H
#define AVGDIAMOND_H

#include <QDialog>

#include "diamondstable.h"

namespace Ui {
class AvgDiamond;
}

class AvgDiamond : public QDialog {
    Q_OBJECT

   public:
    explicit AvgDiamond(QWidget *parent = nullptr,
                        const Diamond &diamond = Diamond());
    ~AvgDiamond();

   private:
    Ui::AvgDiamond *ui;
};

#endif // AVGDIAMOND_H
