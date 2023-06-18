#pragma once

#include <QString>

class Car
{
public:
    Car() = default;
    ~Car() = default;

    const QString &getBrand() const;
    void setBrand(const QString &newBrand);

    const QString &getModel() const;
    void setModel(const QString &newModel);

    int getPrice() const;
    void setPrice(int newPrice);

    int getInvalidPrice() const;

    inline static const int invalidPrice = -1;
private:
    QString brand{};
    QString model{};
    int price = invalidPrice;
};
