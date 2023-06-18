#include "qcatlistmodel.h"

QCarListModel::QCarListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int QCarListModel::rowCount(const QModelIndex &parent) const
{
    return carNames.size();
}

QVariant QCarListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return carNames.at(index.row());
    }

    return QVariant();
}

bool QCarListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        carNames.at(index.row()) = value.toString();
    }
    emit dataChanged(index, index);
    return true;
}

std::vector<QString> &QCarListModel::getCarNames()
{
    emit dataChanged(this->index(0, 0), this->index(carNames.size(), 1));
    return carNames;
}

void QCarListModel::addCar(const Car &car)
{
    beginInsertRows(QModelIndex(), carNames.size(), carNames.size());
    carNames.push_back(car.getBrand() + " " + car.getModel());
    endInsertRows();
    emit dataChanged(this->index(0, 0), this->index(carNames.size(), 1));
}
