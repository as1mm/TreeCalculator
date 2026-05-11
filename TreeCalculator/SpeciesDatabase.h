#ifndef SPECIESDATABASE_H
#define SPECIESDATABASE_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QSqlDatabase>
#include <QDateTime>

// структура для записи деревьев в таблицу (ведомость)
struct TreeRecord {
    int id = -1;
    QString species;
    double diameterCm = 0.0;
    double heightM = 0.0;
    double formFactor = 0.0;
    double volumeM3 = 0.0;
    QDateTime createdAt;
};

// бд пород деревьев и их форм-факторы
class SpeciesDatabase {
public:
    SpeciesDatabase();
    ~SpeciesDatabase();

    // Справочник пород
    QStringList speciesList() const;
    double formFactor(const QString &speciesName) const;
    bool addSpecies(const QString &name, double formFactor);
    bool removeSpecies(const QString &name);

    // Работа с записями ведомости
    bool addTreeRecord(const TreeRecord &record);
    QVector<TreeRecord> allTreeRecords() const;
    bool deleteTreeRecord(int id);
    double totalVolume() const;

    // Для изменения пород
    bool updateSpecies(const QString &oldName, const QString &newName, double formFactor);
    void resetToDefaults();

private:
    void initializeDatabase();
    bool createSpeciesTable();
    bool createTreeRecordsTable();
    bool insertDefaultSpecies();

    QSqlDatabase m_db;
};

#endif // SPECIESDATABASE_H
