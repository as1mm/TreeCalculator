#include "SpeciesDatabase.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QMap>
#include <QPair>
#include <cmath>

// ======================================================================
// Конструктор / деструктор
// ======================================================================
SpeciesDatabase::SpeciesDatabase() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(QCoreApplication::applicationDirPath() + "/species.db");

    if (!m_db.open()) {
        qWarning() << "Ошибка открытия БД:" << m_db.lastError().text();
        return;
    }

    initializeDatabase();
}

SpeciesDatabase::~SpeciesDatabase() {
    if (m_db.isOpen()) m_db.close();
}

void SpeciesDatabase::initializeDatabase() {
    createSpeciesTable();
    createTreeRecordsTable();
    createDefaultSpeciesTable();
    createStockTables();               // новые таблицы (склад, заказчики, заказы)
    migrateIfNeeded();                 // добавляет price_per_m3, если старая БД
    seedDefaultSpecies();              // заполняет default_species заводскими значениями

    // При первом запуске (species пуста) копируем заводские породы в species
    QSqlQuery q(m_db);
    q.exec("SELECT COUNT(*) FROM species");
    if (q.next() && q.value(0).toInt() == 0) {
        resetToDefaults();             // копирует из default_species в species
    }
}

// ======================================================================
// Миграция (добавление столбца price_per_m3 в старых БД)
// ======================================================================
void SpeciesDatabase::migrateIfNeeded() {
    // Проверяем species
    QSqlQuery query(m_db);
    query.exec("PRAGMA table_info(species)");
    bool hasPrice = false;
    while (query.next()) {
        if (query.value(1).toString() == "price_per_m3") {
            hasPrice = true;
            break;
        }
    }
    if (!hasPrice) {
        QSqlQuery alter(m_db);
        alter.exec("ALTER TABLE species ADD COLUMN price_per_m3 REAL NOT NULL DEFAULT 0.0");
    }

    // Проверяем tree_records
    query.exec("PRAGMA table_info(tree_records)");
    hasPrice = false;
    while (query.next()) {
        if (query.value(1).toString() == "price_per_m3") {
            hasPrice = true;
            break;
        }
    }
    if (!hasPrice) {
        QSqlQuery alter(m_db);
        alter.exec("ALTER TABLE tree_records ADD COLUMN price_per_m3 REAL NOT NULL DEFAULT 0.0");
    }
}

// ======================================================================
// Таблица species (справочник пород)
// ======================================================================
bool SpeciesDatabase::createSpeciesTable() {
    QSqlQuery query(m_db);
    const QString sql = "CREATE TABLE IF NOT EXISTS species ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "name TEXT NOT NULL UNIQUE, "
                        "form_factor REAL NOT NULL DEFAULT 0.5, "
                        "price_per_m3 REAL NOT NULL DEFAULT 0.0)";
    if (!query.exec(sql)) {
        qWarning() << "Ошибка создания species:" << query.lastError().text();
        return false;
    }
    return true;
}

QStringList SpeciesDatabase::speciesList() const {
    QStringList list;
    QSqlQuery query(m_db);
    query.exec("SELECT name FROM species ORDER BY name");
    while (query.next()) list << query.value(0).toString();
    return list;
}

double SpeciesDatabase::formFactor(const QString &speciesName) const {
    QSqlQuery query(m_db);
    query.prepare("SELECT form_factor FROM species WHERE name = ?");
    query.addBindValue(speciesName);
    if (query.exec() && query.next()) return query.value(0).toDouble();
    return 0.0;
}

bool SpeciesDatabase::addSpecies(const QString &name, double formFactor, double price) {
    if (name.trimmed().isEmpty()) return false;
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO species (name, form_factor, price_per_m3) VALUES (?, ?, ?)");
    query.addBindValue(name.trimmed());
    query.addBindValue(formFactor);
    query.addBindValue(price);
    if (!query.exec()) {
        qWarning() << "Не удалось добавить породу:" << query.lastError().text();
        return false;
    }
    return true;
}

bool SpeciesDatabase::removeSpecies(const QString &name) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM species WHERE name = ?");
    query.addBindValue(name);
    return query.exec();
}

