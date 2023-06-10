#include "avgdiamond.h"
#include "ui_avgdiamond.h"

AvgDiamond::AvgDiamond(QWidget* parent, const Diamond& diamond)
    : QDialog(parent), ui(new Ui::AvgDiamond) {
    ui->setupUi(this);
    ui->caratEdit->setText(QString::number(diamond.carat));
    ui->cutEdit->setText(diamond.cut);
    ui->colorEdit->setText(diamond.color);
    ui->clarityEdit->setText(diamond.clarity);
    ui->priceEdit->setText(QString::number(diamond.price));
}

AvgDiamond::~AvgDiamond() { delete ui; }
