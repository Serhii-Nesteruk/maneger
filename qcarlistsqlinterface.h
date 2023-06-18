#pragma once

#include "qcatlistmodel.h"
#include "qcarsqlmodel.h"

#include <thread>

class QCarListSqlInterface
{

public:
    QCarListSqlInterface();
    ~QCarListSqlInterface() = default;

    QCarListModel &getAllCarListSqlModel();
    QCarSqlModel &getCarSqlModel();
private:
    void loadDataFromDB();
    void load();
private:
    //std::unique_ptr<QCarListModel> carListModel;
    QCarListModel carListModel;//TODO: add unique_ptr
    std::unique_ptr<QCarSqlModel> carSqlModel;
    std::jthread threadLoad;
};
