#include "stockdialog.h"
#include "ui_stockdialog.h"
#include <QInputDialog>
#include <QMessageBox>

StockDialog::StockDialog(SpeciesDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StockDialog),
    m_db(db)
{
    ui->setupUi(this);

    setWindowTitle("Склад");

    // Лейауты (для того, чтобы кнопки и таблицы растягивались при увеличении окна)
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(ui->tblStock);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(ui->btnAdd);
    btnLayout->addWidget(ui->btnDelete);
    btnLayout->addStretch();
    btnLayout->addWidget(ui->btnClose);
    mainLayout->addLayout(btnLayout);
    ui->tblStock->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Настройка таблицы
    ui->tblStock->setColumnCount(9);
    QStringList headers = {"ID", "Порода", "Тип", "Длина, мм", "Ширина, мм", "Толщина, мм",
                           "Объём ед., м³", "Кол-во", "Цена за шт., руб."};
    ui->tblStock->setHorizontalHeaderLabels(headers);
    ui->tblStock->setColumnHidden(0, true);   // скрываем ID
    ui->tblStock->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblStock->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblStock->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblStock->horizontalHeader()->setStretchLastSection(true);

    loadStockTable();

    connect(ui->btnAdd, &QPushButton::clicked, this, &StockDialog::btnAdd_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &StockDialog::btnDelete_clicked);
    connect(ui->btnClose, &QPushButton::clicked, this, &StockDialog::close);
}

StockDialog::~StockDialog() {
    delete ui;
}

void StockDialog::loadStockTable() {
    ui->tblStock->setRowCount(0);
    QVector<StockItem> items = m_db->allStockItems();
    for (const StockItem &it : items) {
        int row = ui->tblStock->rowCount();
        ui->tblStock->insertRow(row);

        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(it.id));
        ui->tblStock->setItem(row, 0, idItem);

        ui->tblStock->setItem(row, 1, new QTableWidgetItem(it.species));
        ui->tblStock->setItem(row, 2, new QTableWidgetItem(it.type));
        ui->tblStock->setItem(row, 3, new QTableWidgetItem(QString::number(it.length, 'f', 0)));
        ui->tblStock->setItem(row, 4, new QTableWidgetItem(QString::number(it.width, 'f', 0)));
        ui->tblStock->setItem(row, 5, new QTableWidgetItem(QString::number(it.thickness, 'f', 0)));
        ui->tblStock->setItem(row, 6, new QTableWidgetItem(QString::number(it.volumePerUnit, 'f', 4)));
        ui->tblStock->setItem(row, 7, new QTableWidgetItem(QString::number(it.quantity)));
        ui->tblStock->setItem(row, 8, new QTableWidgetItem(QString::number(it.pricePerUnit, 'f', 2)));
    }
}

void StockDialog::btnAdd_clicked() {
    // Список пород для выбора
    QStringList speciesList = m_db->speciesList();
    if (speciesList.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала добавьте породы в справочник.");
        return;
    }

    bool ok;
    QString species = QInputDialog::getItem(this, "Новая позиция", "Порода:", speciesList, 0, false, &ok);
    if (!ok) return;

    QString type = QInputDialog::getText(this, "Новая позиция", "Тип (доска, брус, бревно...):", QLineEdit::Normal, "доска", &ok);
    if (!ok) return;

    double length = QInputDialog::getDouble(this, "Новая позиция", "Длина (мм):", 6000, 1, 20000, 0, &ok);
    if (!ok) return;
    double width = QInputDialog::getDouble(this, "Новая позиция", "Ширина (мм):", 150, 1, 1000, 0, &ok);
    if (!ok) return;
    double thickness = QInputDialog::getDouble(this, "Новая позиция", "Толщина (мм):", 50, 1, 500, 0, &ok);
    if (!ok) return;

    // Вычисляем объём одной единицы (переводим мм³ → м³)
    double volPerUnit = (length * width * thickness) / 1'000'000'000.0;

    // Предлагаем пользователю вычислить автоматически, но можно изменить
    QString volStr = QInputDialog::getText(this, "Новая позиция", "Объём единицы (м³):",
                                          QLineEdit::Normal, QString::number(volPerUnit, 'f', 6), &ok);
    if (!ok) return;
    volPerUnit = volStr.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверное значение объёма.");
        return;
    }

    int quantity = QInputDialog::getInt(this, "Новая позиция", "Количество (шт.):", 1, 0, 1000000, 1, &ok);
    if (!ok) return;
    double price = QInputDialog::getDouble(this, "Новая позиция", "Цена за штуку (руб.):", 0, 0, 10000000, 2, &ok);
    if (!ok) return;

    if (m_db->addStockItem(species, type, length, width, thickness, volPerUnit, quantity, price)) {
        loadStockTable();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить позицию.");
    }
}

void StockDialog::btnDelete_clicked() {
    int row = ui->tblStock->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Удаление", "Выберите позицию для удаления.");
        return;
    }
    int id = ui->tblStock->item(row, 0)->text().toInt();
    int ret = QMessageBox::question(this, "Подтверждение",
                                    QString("Удалить позицию?"),
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        m_db->removeStockItem(id);
        loadStockTable();
    }
}
