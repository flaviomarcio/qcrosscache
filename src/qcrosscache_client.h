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
    //! \param interface
    //!
    explicit Client(QObject*parent, ActuatorInterface *interface);

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
    virtual QByteArray dataGroup()const;

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
    virtual bool put(const QByteArray&key, const QByteArray&data, const quint64 expiration);

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
    //! \param key
    //! \return
    //!
    virtual QVector<QByteArray> listKeys(const QByteArray&key);

private:
    void*p=nullptr;
signals:
};

}
