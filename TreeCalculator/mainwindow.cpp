#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "TreeVolumeCalculator.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include "speciesdialog.h"
#include <QApplication>
#include <QStyleFactory>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Меняем стиль
    qApp->setStyle(QStyleFactory::create("Fusion"));

    // Создаём тёмную палитру (делаем темную тему)
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(35, 35, 35));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);

    // иконки
    ui->btnAddToReport->setIcon(QIcon(":/icons/add_.png"));
    ui->btnDeleteRecord->setIcon(QIcon(":/icons/delete_.png"));

    // Меню "Инструменты"
    QMenu *toolsMenu = menuBar()->addMenu(tr("Инструменты"));
    QAction *editSpeciesAction = toolsMenu->addAction(
                QIcon(":/icons/instrument_.png"),          // иконка
                tr("Редактировать породы")
                );
    connect(editSpeciesAction, &QAction::triggered, this, &MainWindow::btnSettings_clicked);


    // Заполняем комбобокс породами из БД
    ui->cmbSpecies->addItems(m_database.speciesList());

    ui->tblRecords->setColumnCount(8);
    QStringList headers = {"Порода", "Диам., см", "Выс., м", "Вид.число", "Объём, м³", "Цена/м³", "Стоимость", "Дата"};
    ui->tblRecords->setHorizontalHeaderLabels(headers);
    ui->tblRecords->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblRecords->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Растягиваем последний столбец по ширине
    ui->tblRecords->horizontalHeader()->setStretchLastSection(true);

    // Сигналы и слоты
    connect(ui->btnCalculate, &QPushButton::clicked, this, &MainWindow::btnCalculate_clicked);
    connect(ui->btnAddToReport, &QPushButton::clicked, this, &MainWindow::btnAddToReport_clicked);
    connect(ui->btnDeleteRecord, &QPushButton::clicked, this, &MainWindow::btnDeleteRecord_clicked);

    // Отображаем существующие записи при старте
    updateTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnCalculate_clicked() {
    QString species = ui->cmbSpecies->currentText();
    double f = m_database.formFactor(species);
    if (f <= 0.0) {
        QMessageBox::warning(this, "Ошибка", "Неизвестная порода или видовое число не задано.");
        return;
    }
    double d = ui->sbDiameter->value();
    double h = ui->sbHeight->value();
    double volume = TreeVolumeCalculator::calculateVolume(d, h, f);
    ui->lblResult->setText(QString("Объём: %1 м³").arg(volume, 0, 'f', 4));
}

void MainWindow::btnAddToReport_clicked() {
    QString species = ui->cmbSpecies->currentText();
    double f = m_database.formFactor(species);
    if (f <= 0.0) { /* ошибка */ return; }
    double d = ui->sbDiameter->value();
    double h = ui->sbHeight->value();
    double volume = TreeVolumeCalculator::calculateVolume(d, h, f);

    double price = m_database.pricePerCubic(species);
    if (price <= 0.0) {
        // Можно предупредить, но не запрещать, или спросить цену
        QMessageBox::StandardButton btn = QMessageBox::question(this, "Цена не задана",
                                         "Для породы '" + species + "' не указана цена за кубометр. Продолжить с нулевой ценой?");
        if (btn != QMessageBox::Yes) return;
    }

    TreeRecord rec;
    rec.species = species;
    rec.diameterCm = d;
    rec.heightM = h;
    rec.formFactor = f;
    rec.volumeM3 = volume;
    rec.pricePerM3 = price;

    if (m_database.addTreeRecord(rec)) {
        updateTable();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить запись.");
    }
}

void MainWindow::btnDeleteRecord_clicked() {
    int row = ui->tblRecords->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Удаление", "Выберите запись для удаления.");
        return;
    }

    // ID хранится в UserRole первой ячейки
    QTableWidgetItem *item = ui->tblRecords->item(row, 0);
    if (!item) return;
    int id = item->data(Qt::UserRole).toInt();

    if (m_database.deleteTreeRecord(id)) {
        updateTable();
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить запись.");
    }
}

void MainWindow::updateTable() {
    QVector<TreeRecord> records = m_database.allTreeRecords();
    ui->tblRecords->setRowCount(records.size());

    for (int i = 0; i < records.size(); ++i) {
        const TreeRecord &r = records[i];

        QTableWidgetItem *itemSpecies = new QTableWidgetItem(r.species);
        itemSpecies->setData(Qt::UserRole, r.id);  // кладём ID
        ui->tblRecords->setItem(i, 0, itemSpecies);
        ui->tblRecords->setItem(i, 1, new QTableWidgetItem(QString::number(r.diameterCm, 'f', 1)));
        ui->tblRecords->setItem(i, 2, new QTableWidgetItem(QString::number(r.heightM, 'f', 1)));
        ui->tblRecords->setItem(i, 3, new QTableWidgetItem(QString::number(r.formFactor, 'f', 2)));
        ui->tblRecords->setItem(i, 4, new QTableWidgetItem(QString::number(r.volumeM3, 'f', 4)));
        ui->tblRecords->setItem(i, 5, new QTableWidgetItem(QString::number(r.pricePerM3, 'f', 2)));
        double cost = r.volumeM3 * r.pricePerM3;
        ui->tblRecords->setItem(i, 6, new QTableWidgetItem(QString::number(cost, 'f', 2)));
        ui->tblRecords->setItem(i, 7, new QTableWidgetItem(r.createdAt.toString("yyyy-MM-dd hh:mm")));
    }

    // Обновляем итоговый объем и стоимость
    double totalVol = m_database.totalVolume();
    double totalCost = m_database.totalPrice();
    ui->lblTotal->setText(QString("Общий объём: %1 м³ | Общая стоимость: %2 руб.")
                          .arg(totalVol, 0, 'f', 4)
                          .arg(totalCost, 0, 'f', 2));
}

void MainWindow::btnSettings_clicked() {
    SpeciesDialog dialog(&m_database, this);
    connect(&dialog, &SpeciesDialog::speciesChanged, this, [this]() {
        ui->cmbSpecies->clear();
        ui->cmbSpecies->addItems(m_database.speciesList());
    });
    dialog.exec();
    // дополнительное обновление
    ui->cmbSpecies->clear();
    ui->cmbSpecies->addItems(m_database.speciesList());
}
