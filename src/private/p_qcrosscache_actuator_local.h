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
    Q_INVOKABLE explicit ActuatorLocal(Server *session, const QByteArray &dataGroup);

    //!
    //!
    ~ActuatorLocal();

    //!
    //! \brief put
    //! \param key
    //! \param data
    //! \return
    //!
    Q_INVOKABLE virtual bool put(const QByteArray&key, QByteArray&data);

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    Q_INVOKABLE virtual bool get(const QByteArray&key, QByteArray&data);

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

    //!
    //! \brief list
    //! \param key
    //! \param listKeys
    //! \return
    //!
    Q_INVOKABLE virtual bool list(const QByteArray&key, QVector<QByteArray>&listKeys);

    //!
    //! \brief listKeys
    //! \param key
    //! \param listKeys
    //! \return
    //!
    Q_INVOKABLE virtual bool listKeys(const QByteArray&key, QVector<QByteArray>&listKeys);
private:
    void*p=nullptr;
signals:
    void requestCache(const QByteArray&dataGroup, const QByteArray&key, PoolCacheResponseData response);
};

Q_CROSSCACHE_REGISTER_INTERFACE(local, ActuatorLocal)

} // namespace QCrossCache
