#ifndef SPECIESDATABASE_H
#define SPECIESDATABASE_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QSqlDatabase>
#include <QDateTime>
#include <QDate>        // <-- добавлено для QDate в структуре Order

// структура для записи деревьев в таблицу (ведомость)
struct TreeRecord {
    int id = -1;
    QString species;
    double diameterCm = 0.0;
    double heightM = 0.0;
    double formFactor = 0.0;
    double volumeM3 = 0.0;
    double pricePerM3 = 0.0;
    QDateTime createdAt;
};

// одна позиция на складе
struct StockItem {
    int id = -1;
    QString species;
    QString type;    // "доска", "брус"
    double length;   // мм
    double width;
    double thickness;
    double volumePerUnit; // м³ одной штуки
    int quantity;         // штук на складе
    double pricePerUnit;  // цена за штуку
};

// заказчик
struct Customer {
    int id = -1;
    QString name;
    QString city;
    QString address;
};

// заказ
struct Order {
    int id = -1;
    int customerId;
    QDate date;
    QString status; // "новый", "частично", "выполнен"
};

// позиция в заказе
struct OrderItem {
    int id = -1;
    int orderId;
    QString species;
    QString type;
    double length;
    double width;
    double thickness;
    double volumeNeeded;   // потребный объём
    double volumeAllocated; // уже распределено со склада
};

// бд пород деревьев и их форм-факторы
class SpeciesDatabase {
public:
    SpeciesDatabase();
    ~SpeciesDatabase();

    // Справочник пород
    QStringList speciesList() const;
    double formFactor(const QString &speciesName) const;
    bool addSpecies(const QString &name, double formFactor, double price);
    bool removeSpecies(const QString &name);

    // Работа с записями ведомости
    bool addTreeRecord(const TreeRecord &record);
    QVector<TreeRecord> allTreeRecords() const;
    bool deleteTreeRecord(int id);
    double totalVolume() const;

    // Для изменения пород
    bool updateSpeciesFull(const QString &oldName, const QString &newName, double formFactor, double price);
    void resetToDefaults();
    void saveAsDefaults();

    // Получение цены
    double pricePerCubic(const QString &speciesName) const;
    double totalPrice() const;

    // Склад
    bool addStockItem(const QString &species, const QString &type, double length, double width,
                      double thickness, double volumePerUnit, int quantity, double pricePerUnit);
    bool removeStockItem(int id);
    QVector<StockItem> allStockItems() const;

    // Заказчики
    bool addCustomer(const QString &name, const QString &city, const QString &address);
    Customer customerById(int id) const;
    bool removeCustomer(int id);
    QVector<Customer> allCustomers() const;

    // Заказы и позиции
    int createOrder(int customerId, const QDate &date);
    bool addOrderItem(int orderId, const QString &species, const QString &type,
                      double length, double width, double thickness, double volumeNeeded);
    QVector<Order> allOrders() const;
    QVector<OrderItem> orderItems(int orderId) const;

    // Распределение
    bool allocateStock(int orderItemId, int stockItemId, double volume);

private:
    void initializeDatabase();
    bool createSpeciesTable();
    bool createTreeRecordsTable();
    bool insertDefaultSpecies();
    void migrateIfNeeded();
    void createDefaultSpeciesTable();
    void seedDefaultSpecies();
    void createStockTables();

    QSqlDatabase m_db;
};

#endif // SPECIESDATABASE_H
