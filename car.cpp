#include "car.h"

const QString &Car::getBrand() const
{
    return brand;
}

void Car::setBrand(const QString &newBrand)
{
    brand = newBrand;
}

const QString &Car::getModel() const
{
    return model;
}

void Car::setModel(const QString &newModel)
{
    model = newModel;
}

int Car::getPrice() const
{
    return price;
}

void Car::setPrice(int newPrice)
{
    price = newPrice;
}
