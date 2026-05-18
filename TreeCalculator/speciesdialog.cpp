#include "speciesdialog.h"
#include "ui_speciesdialog.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>

SpeciesDialog::SpeciesDialog(SpeciesDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpeciesDialog),
    m_db(db)
{
    ui->setupUi(this);

    setWindowTitle("Редактор пород");

    // Лейауты (для того, чтобы кнопки и таблицы растягивались при увеличении окна)
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(ui->tblSpecies);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(ui->btnAdd);
    btnLayout->addWidget(ui->btnDelete);
    btnLayout->addStretch();
    btnLayout->addWidget(ui->btnReset);
    mainLayout->addLayout(btnLayout);
    ui->tblSpecies->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Настройка таблицы
    ui->tblSpecies->setColumnCount(3);
    QStringList headers = { "Название", "Видовое число", "Цена за м³" };
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

        // Цена за куб
        double price = m_db->pricePerCubic(name);
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(price, 'f', 2));
        priceItem->setFlags(priceItem->flags() | Qt::ItemIsEditable);
        ui->tblSpecies->setItem(row, 2, priceItem);
    }
    ui->tblSpecies->blockSignals(false);
}

void SpeciesDialog::btnAdd_clicked() {
    bool ok;
    QString name = QInputDialog::getText(this, "Новая порода", "Название:", QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty()) return;

    double factor = QInputDialog::getDouble(this, "Новая порода", "Видовое число (0.01–1.00):", 0.50, 0.01, 1.00, 2, &ok);
    if (!ok) return;

    double price = QInputDialog::getDouble(this, "Новая порода", "Цена за кубометр (руб.):", 0.0, 0.0, 1000000.0, 2, &ok);
    if (!ok) return;

    if (!m_db->addSpecies(name, factor, price)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить породу. Возможно, такое имя уже существует.");
        return;
    }

    ui->tblSpecies->blockSignals(true);
    loadSpeciesTable();
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
    QTableWidgetItem *priceItem  = ui->tblSpecies->item(row, 2);

    if (!nameItem || !factorItem || !priceItem) return;

    QString newName = nameItem->text().trimmed();
    if (newName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название породы не может быть пустым.");
        loadSpeciesTable(); // откатываем несохранённые изменения
        return;
    }

    bool okFactor, okPrice;
    double newFactor = factorItem->text().toDouble(&okFactor);
    double newPrice  = priceItem->text().toDouble(&okPrice);

    if (!okFactor || newFactor <= 0.0 || newFactor > 1.0) {
        QMessageBox::warning(this, "Ошибка", "Видовое число должно быть от 0.01 до 1.00.");
        loadSpeciesTable();
        return;
    }
    if (!okPrice || newPrice < 0.0) {
        QMessageBox::warning(this, "Ошибка", "Цена не может быть отрицательной.");
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
    if (!m_db->updateSpeciesFull(oldName, newName, newFactor, newPrice)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить изменения. Возможно, порода с таким именем уже существует.");
        loadSpeciesTable(); // откат
        return;
    }

    // Обновляем сохранённое имя в UserRole для следующего сравнения
    ui->tblSpecies->blockSignals(true);
    nameItem->setData(Qt::UserRole, newName);
    // Также обновим значение видового числа на случай, если в БД произошло округление
    double savedFactor = m_db->formFactor(newName);
    double savedPrice  = m_db->pricePerCubic(newName);
    factorItem->setText(QString::number(savedFactor, 'f', 2));
    priceItem->setText (QString::number(savedPrice,  'f', 2));
    ui->tblSpecies->blockSignals(false);

    emit speciesChanged();
}
