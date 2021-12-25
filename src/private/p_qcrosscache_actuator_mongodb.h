#pragma once

#include "../qcrosscache_actuator_interface.h"
#include "../qcrosscache_actuator_manager.h"

namespace QCrossCache {

//!
//! \brief The ActuatorMongoDb class
//!
class ActuatorMongoDb : public ActuatorInterface
{
    Q_OBJECT
public:

    //!
    //! \brief ActuatorMongoDb
    //! \param parent
    //!
    Q_INVOKABLE explicit ActuatorMongoDb(QObject *parent = nullptr);

    //!
    //! \brief ActuatorMongoDb
    //! \param server
    //! \param dataGroup
    //!
    explicit ActuatorMongoDb(Server *server, const QByteArray &dataGroup);

    //!
    //!
    ~ActuatorMongoDb();

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

Q_CROSSCACHE_REGISTER_INTERFACE(mongodb,ActuatorMongoDb)

} // namespace QCrossCache
