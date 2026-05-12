#ifndef ORDERDETAILDIALOG_H
#define ORDERDETAILDIALOG_H

#include <QDialog>
#include "SpeciesDatabase.h"

namespace Ui {
class OrderDetailDialog;
}

class OrderDetailDialog : public QDialog {
    Q_OBJECT
public:
    explicit OrderDetailDialog(SpeciesDatabase *db, int orderId, QWidget *parent = nullptr);
    ~OrderDetailDialog();

signals:
    void orderChanged();

private slots:
    void btnAddItem_clicked();
    void btnDeleteItem_clicked();
    void btnAllocate_clicked();
    void loadItems();

private:
    Ui::OrderDetailDialog *ui;
    SpeciesDatabase *m_db;
    int m_orderId;
};

#endif
