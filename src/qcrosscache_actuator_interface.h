#pragma once

#include <QObject>
#include <QVariant>
#include "./qcrosscache_global.h"

namespace QCrossCache {

class ActuatorInterfaceItem;
class Server;


//!
//! \brief The ActuatorInterface class
//!
class Q_CROSSCACHE_EXPORT ActuatorInterface : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief ActuatorInterface
    //! \param parent
    //!
    Q_INVOKABLE explicit ActuatorInterface(QObject *parent = nullptr);

    //!
    //! \brief ActuatorInterface
    //! \param groupData
    //! \param parent
    //!
    Q_INVOKABLE explicit ActuatorInterface(Server*server, const QByteArray &dataGroup);

    //!
    //!
    ~ActuatorInterface();

    //!
    //! \brief server
    //! \return
    //!
    virtual Server*server();

    //!
    //! \brief dataGroup
    //! \return
    //!
    virtual QByteArray &dataGroup()const;

    //!
    //! \brief connect
    //! \return
    //!
    virtual bool connect();

    //!
    //! \brief disconnect
    //! \return
    //!
    virtual bool disconnect();

    //!
    //! \brief isConnected
    //! \return
    //!
    virtual bool isConnected();

    //!
    //! \brief clear
    //! \return
    //!
    virtual bool clear();

    //!
    //! \brief exists
    //! \param key
    //! \return
    //!
    virtual bool exists(const QByteArray&key);

    //!
    //! \brief put
    //! \param key
    //! \param data
    //! \return
    //!
    virtual bool put(const QByteArray&key, const QByteArray&data, const quint64 expiration);

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    virtual QByteArray get(const QByteArray&key);

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    virtual QByteArray take(const QByteArray&key);

    //!
    //! \brief remove
    //! \param key
    //! \return
    //!
    virtual bool remove(const QByteArray&key);

    //!
    //! \brief list
    //! \param key
    //! \param listKeys
    //! \return
    //!
    virtual QVector<QByteArray> list(const QByteArray&key);

    //!
    //! \brief listKeys
    //! \param key
    //! \param listKeys
    //! \return
    //!
    virtual QVector<QByteArray> listKeys(const QByteArray&key);

private:
    void*p=nullptr;
signals:
};

}
