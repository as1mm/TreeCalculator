#include "SpeciesDatabase.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QMap>

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
    insertDefaultSpecies();
}

// --------------------- Таблица species ---------------------
bool SpeciesDatabase::createSpeciesTable() {
    QSqlQuery query(m_db);
    const QString sql = "CREATE TABLE IF NOT EXISTS species ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "name TEXT NOT NULL UNIQUE, "
                        "form_factor REAL NOT NULL DEFAULT 0.5)";
    if (!query.exec(sql)) {
        qWarning() << "Ошибка создания species:" << query.lastError().text();
        return false;
    }
    return true;
}

bool SpeciesDatabase::insertDefaultSpecies() {
    QSqlQuery query(m_db);
    query.exec("SELECT COUNT(*) FROM species");
    if (query.next() && query.value(0).toInt() > 0) return true; // уже есть

    QMap<QString, double> defaults = {
        {"Сосна", 0.48}, {"Ель", 0.52}, {"Берёза", 0.43}, {"Дуб", 0.50}
    };
    query.prepare("INSERT OR IGNORE INTO species (name, form_factor) VALUES (?, ?)");
    for (auto it = defaults.constBegin(); it != defaults.constEnd(); ++it) {
        query.addBindValue(it.key());
        query.addBindValue(it.value());
        query.exec();
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

bool SpeciesDatabase::addSpecies(const QString &name, double formFactor) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO species (name, form_factor) VALUES (?, ?)");
    query.addBindValue(name);
    query.addBindValue(formFactor);
    return query.exec();
}

bool SpeciesDatabase::removeSpecies(const QString &name) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM species WHERE name = ?");
    query.addBindValue(name);
    return query.exec();
}

// --------------------- Таблица tree_records ---------------------
bool SpeciesDatabase::createTreeRecordsTable() {
    QSqlQuery query(m_db);
    const QString sql = "CREATE TABLE IF NOT EXISTS tree_records ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "species TEXT NOT NULL, "
                        "diameter_cm REAL NOT NULL, "
                        "height_m REAL NOT NULL, "
                        "form_factor REAL NOT NULL, "
                        "volume_m3 REAL NOT NULL, "
                        "created_at TEXT DEFAULT (datetime('now','localtime')))";
    return query.exec(sql);
}

bool SpeciesDatabase::addTreeRecord(const TreeRecord &record) {
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO tree_records (species, diameter_cm, height_m, form_factor, volume_m3) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(record.species);
    query.addBindValue(record.diameterCm);
    query.addBindValue(record.heightM);
    query.addBindValue(record.formFactor);
    query.addBindValue(record.volumeM3);
    if (!query.exec()) {
        qWarning() << "Ошибка добавления записи:" << query.lastError().text();
        return false;
    }
    return true;
}

QVector<TreeRecord> SpeciesDatabase::allTreeRecords() const {
    QVector<TreeRecord> records;
    QSqlQuery query(m_db);
    query.exec("SELECT id, species, diameter_cm, height_m, form_factor, volume_m3, created_at "
               "FROM tree_records ORDER BY id");
    while (query.next()) {
        TreeRecord rec;
        rec.id         = query.value(0).toInt();
        rec.species    = query.value(1).toString();
        rec.diameterCm = query.value(2).toDouble();
        rec.heightM    = query.value(3).toDouble();
        rec.formFactor = query.value(4).toDouble();
        rec.volumeM3   = query.value(5).toDouble();
        rec.createdAt  = QDateTime::fromString(query.value(6).toString(), Qt::ISODate);
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


bool SpeciesDatabase::updateSpecies(const QString &oldName, const QString &newName, double formFactor) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM species WHERE name = ?");
    query.addBindValue(oldName);
    if (!query.exec()) {
        qWarning() << "Ошибка удаления при обновлении:" << query.lastError().text();
        return false;
    }
    query.prepare("INSERT INTO species (name, form_factor) VALUES (?, ?)");
    query.addBindValue(newName);
    query.addBindValue(formFactor);
    if (!query.exec()) {
        qWarning() << "Ошибка вставки при обновлении:" << query.lastError().text();
        return false;
    }
    return true;
}

void SpeciesDatabase::resetToDefaults() {
    QSqlQuery query(m_db);
    query.exec("DELETE FROM species");
    insertDefaultSpecies();
}
