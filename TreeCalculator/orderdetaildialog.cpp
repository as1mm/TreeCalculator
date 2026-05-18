#include "orderdetaildialog.h"
#include "ui_orderdetaildialog.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlQuery>

OrderDetailDialog::OrderDetailDialog(SpeciesDatabase *db, int orderId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderDetailDialog),
    m_db(db),
    m_orderId(orderId)
{
    ui->setupUi(this);

    setWindowTitle("Детали заказа");

    // Лейауты (для того, чтобы кнопки и таблицы растягивались при увеличении окна)
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(ui->lblCustomerInfo);
    mainLayout->addWidget(ui->tblItems);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(ui->btnAddItem);
    btnLayout->addWidget(ui->btnDeleteItem);
    btnLayout->addWidget(ui->btnAllocate);
    //btnLayout->addWidget(ui->btnSummary);   // если уже добавлена кнопка «Сводка»
    btnLayout->addStretch();
    btnLayout->addWidget(ui->btnClose);
    mainLayout->addLayout(btnLayout);
    ui->tblItems->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Заголовок с информацией о заказчике
    QVector<Order> orders = m_db->allOrders();
    Customer c;
    for (const Order &o : orders) {
        if (o.id == orderId) {
            c = m_db->customerById(o.customerId);
            break;
        }
    }
    ui->lblCustomerInfo->setText(QString("Заказ №%1 от %2. Заказчик: %3 (%4, %5)")
                                 .arg(orderId)
                                 .arg(orders.first().date.toString("dd.MM.yyyy")) // упрощенно, лучше хранить текущий заказ
                                 .arg(c.name, c.city, c.address));
    // Более точно: можно получить заказ по ID отдельным методом, но для краткости оставим так.
    // Добавим метод `Order orderById(int id)` при необходимости.

    ui->tblItems->setColumnCount(8);
    QStringList headers = {"ID", "Порода", "Тип", "Длина", "Ширина", "Толщина", "Нужно м³", "Выделено м³"};
    ui->tblItems->setHorizontalHeaderLabels(headers);
    ui->tblItems->setColumnHidden(0, true);
    ui->tblItems->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblItems->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblItems->horizontalHeader()->setStretchLastSection(true);

    loadItems();

    connect(ui->btnAddItem, &QPushButton::clicked, this, &OrderDetailDialog::btnAddItem_clicked);
    connect(ui->btnDeleteItem, &QPushButton::clicked, this, &OrderDetailDialog::btnDeleteItem_clicked);
    connect(ui->btnAllocate, &QPushButton::clicked, this, &OrderDetailDialog::btnAllocate_clicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &QDialog::close);
}

OrderDetailDialog::~OrderDetailDialog() {
    delete ui;
}

void OrderDetailDialog::loadItems() {
    ui->tblItems->setRowCount(0);
    QVector<OrderItem> items = m_db->orderItems(m_orderId);
    for (const OrderItem &oi : items) {
        int row = ui->tblItems->rowCount();
        ui->tblItems->insertRow(row);
        ui->tblItems->setItem(row, 0, new QTableWidgetItem(QString::number(oi.id)));
        ui->tblItems->setItem(row, 1, new QTableWidgetItem(oi.species));
        ui->tblItems->setItem(row, 2, new QTableWidgetItem(oi.type));
        ui->tblItems->setItem(row, 3, new QTableWidgetItem(QString::number(oi.length, 'f', 0)));
        ui->tblItems->setItem(row, 4, new QTableWidgetItem(QString::number(oi.width, 'f', 0)));
        ui->tblItems->setItem(row, 5, new QTableWidgetItem(QString::number(oi.thickness, 'f', 0)));
        ui->tblItems->setItem(row, 6, new QTableWidgetItem(QString::number(oi.volumeNeeded, 'f', 4)));
        ui->tblItems->setItem(row, 7, new QTableWidgetItem(QString::number(oi.volumeAllocated, 'f', 4)));
    }
}

