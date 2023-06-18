#include "qcarlistsqlinterface.h"

QCarListSqlInterface::QCarListSqlInterface()
{
    load();
}

QCarListModel &QCarListSqlInterface::getAllCarListSqlModel()//*
{
    return carListModel;
}

QCarSqlModel &QCarListSqlInterface::getCarSqlModel()
{
    return *carSqlModel.get();
}

void QCarListSqlInterface::loadDataFromDB()
{
    QVector<Car> temp = carSqlModel->select("model");
    qInfo() << temp.at(0).getModel();
    qInfo() << temp.at(0).getBrand();
    qInfo() << temp.at(0).getPrice();

    for(auto &car: carSqlModel->select())
        carListModel.addCar(car);
}

void QCarListSqlInterface::load()
{
    //threadLoad = std::move(std::jthread([&](){
        carSqlModel = std::make_unique<QCarSqlModel>();
        //carListModel = std::make_unique<QCarListModel>();
        loadDataFromDB();
   // }));
}
