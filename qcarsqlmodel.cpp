#include "qcarsqlmodel.h"

#include <string>

QCarSqlModel::QCarSqlModel()
{
    load();
}

QVector<Car> QCarSqlModel::select(const QString &fields, const QString &where, const QString &limit)
{
    QString strBuilder = "SELECT " + fields + " FROM " + tableName;
    if (!where.isEmpty())
        strBuilder += " WHERE " + where;
    if (!limit.isEmpty())
        strBuilder += " LIMIT " + limit;

    QSqlQuery data = sqlModel->execQuery(strBuilder);
    QVector<Car> temp;
    while(data.next())
        temp.push_back(parsingRowToCar(data));

    return temp;
}

void QCarSqlModel::add(const QString &parameters)
{
    sqlModel->execQuery("INSERT INTO cars VALUES( " + parameters + " );");
}

void QCarSqlModel::add(const Car &newCar)
{
    const QString brand = newCar.getBrand();
    const QString model = newCar.getModel();
    const QString price = QString::number(newCar.getPrice());

    sqlModel->execQuery(QString(R"(INSERT INTO %1(brand, model, price) VALUES('%2', '%3', %4))")
                            .arg(tableName, brand, model, price));
}

void QCarSqlModel::removeDyId(int id)
{
    sqlModel->execQuery(QString("DELETE FROM %1 WHERE id=%2;").arg(tableName).arg(id));
}

void QCarSqlModel::removeIf(const QString &condition)
{
    sqlModel->execQuery(QString("DELETE FROM %1 WHERE %2;").arg(tableName, condition));
}

void QCarSqlModel::removeAll()
{
    sqlModel->execQuery(QString("DELETE FROM %1 WHERE TRUE;").arg(tableName));
}

void QCarSqlModel::clear()
{
    removeAll();
}

void QCarSqlModel::update(int id, const QString &value, const QString &field)
{
    sqlModel->execQuery(QString("UPDATE %1 SET %2 = %3 WHERE id = %4;").arg(tableName, field, value).arg(id));
}

void QCarSqlModel::updateIf(const QString &condition, const QString &field, const QString &value)
{
    sqlModel->execQuery(QString("UPDATE %1 SET %2 = %3 WHERE %4;").arg(tableName, field, value, condition));
}

Car QCarSqlModel::parsingRowToCar(const QSqlQuery &query)
{
    QString carBrand;
    QString carModel;
    int carPrice = Car::invalidPrice;

    if (query.value(brandColumn).isValid())
        carBrand = query.value(brandColumn).toString();
    if (query.value(modelColumn).isValid())
        carModel = query.value(modelColumn).toString();
    if (query.value(priceColumn).isValid())
        carPrice = query.value(priceColumn).toInt();

    Car car;
    car.setBrand(carBrand);
    car.setModel(carModel);
    car.setPrice(carPrice);

    return car;
}

QSqlQuery QCarSqlModel::execQuery(const QString &queryStr)
{
    return sqlModel->execQuery(queryStr);
}

void QCarSqlModel::load()
{
    sqlModel = std::make_unique<SqlModel>("D:/Qt Projects/build-meneger-Desktop_Qt_6_4_0_MinGW_64_bit-Debug/debug/CarsDB.db");
    sqlModel->migration("D:/Qt Projects/build-meneger-Desktop_Qt_6_4_0_MinGW_64_bit-Debug/debug/CarsDBMigration.sql");
}