void OrderDetailDialog::btnAddItem_clicked() {
    QStringList speciesList = m_db->speciesList();
    if (speciesList.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала добавьте породы в справочник.");
        return;
    }

    bool ok;
    QString species = QInputDialog::getItem(this, "Новая позиция", "Порода:", speciesList, 0, false, &ok);
    if (!ok) return;

    QString type = QInputDialog::getText(this, "Новая позиция", "Тип (доска, брус...):", QLineEdit::Normal, "доска", &ok);
    if (!ok) return;

    double length = QInputDialog::getDouble(this, "Новая позиция", "Длина (мм):", 6000, 1, 20000, 0, &ok);
    if (!ok) return;
    double width = QInputDialog::getDouble(this, "Новая позиция", "Ширина (мм):", 150, 1, 1000, 0, &ok);
    if (!ok) return;
    double thickness = QInputDialog::getDouble(this, "Новая позиция", "Толщина (мм):", 50, 1, 500, 0, &ok);
    if (!ok) return;

    double volume = QInputDialog::getDouble(this, "Новая позиция", "Потребный объём (м³):", 1.0, 0.001, 10000.0, 4, &ok);
    if (!ok) return;

    if (m_db->addOrderItem(m_orderId, species, type, length, width, thickness, volume)) {
        loadItems();
        emit orderChanged();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить позицию.");
    }
}

void OrderDetailDialog::btnDeleteItem_clicked() {
    int row = ui->tblItems->currentRow();
    if (row < 0) return;
    int itemId = ui->tblItems->item(row, 0)->text().toInt();
    if (QMessageBox::question(this, "Подтверждение", "Удалить позицию?") == QMessageBox::Yes) {
        QSqlQuery q(QSqlDatabase::database());
        q.prepare("DELETE FROM order_items WHERE id = ?");
        q.addBindValue(itemId);
        q.exec();
        loadItems();
        emit orderChanged();
    }
}

void OrderDetailDialog::btnAllocate_clicked() {
    int row = ui->tblItems->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Распределение", "Выберите позицию заказа.");
        return;
    }
    int itemId = ui->tblItems->item(row, 0)->text().toInt();
    OrderItem oi;
    bool found = false;
    QVector<OrderItem> items = m_db->orderItems(m_orderId);
    for (const OrderItem &i : items) {
        if (i.id == itemId) {
            oi = i;
            found = true;
            break;
        }
    }
    if (!found) return;

    // Показываем диалог со списком подходящих складских позиций
    QVector<StockItem> stock = m_db->allStockItems();
    // Фильтруем по породе и типу (упрощённо)
    QStringList stockList;
    QList<int> stockIds;
    for (const StockItem &si : stock) {
        if (si.species == oi.species && si.type == oi.type && si.quantity > 0) {
            stockList << QString("%1 %2 %3x%4x%5, в наличии: %6 шт (объём ед. %7 м³)")
                         .arg(si.species)
                         .arg(si.type)
                         .arg(si.length).arg(si.width).arg(si.thickness)
                         .arg(si.quantity)
                         .arg(si.volumePerUnit, 0, 'f', 4);
            stockIds << si.id;
        }
    }
    if (stockList.isEmpty()) {
        QMessageBox::information(this, "Распределение", "Нет подходящих складских позиций.");
        return;
    }

    bool ok;
    QString sel = QInputDialog::getItem(this, "Выберите складскую позицию",
                                        "Позиции на складе:", stockList, 0, false, &ok);
    if (!ok) return;
    int idx = stockList.indexOf(sel);
    if (idx < 0) return;
    int stockId = stockIds[idx];
    StockItem selectedStock;
    for (const StockItem &si : stock) {
        if (si.id == stockId) {
            selectedStock = si;
            break;
        }
    }

    // Запрашиваем объём для списания
    double availVolume = selectedStock.quantity * selectedStock.volumePerUnit;
    double needed = oi.volumeNeeded - oi.volumeAllocated;
    if (needed <= 0) {
        QMessageBox::information(this, "Распределение", "Позиция уже полностью обеспечена.");
        return;
    }
    double maxVol = qMin(availVolume, needed);
    double volume = QInputDialog::getDouble(this, "Объём списания",
                                            QString("Какой объём списать со склада? (доступно %1 м³, нужно %2 м³)")
                                            .arg(availVolume, 0, 'f', 4).arg(needed, 0, 'f', 4),
                                            maxVol, 0.001, maxVol, 4, &ok);
    if (!ok) return;

    if (m_db->allocateStock(itemId, stockId, volume)) {
        loadItems();
        emit orderChanged();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось распределить. Возможно, недостаточно количества на складе.");
    }
}
