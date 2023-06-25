#pragma once
//
//#include "qbasesqlmodel.h"
//#include "car.h"
//
//extern const char CarTableName[] = "cars";
//extern const char CarFieldModel[] = "model";
//extern const char CarFieldPrice[] = "price";
//extern const char CarFieldBrand[] = "brand";

//using QCarTableSqlModel;
QBaseSqlModel<Car, CarTableName, CarFieldModel, CarFieldPrice, CarFieldBrand>;
