#include "delaymodel.h"


DelayModel::DelayModel(QObject* parent) :
    QAbstractListModel(parent)
{

}

DelayModel::~DelayModel()
{
    qDebug() << "Destroy DelayModel";
}

int DelayModel::rowCount(const QModelIndex&) const
{
    return delayData.size();
}

QVariant DelayModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    switch (role) {
    case Qt::DisplayRole:
        return delayData.at(row);
    }
    return QVariant();
}

bool DelayModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        int row = index.row();
        if (row >= -1 && row < rowCount(QModelIndex()))
        {
            if (row == -1)
                sendCommand();
            else
                delayData[row] = value.toInt();
            return true;
        }
    }
    return false;
}

void DelayModel::sendCommand()
{
    emit sendDataSignal(delayData);
}

