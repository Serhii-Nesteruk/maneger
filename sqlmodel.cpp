#include "sqlmodel.h"

#include <QSqlError>
#include <fstream>
#include <sstream>

SqlModel::SqlModel(const QString& dbName)
{
    openDBConection(dbName);
}

SqlModel::~SqlModel()
{
    closeDBConsection();
}

void SqlModel::migration(const QString &filePath)
{
    std::ifstream file;
    file.open(filePath.toStdString());

    if (!file.is_open())
    {
        qFatal() << "file not found!";
        std::terminate();
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    file.close();

    QString stringBuffer = buffer.str().c_str();
    QStringList queries = stringBuffer.split(';');

    for (QString &query : queries)
        if (!query.isEmpty())
            execQuery(query);
}

QSqlQuery SqlModel::execQuery(const QString &queryStr)
{
    if (!db.isOpen())
        qFatal() << "DB is not open";
    QSqlQuery query(db);
    if (!query.exec(queryStr)) {
        qInfo() << query.lastError().text();
        qFatal() << "Query error!!!";
    }
    return query;
}

void SqlModel::openDBConection(const QString &dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE", "SQLITE");
    db.setDatabaseName(dbName);
    db.open();

    if (!db.isOpen())
    {
        qFatal() << "ERROR!!!";
        return;
    }
}

void SqlModel::closeDBConsection()
{
    db.close();
}
