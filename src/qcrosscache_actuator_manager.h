#pragma once

#include <QObject>
#include <QVariant>
#include "./qcrosscache_global.h"
#include "./qcrosscache_types.h"

#define Q_CROSSCACHE_REGISTER_INTERFACE(serviceName, object)\
static auto const interface__##object=QCrossCache::ActuatorManager::instance().registerInterface(#serviceName, object::staticMetaObject);

namespace QCrossCache {

class Session;
class Server;

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
    //!
    ~ActuatorManager();

    //!
    //! \brief instance
    //! \return
    //!
    static ActuatorManager&instance();

    //!
    //! \brief interfaceRegistered
    //! \return
    //!
    const ActuatorInterfaceCollection &interfaceRegistered();

    //!
    //! \brief interfaceRegister
    //! \param metaObject
    //!
    ActuatorInterfaceItem *registerInterface(const QByteArray&serviceName, const QMetaObject &metaObject);

    //!
    //! \brief createServer
    //! \param service
    //! \param hostName
    //! \param passWord
    //! \param portNumber
    //! \param dataGroup
    //! \return
    //!
    Server*createServer(const QByteArray &service, const QByteArray &hostName, const QByteArray &passWord, const QByteArray &portNumber);

    //!
    //! \brief createServer
    //! \param settings
    //! \return
    //!
    Server*createServer(const QVariant&settings);
private:
    void*p=nullptr;
signals:
};

}
