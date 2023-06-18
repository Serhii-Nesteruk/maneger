#pragma once

#include "car.h"

#include <QAbstractListModel>
#include <vector>

class QCarListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit QCarListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    std::vector<QString> &getCarNames();
    void addCar(const Car& car);
private:
    std::vector<QString> carNames{};
};
