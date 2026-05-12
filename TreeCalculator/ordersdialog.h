#ifndef ORDERSDIALOG_H
#define ORDERSDIALOG_H

#include <QDialog>
#include "SpeciesDatabase.h"

namespace Ui {
class OrdersDialog;
}

class OrdersDialog : public QDialog {
    Q_OBJECT
public:
    explicit OrdersDialog(SpeciesDatabase *db, QWidget *parent = nullptr);
    ~OrdersDialog();

private slots:
    void btnCreate_clicked();
    void btnOpen_clicked();
    void btnDelete_clicked();
    void loadOrders();

private:
    Ui::OrdersDialog *ui;
    SpeciesDatabase *m_db;
};

#endif