bool SpeciesDatabase::updateSpeciesFull(const QString &oldName, const QString &newName,
                                        double formFactor, double price) {
    if (newName.trimmed().isEmpty()) return false;
    if (oldName == newName) {
        QSqlQuery query(m_db);
        query.prepare("UPDATE species SET form_factor=?, price_per_m3=? WHERE name=?");
        query.addBindValue(formFactor);
        query.addBindValue(price);
        query.addBindValue(oldName);
        return query.exec();
    }
    // Проверка, не занято ли новое имя
    QSqlQuery check(m_db);
    check.prepare("SELECT COUNT(*) FROM species WHERE name=?");
    check.addBindValue(newName);
    if (check.exec() && check.next() && check.value(0).toInt() > 0) {
        qWarning() << "Порода с именем" << newName << "уже существует";
        return false;
    }
    // Удаление старой, вставка новой
    QSqlQuery del(m_db);
    del.prepare("DELETE FROM species WHERE name=?");
    del.addBindValue(oldName);
    if (!del.exec()) return false;

    QSqlQuery ins(m_db);
    ins.prepare("INSERT INTO species (name, form_factor, price_per_m3) VALUES (?, ?, ?)");
    ins.addBindValue(newName);
    ins.addBindValue(formFactor);
    ins.addBindValue(price);
    return ins.exec();
}

// ======================================================================
// Таблица default_species (эталонный набор пород для сброса)
// ======================================================================
void SpeciesDatabase::createDefaultSpeciesTable() {
    QSqlQuery query(m_db);
    const QString sql = "CREATE TABLE IF NOT EXISTS default_species ("
                        "name TEXT NOT NULL UNIQUE, "
                        "form_factor REAL NOT NULL DEFAULT 0.5, "
                        "price_per_m3 REAL NOT NULL DEFAULT 0.0)";
    query.exec(sql);
}

void SpeciesDatabase::seedDefaultSpecies() {
    QSqlQuery query(m_db);
    query.exec("SELECT COUNT(*) FROM default_species");
    if (query.next() && query.value(0).toInt() > 0) return; // уже заполнена

    QMap<QString, QPair<double, double>> factory;
    factory["Сосна"]  = {0.48, 5000.0};
    factory["Ель"]    = {0.42, 4500.0};   // ты указал 0.42, оставляю как у тебя
    factory["Берёза"] = {0.66, 4000.0};
    factory["Дуб"]    = {0.55, 10000.0};

    query.prepare("INSERT INTO default_species (name, form_factor, price_per_m3) VALUES (?, ?, ?)");
    for (auto it = factory.constBegin(); it != factory.constEnd(); ++it) {
        query.addBindValue(it.key());
        query.addBindValue(it.value().first);
        query.addBindValue(it.value().second);
        query.exec();
    }
}

void SpeciesDatabase::saveAsDefaults() {
    QSqlQuery query(m_db);
    query.exec("DELETE FROM default_species");
    query.exec("INSERT INTO default_species (name, form_factor, price_per_m3) "
               "SELECT name, form_factor, price_per_m3 FROM species");
}

void SpeciesDatabase::resetToDefaults() {
    QSqlQuery query(m_db);
    query.exec("DELETE FROM species");
    query.exec("INSERT INTO species (name, form_factor, price_per_m3) "
               "SELECT name, form_factor, price_per_m3 FROM default_species");
}

// ======================================================================
// Таблица tree_records (ведомость объёмов)
// ======================================================================
bool SpeciesDatabase::createTreeRecordsTable() {
    QSqlQuery query(m_db);
    const QString sql = "CREATE TABLE IF NOT EXISTS tree_records ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "species TEXT NOT NULL, "
                        "diameter_cm REAL NOT NULL, "
                        "height_m REAL NOT NULL, "
                        "form_factor REAL NOT NULL, "
                        "volume_m3 REAL NOT NULL, "
                        "price_per_m3 REAL NOT NULL DEFAULT 0.0, "
                        "created_at TEXT DEFAULT (datetime('now','localtime')))";
    return query.exec(sql);
}

bool SpeciesDatabase::addTreeRecord(const TreeRecord &record) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO tree_records (species, diameter_cm, height_m, form_factor, volume_m3, price_per_m3) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(record.species);
    query.addBindValue(record.diameterCm);
    query.addBindValue(record.heightM);
    query.addBindValue(record.formFactor);
    query.addBindValue(record.volumeM3);
    query.addBindValue(record.pricePerM3);
    if (!query.exec()) {
        qWarning() << "Ошибка добавления записи:" << query.lastError().text();
        return false;
    }
    return true;
}

QVector<TreeRecord> SpeciesDatabase::allTreeRecords() const {
    QVector<TreeRecord> records;
    QSqlQuery query(m_db);
    query.exec("SELECT id, species, diameter_cm, height_m, form_factor, volume_m3, price_per_m3, created_at "
               "FROM tree_records ORDER BY id");
    while (query.next()) {
        TreeRecord rec;
        rec.id         = query.value(0).toInt();
        rec.species    = query.value(1).toString();
        rec.diameterCm = query.value(2).toDouble();
        rec.heightM    = query.value(3).toDouble();
        rec.formFactor = query.value(4).toDouble();
        rec.volumeM3   = query.value(5).toDouble();
        rec.pricePerM3 = query.value(6).toDouble();
        rec.createdAt  = QDateTime::fromString(query.value(7).toString(), Qt::ISODate);
        records.append(rec);
    }
    return records;
}

