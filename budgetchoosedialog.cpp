#include "budgetchoosedialog.h"
#include "ui_budgetchoosedialog.h"

BudgetChooseDialog::BudgetChooseDialog(QWidget *parent, double *fromFilter, double *toFilter)
    : QDialog(parent)
    , ui(new Ui::BudgetChooseDialog)
    , from(fromFilter)
    , to(toFilter)
{
    ui->setupUi(this);

    connect(this, SIGNAL(accepted()), this, SLOT(applyBudget()));
}

void BudgetChooseDialog::applyBudget()
{
    *from = ui->fromEdit->text().toDouble();
    *to = ui->toEdit->text().toDouble();
}
BudgetChooseDialog::~BudgetChooseDialog()
{
    delete ui;
}
