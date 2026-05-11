#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SpeciesDatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void btnCalculate_clicked();
    void btnAddToReport_clicked();
    void btnDeleteRecord_clicked();
    void updateTable();   // обновляет таблицу и сумму
    void btnSettings_clicked();

private:
    Ui::MainWindow *ui;
    SpeciesDatabase m_database;
};
#endif // MAINWINDOW_H
