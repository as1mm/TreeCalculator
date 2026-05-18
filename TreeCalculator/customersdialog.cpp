#include "customersdialog.h"
#include "ui_customersdialog.h"
#include <QInputDialog>
#include <QMessageBox>

CustomersDialog::CustomersDialog(SpeciesDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomersDialog),
    m_db(db)
{
    ui->setupUi(this);

    setWindowTitle("Заказчики");

    // Лейауты (для того, чтобы кнопки и таблицы растягивались при увеличении окна)
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(ui->tblCustomers);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(ui->btnAdd);
    btnLayout->addWidget(ui->btnDelete);
    btnLayout->addStretch();
    btnLayout->addWidget(ui->btnClose);
    mainLayout->addLayout(btnLayout);
    ui->tblCustomers->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Настройки таблицы
    ui->tblCustomers->setColumnCount(4);
    ui->tblCustomers->setHorizontalHeaderLabels({"ID", "Название", "Город", "Адрес"});
    ui->tblCustomers->setColumnHidden(0, true);
    ui->tblCustomers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblCustomers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblCustomers->horizontalHeader()->setStretchLastSection(true);
    loadCustomers();

    connect(ui->btnAdd, &QPushButton::clicked, this, &CustomersDialog::btnAdd_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &CustomersDialog::btnDelete_clicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &CustomersDialog::close);
}

CustomersDialog::~CustomersDialog() {
    delete ui;
}

void CustomersDialog::loadCustomers() {
    ui->tblCustomers->setRowCount(0);
    QVector<Customer> list = m_db->allCustomers();
    for (const Customer &c : list) {
        int row = ui->tblCustomers->rowCount();
        ui->tblCustomers->insertRow(row);
        ui->tblCustomers->setItem(row, 0, new QTableWidgetItem(QString::number(c.id)));
        ui->tblCustomers->setItem(row, 1, new QTableWidgetItem(c.name));
        ui->tblCustomers->setItem(row, 2, new QTableWidgetItem(c.city));
        ui->tblCustomers->setItem(row, 3, new QTableWidgetItem(c.address));
    }
}

void CustomersDialog::btnAdd_clicked() {
    bool ok;
    QString name = QInputDialog::getText(this, "Новый заказчик", "Название:", QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty()) return;
    QString city = QInputDialog::getText(this, "Новый заказчик", "Город:", QLineEdit::Normal, "", &ok);
    if (!ok) return;
    QString address = QInputDialog::getText(this, "Новый заказчик", "Адрес:", QLineEdit::Normal, "", &ok);
    if (!ok) return;

    if (m_db->addCustomer(name, city, address)) {
        loadCustomers();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить заказчика.");
    }
}

void CustomersDialog::btnDelete_clicked() {
    int row = ui->tblCustomers->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Удаление", "Выберите заказчика.");
        return;
    }
    int id = ui->tblCustomers->item(row, 0)->text().toInt();
    if (QMessageBox::question(this, "Подтверждение", "Удалить заказчика?") == QMessageBox::Yes) {
        m_db->removeCustomer(id);
        loadCustomers();
    }
}
