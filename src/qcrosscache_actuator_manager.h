#pragma once

#include "./qcrosscache_global.h"
#include "./qcrosscache_types.h"
#include <QObject>
#include <QVariant>

#define Q_CROSSCACHE_REGISTER_INTERFACE(serviceName, object) \
static auto const interface__##object = QCrossCache::ActuatorManager::instance() .interfaceRegister(#serviceName, object::staticMetaObject);

namespace QCrossCache {

class Session;
class Server;
class ActuatorInterface;
class ActuatorManagerPvt;

//!
//! \brief The ActuatorManager class
//!
class Q_CROSSCACHE_EXPORT ActuatorManager : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief ActuatorManager
    //! \param parent
    //!
    Q_INVOKABLE explicit ActuatorManager(QObject *parent = nullptr);

    //!
    //! \brief instance
    //! \return
    //!
    static ActuatorManager &instance();

    //!
    //! \brief interfaceRegistered
    //! \return
    //!
    const ActuatorInterfaceCollection &interfaceRegistered();

    //!
    //! \brief interfaceRegister
    //! \param metaObject
    //!
    ActuatorInterfaceItem *interfaceRegister(const QByteArray &interfaceName,
                                             const QMetaObject &metaObject);

    //!
    //! \brief interfaceCreate
    //! \param interfaceName
    //! \return
    //!
    ActuatorInterface *interfaceCreate(const QByteArray &interfaceName);

    //!
    //! \brief createServer
    //! \param service
    //! \param hostName
    //! \param passWord
    //! \param portNumber
    //! \param dataGroup
    //! \return
    //!
    Server *createServer(const QByteArray &service,
                         const QByteArray &hostName,
                         const QByteArray &passWord,
                         const QByteArray &portNumber);

    //!
    //! \brief createServer
    //! \param settings
    //! \return
    //!
    Server *createServer(const QVariant &settings);

private:
    ActuatorManagerPvt *p = nullptr;
signals:
};

} // namespace QCrossCache
