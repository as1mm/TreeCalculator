#include "ordersdialog.h"
#include "ui_ordersdialog.h"
#include "orderdetaildialog.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDate>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateEdit>
#include <QDialogButtonBox>

OrdersDialog::OrdersDialog(SpeciesDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrdersDialog),
    m_db(db)
{
    ui->setupUi(this);

    setWindowTitle("Заказы");

    // Лейауты (для того, чтобы кнопки и таблицы растягивались при увеличении окна)
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(ui->tblOrders);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(ui->btnCreate);
    btnLayout->addWidget(ui->btnOpen);
    btnLayout->addWidget(ui->btnDelete);
    btnLayout->addStretch();
    btnLayout->addWidget(ui->btnClose);
    mainLayout->addLayout(btnLayout);
    ui->tblOrders->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Настройка таблицы
    ui->tblOrders->setColumnCount(4);
    QStringList headers = {"ID", "Заказчик", "Дата", "Статус"};
    ui->tblOrders->setHorizontalHeaderLabels(headers);
    ui->tblOrders->setColumnHidden(0, true);
    ui->tblOrders->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblOrders->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblOrders->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblOrders->horizontalHeader()->setStretchLastSection(true);

    loadOrders();

    connect(ui->btnCreate, &QPushButton::clicked, this, &OrdersDialog::btnCreate_clicked);
    connect(ui->btnOpen, &QPushButton::clicked, this, &OrdersDialog::btnOpen_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &OrdersDialog::btnDelete_clicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &OrdersDialog::close);
}

OrdersDialog::~OrdersDialog() {
    delete ui;
}

void OrdersDialog::loadOrders() {
    ui->tblOrders->setRowCount(0);
    QVector<Order> orders = m_db->allOrders();
    for (const Order &o : orders) {
        int row = ui->tblOrders->rowCount();
        ui->tblOrders->insertRow(row);

        ui->tblOrders->setItem(row, 0, new QTableWidgetItem(QString::number(o.id)));
        Customer c = m_db->customerById(o.customerId);
        ui->tblOrders->setItem(row, 1, new QTableWidgetItem(c.name.isEmpty() ? QString("ID %1").arg(o.customerId) : c.name));
        ui->tblOrders->setItem(row, 2, new QTableWidgetItem(o.date.toString("dd.MM.yyyy")));
        ui->tblOrders->setItem(row, 3, new QTableWidgetItem(o.status));
    }
}

void OrdersDialog::btnCreate_clicked() {
    // Список заказчиков
    QVector<Customer> customers = m_db->allCustomers();
    if (customers.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала добавьте заказчиков.");
        return;
    }
    QStringList customerNames;
    for (const Customer &c : customers) {
        customerNames << QString("%1 (г. %2)").arg(c.name, c.city);
    }

    bool ok;
    QString selected = QInputDialog::getItem(this, "Новый заказ", "Выберите заказчика:",
                                             customerNames, 0, false, &ok);
    if (!ok) return;
    int idx = customerNames.indexOf(selected);
    if (idx < 0) return;
    int customerId = customers[idx].id;

    QDialog dateDlg(this);
    dateDlg.setWindowTitle(tr("Новый заказ"));
    QVBoxLayout *layout = new QVBoxLayout(&dateDlg);
    QLabel *lblDate = new QLabel(tr("Дата заказа:"));
    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    dateEdit->setMinimumDate(QDate(2000, 1, 1));
    dateEdit->setMaximumDate(QDate(2100, 12, 31));
    layout->addWidget(lblDate);
    layout->addWidget(dateEdit);

    QDialogButtonBox *btnBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(btnBox, &QDialogButtonBox::accepted, &dateDlg, &QDialog::accept);
    connect(btnBox, &QDialogButtonBox::rejected, &dateDlg, &QDialog::reject);
    layout->addWidget(btnBox);

    if (dateDlg.exec() != QDialog::Accepted) return;
    QDate date = dateEdit->date();

    if (!ok) return;

    int orderId = m_db->createOrder(customerId, date);
    if (orderId < 0) {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать заказ.");
        return;
    }
    loadOrders();
}

void OrdersDialog::btnOpen_clicked() {
    int row = ui->tblOrders->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Открытие", "Выберите заказ.");
        return;
    }
    int orderId = ui->tblOrders->item(row, 0)->text().toInt();
    OrderDetailDialog dlg(m_db, orderId, this);
    connect(&dlg, &OrderDetailDialog::orderChanged, this, &OrdersDialog::loadOrders);
    dlg.exec();
    loadOrders();
}

void OrdersDialog::btnDelete_clicked() {
    int row = ui->tblOrders->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Удаление", "Выберите заказ.");
        return;
    }
    int orderId = ui->tblOrders->item(row, 0)->text().toInt();
    int ret = QMessageBox::question(this, "Подтверждение",
                                    QString("Удалить заказ №%1?").arg(orderId),
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        // Удаляем заказ и его позиции (каскадно в коде)
        QSqlQuery q(QSqlDatabase::database());
        q.prepare("DELETE FROM order_items WHERE order_id = ?");
        q.addBindValue(orderId);
        q.exec();
        q.prepare("DELETE FROM orders WHERE id = ?");
        q.addBindValue(orderId);
        q.exec();
        loadOrders();
    }
}
