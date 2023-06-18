#pragma once

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQueryModel>

class SqlModel
{
    //Q_OBJECT

public:
    SqlModel(const QString &dbName);
    ~SqlModel();

    void migration(const QString &filePath);
    QSqlQuery execQuery(const QString &queryStr);
    void openDBConection(const QString &dbName);
private:
    void closeDBConsection();
private:
    QSqlDatabase db;
};
