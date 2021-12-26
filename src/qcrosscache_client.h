#pragma once

#include <QObject>
#include <QVariant>
#include "./qcrosscache_global.h"

namespace QCrossCache {

class ClientItem;
class Server;
class ActuatorInterface;

//!
//! \brief The Client class
//!
class Q_CROSSCACHE_EXPORT Client : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief Client
    //! \param parent
    //!
    Q_INVOKABLE explicit Client(QObject*parent=nullptr);

    //!
    //! \brief Client
    //! \param parent
    //!
    explicit Client(const QByteArray&dataGroup, QObject*parent=nullptr);

    //!
    //! \brief Client
    //! \param parent
    //! \param interface
    //!
    explicit Client(ActuatorInterface *interface, QObject*parent=nullptr);

    //!
    //!
    ~Client();


    //!
    //! \brief server
    //! \return
    //!
    virtual Server*server();

    //!
    //! \brief dataGroup
    //! \return
    //!
    virtual const QByteArray &dataGroup()const;

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
    //! \param expiration
    //! \return
    //!
    virtual bool put(const QByteArray&key, const QByteArray&data, const quint64 expiration=0);

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    virtual QByteArray get(const QByteArray&key);

    //!
    //! \brief take
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
    //! \return
    //!
    virtual QVector<QByteArray> list(const QByteArray&key);

    //!
    //! \brief listKeys
    //! \return
    //!
    virtual QVector<QByteArray> listKeys();

private:
    void*p=nullptr;
};

//!
//! \brief clientForLocal
//! \return
//!
Client*clientForLocal(QObject*parent=nullptr);

//!
//! \brief clientForMemcached
//! \return
//!
Client*clientForMemcached(QObject*parent=nullptr);

//!
//! \brief clientForMongoDb
//! \return
//!
Client*clientForMongoDb(QObject*parent=nullptr);

//!
//! \brief clientForRedis
//! \return
//!
Client*clientForRedis(QObject*parent=nullptr);

}
