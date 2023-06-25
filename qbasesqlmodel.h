#pragma once

#include <sqlmodel.h>

#include <memory>
#include <QString>
#include <string>
#include <QVector>
#include <QtSql/QSqlQuery>

template <class T, const char *TableName, const char *... Fields>
class QBaseSqlModel
{
public:
    QBaseSqlModel();

    virtual QVector<T> select(const QString& fields = "*",  const QString& where = "",
                        const QString &limit = "");

    virtual void add(const QString &parameters);
    virtual QVector<T> first();
    virtual QVector<T> last();

    virtual void add(const T& newCar);
    virtual void removeDyId(int id);
    virtual void removeIf(const QString &condition);
    virtual void removeAll();
    virtual void clear();
    virtual void update(int id, const QString &value, const QString &field);
    virtual void updateIf(const QString &condition, const QString &field, const QString &value);

    virtual T parsingRowToObject(const QSqlQuery &query);
    virtual QSqlQuery execQuery(const QString &queryStr);

    inline static const QString tableName = TableName;
private:
    void load();
private:

    std::unique_ptr<SqlModel> sqlModel;
};

template <class T, const char *TableName, const char*... Fields>
QBaseSqlModel<T, TableName, Fields...>::QBaseSqlModel()
{
    load();
}

template <class T, const char *TableName, const char*... Fields>
QVector<T> QBaseSqlModel<T, TableName, Fields...>::select(const QString &fields, const QString &where, const QString &limit)
{
    QString strBuilder = "SELECT " + fields + " FROM " + tableName;
    if (!where.isEmpty())
        strBuilder += " WHERE " + where;
    if (!limit.isEmpty())
        strBuilder += " LIMIT " + limit;

    QSqlQuery data = sqlModel->execQuery(strBuilder);
    QVector<T> temp;
    while(data.next())
        temp.push_back(parsingRowToObject(data));

    return temp;
}

template <class T, const char *TableName, const char*... Fields>
void QBaseSqlModel<T, TableName, Fields...>::add(const QString &parameters)
{
    sqlModel->execQuery("INSERT INTO Ts VALUES( " + parameters + " );");
}

template <class T, const char *TableName, const char*... Fields>
void QBaseSqlModel<T, TableName, Fields...>::add(const T &newT)
{
    const QString brand = newT.getBrand();
    const QString model = newT.getModel();
    const QString price = QString::number(newT.getPrice());

    sqlModel->execQuery(QString(R"(INSERT INTO %1(brand, model, price) VALUES('%2', '%3', %4))")
                            .arg(tableName, brand, model, price));
}

template <class T, const char *TableName, const char*... Fields>
void QBaseSqlModel<T, TableName, Fields...>::removeDyId(int id)
{
    sqlModel->execQuery(QString("DELETE FROM %1 WHERE id=%2;").arg(tableName).arg(id));
}

template <class T, const char *TableName, const char*... Fields>
void QBaseSqlModel<T, TableName, Fields...>::removeIf(const QString &condition)
{
    sqlModel->execQuery(QString("DELETE FROM %1 WHERE %2;").arg(tableName, condition));
}

template <class T, const char *TableName, const char*... Fields>
void QBaseSqlModel<T, TableName, Fields...>::removeAll()
{
    sqlModel->execQuery(QString("DELETE FROM %1 WHERE TRUE;").arg(tableName));
}

template <class T, const char *TableName, const char*... Fields>
void QBaseSqlModel<T, TableName, Fields...>::clear()
{
    removeAll();
}

template <class T, const char *TableName, const char*... Fields>
void QBaseSqlModel<T, TableName, Fields...>::update(int id, const QString &value, const QString &field)
{
    sqlModel->execQuery(QString("UPDATE %1 SET %2 = %3 WHERE id = %4;").arg(tableName, field, value).arg(id));
}

template <class T, const char *TableName, const char*... Fields>
void QBaseSqlModel<T, TableName, Fields...>::updateIf(const QString &condition, const QString &field, const QString &value)
{
    sqlModel->execQuery(QString("UPDATE %1 SET %2 = %3 WHERE %4;").arg(tableName, field, value, condition));
}

template <class T, const char *TableName, const char*... Fields>
T QBaseSqlModel<T, TableName, Fields...>::parsingRowToT(const QSqlQuery &query)
{
    QString TBrand;
    QString TModel;
    int TPrice = T::invalidPrice;

    if (query.value(brandColumn).isValid())
        TBrand = query.value(brandColumn).toString();
    if (query.value(modelColumn).isValid())
        TModel = query.value(modelColumn).toString();
    if (query.value(priceColumn).isValid())
        TPrice = query.value(priceColumn).toInt();

    T T;
    T.setBrand(TBrand);
    T.setModel(TModel);
    T.setPrice(TPrice);

    return T;
}

template <class T, const char *TableName, const char*... Fields>
QSqlQuery QBaseSqlModel<T, TableName, Fields...>::execQuery(const QString &queryStr)
{
    return sqlModel->execQuery(queryStr);
}

template <class T, const char *TableName, const char*... Fields>
void QBaseSqlModel<T, TableName, Fields...>::load()
{
    sqlModel = std::make_unique<SqlModel>("D:/Qt Projects/build-meneger-Desktop_Qt_6_4_0_MinGW_64_bit-Debug/debug/TsDB.db");
    sqlModel->migration("D:/Qt Projects/build-meneger-Desktop_Qt_6_4_0_MinGW_64_bit-Debug/debug/TsDBMigration.sql");
}
