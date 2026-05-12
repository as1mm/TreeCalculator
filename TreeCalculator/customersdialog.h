#ifndef CUSTOMERSDIALOG_H
#define CUSTOMERSDIALOG_H

#include <QDialog>
#include "SpeciesDatabase.h"

namespace Ui {
class CustomersDialog;
}

class CustomersDialog : public QDialog {
    Q_OBJECT
public:
    explicit CustomersDialog(SpeciesDatabase *db, QWidget *parent = nullptr);
    ~CustomersDialog();
private slots:
    void btnAdd_clicked();
    void btnDelete_clicked();
    void loadCustomers();
private:
    Ui::CustomersDialog *ui;
    SpeciesDatabase *m_db;
};

#endif
