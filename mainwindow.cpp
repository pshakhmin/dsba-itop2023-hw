#include "mainwindow.h"

#include <qsortfilterproxymodel.h>

#include <QFile>
#include <QFileDialog>
#include <QStandardPaths>
#include <iostream>

#include "./ui_mainwindow.h"
#include "avgdiamond.h"
#include "budgetchoosedialog.h"
#include "chartview.h"
#include "chartwindow.h"
#include "diamonddialog.h"
#include "diamondproxymodel.h"
#include "diamondstable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table = new DiamondsTable(this);

    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex &)), this,
            SLOT(onTableClicked(const QModelIndex &)));

    connect(ui->avgDiamondButton, SIGNAL(clicked(bool)), this,
            SLOT(avgDiamondClicked()));

    connect(ui->budgetButton, SIGNAL(clicked(bool)), this,
            SLOT(budgetClicked()));

    connect(ui->graphButton, SIGNAL(clicked(bool)), this, SLOT(graphClicked()));
    connect(ui->minusButton, SIGNAL(clicked(bool)), this, SLOT(minusClicked()));

    QPainter painter(ui->logoWidget);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "Qt");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::avgDiamondClicked() {
    AvgDiamond *ad = new AvgDiamond(this, table->getAvgDiamond());
    ad->show();
}

void MainWindow::minusClicked() {
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    qInfo() << indexes;
    for (const QModelIndex &index : indexes) {
        size_t clickedIndex = proxyModel->index(index.row(), 0).data().toUInt();
        table->removeRow(clickedIndex, index);
        ui->tableView->update();
    }
}

void MainWindow::budgetClicked() {
    if (!budgetFilerEnabled) {
        qInfo() << ui->budgetButton->text();
        double from, to;
        BudgetChooseDialog *bcd = new BudgetChooseDialog(this, &from, &to);
        int result = bcd->exec();
        if (result == QDialog::Accepted) {
            ui->budgetButton->setText("Remove bugdet filter");
            budgetFilerEnabled = true;
            proxyModel->setFilter(from, to);
            proxyModel->setFilterKeyColumn(5);
            ui->tableView->update();
        }
    } else {
        ui->budgetButton->setText("Bugdet filter");
        budgetFilerEnabled = false;
        proxyModel->setFilter(0, 1000000);
        proxyModel->setFilterKeyColumn(5);
        ui->tableView->update();
    }
}

void MainWindow::graphClicked() {
    QMap<QChar, QList<QPair<size_t, double>>> dataForChart;
    table->getDataForGraph(&dataForChart);

    ChartView *chartView = new ChartView(this, &dataForChart);
    ChartWindow *chartWindow = new ChartWindow();
    chartWindow->setCentralWidget(chartView);
    chartWindow->show();
}

void MainWindow::onTableClicked(const QModelIndex &index) {
    size_t clickedIndex = proxyModel->index(index.row(), 0).data().toUInt();
    Diamond clickedDiamond = table->getDiamondByIndex(clickedIndex);
    DiamondDialog *dd = new DiamondDialog(&clickedDiamond);
    int result = dd->exec();
    if (result == QDialog::Accepted) {
        table->saveDiamond(clickedDiamond);
        ui->tableView->update();
    }
}

void MainWindow::on_actionOpen_triggered() {
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("CSV (*.csv)"));
    dialog.setFileMode(QFileDialog::AnyFile);
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        table->readData(fileNames[0]);
        fp = fileNames[0];
        proxyModel = new DiamondSortFilterProxyModel(this);
        proxyModel->setSourceModel(table);
        proxyModel->setDynamicSortFilter(true);

        ui->tableView->setModel(proxyModel);
        ui->tableView->setSortingEnabled(true);
    }
}

void MainWindow::on_actionSave_As_triggered() {
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("CSV (*.csv)"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        table->saveAs(fileNames[0]);
    }
}

void MainWindow::on_actionSave_triggered() {
    if (fp != "") table->saveAs(fp);
}
