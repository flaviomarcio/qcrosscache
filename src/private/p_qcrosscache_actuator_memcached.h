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
    Q_INVOKABLE explicit ActuatorMemcached(Server *server, const QByteArray &dataGroup);

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
    Q_INVOKABLE virtual bool put(const QByteArray&key, const QByteArray &data);

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    Q_INVOKABLE virtual bool get(const QByteArray&key, QByteArray &data);

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    Q_INVOKABLE virtual bool take(const QByteArray&key, QByteArray&data);

    //!
    //! \brief remove
    //! \param key
    //! \return
    //!
    Q_INVOKABLE virtual bool remove(const QByteArray&key);

private:
    void*p=nullptr;
signals:
};

Q_CROSSCACHE_REGISTER_INTERFACE(memcached,ActuatorMemcached)

} // namespace QCrossCache