bool SpeciesDatabase::deleteTreeRecord(int id) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM tree_records WHERE id = ?");
    query.addBindValue(id);
    return query.exec();
}

double SpeciesDatabase::totalVolume() const {
    QSqlQuery query(m_db);
    query.exec("SELECT COALESCE(SUM(volume_m3), 0) FROM tree_records");
    if (query.next()) return query.value(0).toDouble();
    return 0.0;
}

double SpeciesDatabase::pricePerCubic(const QString &speciesName) const {
    QSqlQuery query(m_db);
    query.prepare("SELECT price_per_m3 FROM species WHERE name = ?");
    query.addBindValue(speciesName);
    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

double SpeciesDatabase::totalPrice() const {
    QSqlQuery query(m_db);
    query.exec("SELECT COALESCE(SUM(volume_m3 * price_per_m3), 0) FROM tree_records");
    if (query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

// ======================================================================
// Таблицы склада, заказчиков, заказов
// ======================================================================
void SpeciesDatabase::createStockTables() {
    QSqlQuery q(m_db);

    q.exec("CREATE TABLE IF NOT EXISTS customers ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
           "name TEXT NOT NULL, "
           "city TEXT, "
           "address TEXT)");

    q.exec("CREATE TABLE IF NOT EXISTS stock ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
           "species TEXT NOT NULL, "
           "type TEXT NOT NULL, "
           "length REAL NOT NULL, "
           "width REAL NOT NULL, "
           "thickness REAL NOT NULL, "
           "volume_per_unit REAL NOT NULL, "
           "quantity INTEGER NOT NULL DEFAULT 0, "
           "price_per_unit REAL NOT NULL DEFAULT 0.0)");

    q.exec("CREATE TABLE IF NOT EXISTS orders ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
           "customer_id INTEGER NOT NULL, "
           "date TEXT NOT NULL, "
           "status TEXT NOT NULL DEFAULT 'новый', "
           "FOREIGN KEY (customer_id) REFERENCES customers(id))");

    q.exec("CREATE TABLE IF NOT EXISTS order_items ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
           "order_id INTEGER NOT NULL, "
           "species TEXT NOT NULL, "
           "type TEXT NOT NULL, "
           "length REAL NOT NULL, "
           "width REAL NOT NULL, "
           "thickness REAL NOT NULL, "
           "volume_needed REAL NOT NULL, "
           "volume_allocated REAL NOT NULL DEFAULT 0.0, "
           "FOREIGN KEY (order_id) REFERENCES orders(id))");
}

// ----------------- Склад -----------------
bool SpeciesDatabase::addStockItem(const QString &species, const QString &type,
                                   double length, double width, double thickness,
                                   double volumePerUnit, int quantity, double pricePerUnit) {
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO stock (species, type, length, width, thickness, volume_per_unit, quantity, price_per_unit) "
              "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    q.addBindValue(species);
    q.addBindValue(type);
    q.addBindValue(length);
    q.addBindValue(width);
    q.addBindValue(thickness);
    q.addBindValue(volumePerUnit);
    q.addBindValue(quantity);
    q.addBindValue(pricePerUnit);
    return q.exec();
}

bool SpeciesDatabase::removeStockItem(int id) {
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM stock WHERE id = ?");
    q.addBindValue(id);
    return q.exec();
}

QVector<StockItem> SpeciesDatabase::allStockItems() const {
    QVector<StockItem> items;
    QSqlQuery q(m_db);
    q.exec("SELECT id, species, type, length, width, thickness, volume_per_unit, quantity, price_per_unit FROM stock");
    while (q.next()) {
        StockItem it;
        it.id            = q.value(0).toInt();
        it.species       = q.value(1).toString();
        it.type          = q.value(2).toString();
        it.length        = q.value(3).toDouble();
        it.width         = q.value(4).toDouble();
        it.thickness     = q.value(5).toDouble();
        it.volumePerUnit = q.value(6).toDouble();
        it.quantity      = q.value(7).toInt();
        it.pricePerUnit  = q.value(8).toDouble();
        items.append(it);
    }
    return items;
}

// ----------------- Заказчики -----------------
bool SpeciesDatabase::addCustomer(const QString &name, const QString &city, const QString &address) {
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO customers (name, city, address) VALUES (?, ?, ?)");
    q.addBindValue(name);
    q.addBindValue(city);
    q.addBindValue(address);
    return q.exec();
}

Customer SpeciesDatabase::customerById(int id) const {
    Customer c;
    QSqlQuery q(m_db);
    q.prepare("SELECT id, name, city, address FROM customers WHERE id = ?");
    q.addBindValue(id);
    if (q.exec() && q.next()) {
        c.id      = q.value(0).toInt();
        c.name    = q.value(1).toString();
        c.city    = q.value(2).toString();
        c.address = q.value(3).toString();
    }
    return c;
}

bool SpeciesDatabase::removeCustomer(int id) {
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM customers WHERE id = ?");
    q.addBindValue(id);
    return q.exec();
}

QVector<Customer> SpeciesDatabase::allCustomers() const {
    QVector<Customer> list;
    QSqlQuery q(m_db);
    q.exec("SELECT id, name, city, address FROM customers ORDER BY name");
    while (q.next()) {
        Customer c;
        c.id      = q.value(0).toInt();
        c.name    = q.value(1).toString();
        c.city    = q.value(2).toString();
        c.address = q.value(3).toString();
        list.append(c);
    }
    return list;
}

// ----------------- Заказы и позиции -----------------
int SpeciesDatabase::createOrder(int customerId, const QDate &date) {
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO orders (customer_id, date, status) VALUES (?, ?, 'новый')");
    q.addBindValue(customerId);
    q.addBindValue(date.toString(Qt::ISODate));
    if (!q.exec()) {
        qWarning() << "Ошибка создания заказа:" << q.lastError().text();
        return -1;
    }
    return q.lastInsertId().toInt();
}

bool SpeciesDatabase::addOrderItem(int orderId, const QString &species, const QString &type,
                                   double length, double width, double thickness, double volumeNeeded) {
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO order_items (order_id, species, type, length, width, thickness, volume_needed) "
              "VALUES (?, ?, ?, ?, ?, ?, ?)");
    q.addBindValue(orderId);
    q.addBindValue(species);
    q.addBindValue(type);
    q.addBindValue(length);
    q.addBindValue(width);
    q.addBindValue(thickness);
    q.addBindValue(volumeNeeded);
    return q.exec();
}

QVector<Order> SpeciesDatabase::allOrders() const {
    QVector<Order> orders;
    QSqlQuery q(m_db);
    q.exec("SELECT id, customer_id, date, status FROM orders ORDER BY id");
    while (q.next()) {
        Order o;
        o.id         = q.value(0).toInt();
        o.customerId = q.value(1).toInt();
        o.date       = QDate::fromString(q.value(2).toString(), Qt::ISODate);
        o.status     = q.value(3).toString();
        orders.append(o);
    }
    return orders;
}

QVector<OrderItem> SpeciesDatabase::orderItems(int orderId) const {
    QVector<OrderItem> items;
    QSqlQuery q(m_db);
    q.prepare("SELECT id, species, type, length, width, thickness, volume_needed, volume_allocated "
              "FROM order_items WHERE order_id = ?");
    q.addBindValue(orderId);
    if (q.exec()) {
        while (q.next()) {
            OrderItem oi;
            oi.id              = q.value(0).toInt();
            oi.orderId         = orderId;
            oi.species         = q.value(1).toString();
            oi.type            = q.value(2).toString();
            oi.length          = q.value(3).toDouble();
            oi.width           = q.value(4).toDouble();
            oi.thickness       = q.value(5).toDouble();
            oi.volumeNeeded    = q.value(6).toDouble();
            oi.volumeAllocated = q.value(7).toDouble();
            items.append(oi);
        }
    }
    return items;
}

// ----------------- Распределение (заглушка) -----------------
bool SpeciesDatabase::allocateStock(int orderItemId, int stockItemId, double volume) {
    // Проверяем наличие на складе
    QSqlQuery q(m_db);
    q.prepare("SELECT quantity, volume_per_unit FROM stock WHERE id = ?");
    q.addBindValue(stockItemId);
    if (!q.exec() || !q.next()) return false;

    int qty = q.value(0).toInt();
    double volPerUnit = q.value(1).toDouble();
    int neededPieces = static_cast<int>(std::ceil(volume / volPerUnit));
    if (neededPieces > qty) return false;   // недостаточно штук

    // Уменьшаем склад
    QSqlQuery upd(m_db);
    upd.prepare("UPDATE stock SET quantity = quantity - ? WHERE id = ?");
    upd.addBindValue(neededPieces);
    upd.addBindValue(stockItemId);
    if (!upd.exec()) return false;

    // Увеличиваем allocated в order_items
    upd.prepare("UPDATE order_items SET volume_allocated = volume_allocated + ? WHERE id = ?");
    upd.addBindValue(volume);
    upd.addBindValue(orderItemId);
    return upd.exec();
}
