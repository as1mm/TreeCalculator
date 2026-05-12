#ifndef STOCKDIALOG_H
#define STOCKDIALOG_H

#include <QDialog>
#include "SpeciesDatabase.h"

namespace Ui {
class StockDialog;
}

class StockDialog : public QDialog {
    Q_OBJECT

public:
    explicit StockDialog(SpeciesDatabase *db, QWidget *parent = nullptr);
    ~StockDialog();

private slots:
    void btnAdd_clicked();
    void btnDelete_clicked();
    void loadStockTable();

private:
    Ui::StockDialog *ui;
    SpeciesDatabase *m_db;
};

#endif // STOCKDIALOG_H
