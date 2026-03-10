#ifndef DELAYMODEL_H
#define DELAYMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "exchangeables.h"

class DelayModel : public QAbstractListModel
{
    Q_OBJECT
public:
    DelayModel(QObject* parent = Q_NULLPTR, VoltDelay* = nullptr);
    ~DelayModel();

private:
    VoltDelay *vd;
    std::vector<int> delayData = {300, 300, 500, 500, 400, 400};
    std::vector<int> voltData = {0, 600, 10, 1000, 10, 0};
private:
    void sendCommand();

    // QAbstractItemModel interface
public:
    /**
     * @brief rowCount возвращает число управляющих задержек
     * @param parent
     * @return число управляющих задержек
     */
    virtual int columnCount(const QModelIndex& parent) const override;
    /**
     * @brief rowCount возвращает число управляющих задержек
     * @param parent
     * @return число управляющих задержек
     */
    virtual int rowCount(const QModelIndex& parent) const override;

    /**
     * @brief data возращает данные по индексу модели index и роли role
     * @param index
     * @param role
     * @return данные по индексу модели index и роли role
     */
    virtual QVariant data(const QModelIndex& index, int role) const override;

    /**
     * @brief setData устанавливает значение value в модель по индексу index и роли role
     * @param index
     * @param value
     * @param role
     * @return удалось ли установить значение
     */
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

signals:
    /**
     * @brief sendDataSignal сигнализирует об отправке пакета данных в worker
     * @param message
     */
    void sendDataSignal(VoltDelay* vd);
};

#endif // DELAYMODEL_H
