#ifndef DIAMONDDIALOG_H
#define DIAMONDDIALOG_H

#include <QDialog>

#include "diamondstable.h"

namespace Ui {
class DiamondDialog;
}

class DiamondDialog : public QDialog
{
    Q_OBJECT

   public:
    explicit DiamondDialog(Diamond *diamond, QWidget *parent = nullptr);
    ~DiamondDialog();

   private:
    Ui::DiamondDialog *ui;
    Diamond *diamond = nullptr;
   private slots:
    void applyDiamondChange();
};

#endif // DIAMONDDIALOG_H
