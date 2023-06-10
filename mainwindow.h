#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "diamondproxymodel.h"
#include "diamondstable.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onTableClicked(const QModelIndex &index);
    void avgDiamondClicked();
    void budgetClicked();
    void graphClicked();
    void minusClicked();
    void plusClicked();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    DiamondSortFilterProxyModel *proxyModel;
    DiamondsTable *table;
    QString fp = "";
    bool budgetFilerEnabled = false;
};
#endif // MAINWINDOW_H
