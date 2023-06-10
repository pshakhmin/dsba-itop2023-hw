#include "diamonddialog.h"
#include "ui_diamonddialog.h"

DiamondDialog::DiamondDialog(Diamond* diamondPtr, QWidget* parent)
    : QDialog(parent), ui(new Ui::DiamondDialog), diamond(diamondPtr) {
    ui->setupUi(this);

    ui->indexLine->setText(QString::number(diamond->index));
    ui->caratLine->setText(QString::number(diamond->carat));
    //    ui->caratLine->setValidator(new QDoubleValidator(0, 100, 2, this));

    ui->cutComboBox->setCurrentText(diamond->cut);
    ui->colorComboBox->setCurrentText(diamond->color);

    ui->priceLine->setText(QString::number(diamond->price).replace('.', ','));
    ui->priceLine->setValidator(new QIntValidator(0, 100000, this));

    ui->clarityComboBox->setCurrentText(diamond->clarity);

    ui->depthLine->setText(QString::number(diamond->depth).replace('.', ','));
    ui->depthLine->setValidator(new QDoubleValidator(0, 100, 2, this));

    ui->tableLine->setText(QString::number(diamond->table).replace('.', ','));
    ui->tableLine->setValidator(new QDoubleValidator(0, 100, 2, this));

    ui->lengthLine->setText(QString::number(diamond->length).replace('.', ','));
    ui->lengthLine->setValidator(new QDoubleValidator(0, 100, 2, this));

    ui->widthLine->setText(QString::number(diamond->width).replace('.', ','));
    ui->widthLine->setValidator(new QDoubleValidator(0, 100, 2, this));

    connect(this, SIGNAL(accepted()), this, SLOT(applyDiamondChange()));
}

void DiamondDialog::applyDiamondChange() {
    diamond->carat = ui->caratLine->text().toDouble();
    diamond->cut = ui->cutComboBox->currentText();
    diamond->color = ui->colorComboBox->currentText().at(0);
    diamond->price = ui->priceLine->text().toULong();
    diamond->clarity = ui->clarityComboBox->currentText();
    diamond->depth = ui->depthLine->text().toDouble();
    diamond->table = ui->tableLine->text().toDouble();
    diamond->length = ui->lengthLine->text().toDouble();
    diamond->width = ui->widthLine->text().toDouble();
}

DiamondDialog::~DiamondDialog() { delete ui; }
