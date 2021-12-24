#pragma once

#include "../qcrosscache_actuator_interface.h"
#include "../qcrosscache_types.h"
#include "../qcrosscache_actuator_manager.h"

namespace QCrossCache {

//!
//! \brief The ActuatorLocal class
//!
class ActuatorLocal : public ActuatorInterface
{
    Q_OBJECT
public:

    //!
    //! \brief ActuatorLocal
    //! \param parent
    //!
    Q_INVOKABLE explicit ActuatorLocal(QObject *parent = nullptr);

    //!
    //! \brief ActuatorLocal
    //! \param parent
    //! \param session
    //! \param dataGroup
    //!
    explicit ActuatorLocal(Server *session, const QByteArray &dataGroup);

    //!
    //!
    ~ActuatorLocal();

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
    //! \brief clear
    //! \return
    //!
    virtual bool clear();

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
};

Q_CROSSCACHE_REGISTER_INTERFACE(local, ActuatorLocal)

} // namespace QCrossCache
