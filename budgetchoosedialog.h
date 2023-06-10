#ifndef BUDGETCHOOSEDIALOG_H
#define BUDGETCHOOSEDIALOG_H

#include <QDialog>

namespace Ui {
class BudgetChooseDialog;
}

class BudgetChooseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BudgetChooseDialog(QWidget *parent = nullptr,
                                double *from = nullptr,
                                double *to = nullptr);
    ~BudgetChooseDialog();

private:
    Ui::BudgetChooseDialog *ui;
    double *from = nullptr;
    double *to = nullptr;
private slots:
    void applyBudget();
};

#endif // BUDGETCHOOSEDIALOG_H
