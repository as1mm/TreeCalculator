#include "speciesdialog.h"
#include "ui_speciesdialog.h"
#include <QMessageBox>

SpeciesDialog::SpeciesDialog(SpeciesDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpeciesDialog),
    m_db(db)
{
    ui->setupUi(this);

    // Настройка таблицы
    ui->tblSpecies->setColumnCount(2);
    QStringList headers = { "Название", "Видовое число" };
    ui->tblSpecies->setHorizontalHeaderLabels(headers);
    ui->tblSpecies->horizontalHeader()->setStretchLastSection(true);
    ui->tblSpecies->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblSpecies->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblSpecies->setEditTriggers(QAbstractItemView::DoubleClicked);

    // Загружаем текущие породы
    loadSpeciesTable();

    // Соединения кнопок
    connect(ui->btnAdd, &QPushButton::clicked, this, &SpeciesDialog::btnAdd_clicked);
    connect(ui->btnDelete, &QPushButton::clicked, this, &SpeciesDialog::btnDelete_clicked);
    connect(ui->btnReset, &QPushButton::clicked, this, &SpeciesDialog::btnReset_clicked);

    // Автосохранение при редактировании ячейки
    connect(ui->tblSpecies, &QTableWidget::cellChanged, this, &SpeciesDialog::cellChanged);
}

SpeciesDialog::~SpeciesDialog() {
    delete ui;
}

void SpeciesDialog::loadSpeciesTable() {
    // Блокируем сигналы, чтобы cellChanged не срабатывал при программном заполнении
    ui->tblSpecies->blockSignals(true);
    ui->tblSpecies->setRowCount(0);

    QStringList speciesList = m_db->speciesList();
    for (const QString &name : speciesList) {
        int row = ui->tblSpecies->rowCount();
        ui->tblSpecies->insertRow(row);

        // Название
        QTableWidgetItem *nameItem = new QTableWidgetItem(name);
        nameItem->setFlags(nameItem->flags() | Qt::ItemIsEditable);
        // Сохраняем исходное имя в UserRole, чтобы отследить переименование
        nameItem->setData(Qt::UserRole, name);
        ui->tblSpecies->setItem(row, 0, nameItem);

        // Видовое число
        double f = m_db->formFactor(name);
        QTableWidgetItem *factorItem = new QTableWidgetItem(QString::number(f, 'f', 2));
        factorItem->setFlags(factorItem->flags() | Qt::ItemIsEditable);
        ui->tblSpecies->setItem(row, 1, factorItem);
    }
    ui->tblSpecies->blockSignals(false);
}

void SpeciesDialog::btnAdd_clicked() {
    // Добавляем пустую строку в таблицу и сразу сохраняем в БД
    int row = ui->tblSpecies->rowCount();
    ui->tblSpecies->insertRow(row);

    QString newName = "Новая порода";
    double newFactor = 0.50;

    // Пытаемся добавить в БД
    if (!m_db->addSpecies(newName, newFactor)) {
        // Если не удалось (например, уже есть), сообщим и удалим строку
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить породу. Возможно, такое имя уже существует.");
        ui->tblSpecies->removeRow(row);
        return;
    }

    // Создаём элементы (сигналы временно блокируем, чтобы не вызвать onCellChanged)
    ui->tblSpecies->blockSignals(true);
    QTableWidgetItem *nameItem = new QTableWidgetItem(newName);
    nameItem->setFlags(nameItem->flags() | Qt::ItemIsEditable);
    nameItem->setData(Qt::UserRole, newName);
    ui->tblSpecies->setItem(row, 0, nameItem);

    QTableWidgetItem *factorItem = new QTableWidgetItem(QString::number(newFactor, 'f', 2));
    factorItem->setFlags(factorItem->flags() | Qt::ItemIsEditable);
    ui->tblSpecies->setItem(row, 1, factorItem);
    ui->tblSpecies->blockSignals(false);

    emit speciesChanged();
}

void SpeciesDialog::btnDelete_clicked() {
    int row = ui->tblSpecies->currentRow();
    if (row < 0) {
        QMessageBox::information(this, "Удаление", "Выберите породу для удаления.");
        return;
    }

    QString name = ui->tblSpecies->item(row, 0)->text();
    int ret = QMessageBox::question(this, "Подтверждение",
                                    QString("Удалить породу '%1'?").arg(name),
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        m_db->removeSpecies(name);
        // Удаляем строку из таблицы (сигналы временно блокируем)
        ui->tblSpecies->blockSignals(true);
        ui->tblSpecies->removeRow(row);
        ui->tblSpecies->blockSignals(false);
        emit speciesChanged();
    }
}

void SpeciesDialog::btnReset_clicked() {
    int ret = QMessageBox::question(this, "Сброс",
                                    "Восстановить стандартный набор пород?\n"
                                    "Все текущие породы будут удалены и заменены на Сосна, Ель, Берёза, Дуб.",
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        m_db->resetToDefaults();
        loadSpeciesTable();
        emit speciesChanged();
    }
}

void SpeciesDialog::cellChanged(int row, int column) {
    // Получаем текущие данные из ячеек
    QTableWidgetItem *nameItem = ui->tblSpecies->item(row, 0);
    QTableWidgetItem *factorItem = ui->tblSpecies->item(row, 1);
    if (!nameItem || !factorItem) return;

    QString newName = nameItem->text().trimmed();
    if (newName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название породы не может быть пустым.");
        loadSpeciesTable(); // откатить несохранённое изменение
        return;
    }

    bool ok;
    double newFactor = factorItem->text().toDouble(&ok);
    if (!ok || newFactor <= 0.0 || newFactor > 1.0) {
        QMessageBox::warning(this, "Ошибка", "Видовое число должно быть числом от 0.01 до 1.00.");
        loadSpeciesTable();
        return;
    }

    // Получаем исходное имя, которое было загружено из БД (UserRole)
    QString oldName = nameItem->data(Qt::UserRole).toString();

    // Если имя или коэффициент действительно изменились
    if (oldName == newName && qAbs(m_db->formFactor(oldName) - newFactor) < 0.001) {
        // Ничего не изменилось, выходим
        return;
    }

    // Обновляем запись в БД
    if (!m_db->updateSpecies(oldName, newName, newFactor)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить изменения. Возможно, порода с таким именем уже существует.");
        loadSpeciesTable(); // откатить
        return;
    }

    // Обновляем сохранённое имя в UserRole для следующего сравнения
    ui->tblSpecies->blockSignals(true);
    nameItem->setData(Qt::UserRole, newName);
    // Также обновим значение видового числа на случай, если в БД произошло округление
    double savedFactor = m_db->formFactor(newName);
    factorItem->setText(QString::number(savedFactor, 'f', 2));
    ui->tblSpecies->blockSignals(false);

    emit speciesChanged();
}
