#pragma once

//#include "tables.h"

#include "car.h"
#include "qbasesqlmodel.h"

#include <memory>
#include <thread>
#include <QtSql/QSqlQuery>

extern const char CarTableName[] = "cars";
extern const char CarFieldModel[] = "model";
extern const char CarFieldPrice[] = "price";
extern const char CarFieldBrand[] = "brand";

class QCarSqlModel : public QBaseSqlModel<Car, CarTableName, CarFieldModel, CarFieldPrice, CarFieldBrand>
{
public:
    QCarSqlModel();
    ~QCarSqlModel() = default;

    QVector<Car> select(const QString& fields = "*",  const QString& where = "",
    const QString &limit = "");

    void add(const QString &parameters);
    QVector<Car> first();
    QVector<Car> last();

    void add(const Car& newCar);
    void removeDyId(int id);
    void removeIf(const QString &condition);
    void removeAll();
    void clear();
    void update(int id, const QString &value, const QString &field);
    void updateIf(const QString &condition, const QString &field, const QString &value);

    Car parsingRowToCar(const QSqlQuery &query) override;
    QSqlQuery execQuery(const QString &queryStr);

    inline static const QString brandColumn = "brand";
    inline static const QString modelColumn = "model";
    inline static const QString priceColumn = "price";
    inline static const QString tableName = "cars";
private:
    void load();
private:

    std::unique_ptr<SqlModel> sqlModel;
};
