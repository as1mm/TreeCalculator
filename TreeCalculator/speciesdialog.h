#ifndef SPECIESDIALOG_H
#define SPECIESDIALOG_H

#include <QDialog>
#include "SpeciesDatabase.h"

namespace Ui {
class SpeciesDialog;
}

class SpeciesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SpeciesDialog(SpeciesDatabase *db, QWidget *parent = nullptr);
    ~SpeciesDialog();

signals:
    void speciesChanged();

private slots:
    void btnAdd_clicked();
    void btnDelete_clicked();
    void btnReset_clicked();
    void cellChanged(int row, int column);
    void loadSpeciesTable();


private:
    Ui::SpeciesDialog *ui;
    SpeciesDatabase *m_db;
};

#endif // SPECIESDIALOG_H
