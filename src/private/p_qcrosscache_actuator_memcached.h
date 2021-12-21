#pragma once

#include "../qcrosscache_actuator_interface.h"
#include "../qcrosscache_actuator_manager.h"

namespace QCrossCache {

//!
//! \brief The ActuatorMemcached class
//!
class ActuatorMemcached : public ActuatorInterface
{
    Q_OBJECT
public:

    //!
    //! \brief ActuatorMemcached
    //! \param parent
    //!
    Q_INVOKABLE explicit ActuatorMemcached(QObject *parent = nullptr);

    //!
    //! \brief ActuatorMemcached
    //! \param server
    //! \param dataGroup
    //!
    explicit ActuatorMemcached(Server *server, const QByteArray &dataGroup);

    //!
    //!
    ~ActuatorMemcached();

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

private:
    void*p=nullptr;
signals:
};

Q_CROSSCACHE_REGISTER_INTERFACE(memcached,ActuatorMemcached)

} // namespace QCrossCache
