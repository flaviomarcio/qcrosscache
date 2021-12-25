#pragma once

#include "../qcrosscache_actuator_interface.h"
#include "../qcrosscache_actuator_manager.h"

namespace QCrossCache {

//!
//! \brief The ActuatorRedis class
//!
class ActuatorRedis : public ActuatorInterface
{
    Q_OBJECT
public:

    //!
    //! \brief ActuatorRedis
    //! \param parent
    //!
    Q_INVOKABLE explicit ActuatorRedis(QObject *parent = nullptr);

    //!
    //! \brief ActuatorRedis
    //! \param server
    //! \param dataGroup
    //!
    explicit ActuatorRedis(Server *server, const QByteArray &dataGroup);

    //!
    //!
    ~ActuatorRedis();

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
    virtual bool put(const QByteArray&key, const QByteArray &data, const quint64 expiration);

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
    //! \return
    //!
    virtual QVector<QByteArray> list(const QByteArray&key);

    //!
    //! \brief listKeys
    //! \param key
    //! \return
    //!
    virtual QVector<QByteArray> listKeys();

private:
    void*p=nullptr;
signals:
};

Q_CROSSCACHE_REGISTER_INTERFACE(redis,ActuatorRedis)

} // namespace QCrossCache
