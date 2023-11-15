#include "./qcrosscache_actuator_manager.h"
#include "./qcrosscache_actuator_interface.h"
#include "./qcrosscache_server.h"
#include "./qcrosscache_types.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QVariantHash>
#include <QVariantList>

namespace QCrossCache {

Q_GLOBAL_STATIC(ActuatorManager, staticActuatorManager)

class ActuatorManagerPvt : public QObject
{
public:
    ActuatorManager *parent = nullptr;
    ActuatorInterfaceCollection interfaceCollection;
    QHash<QByteArray, Server *> servers;
    explicit ActuatorManagerPvt(ActuatorManager *parent) : QObject{parent}, parent{parent}
    {
    }

public slots:
    void serverDestroyed(QObject *object = nullptr)
    {
        auto server = dynamic_cast<Server *>(object);
        this->servers.remove(server->uuid().toByteArray());
    }
};

ActuatorManager::ActuatorManager(QObject *parent) : QObject{parent}, p{new ActuatorManagerPvt{this}}
{
}

ActuatorManager &ActuatorManager::instance()
{
    return *staticActuatorManager;
}

const ActuatorInterfaceCollection &ActuatorManager::interfaceRegistered()
{

    return p->interfaceCollection;
}

ActuatorInterfaceItem *ActuatorManager::interfaceRegister(const QByteArray &interfaceName,
                                                          const QMetaObject &metaObject)
{
    auto object = metaObject.newInstance();
    if (object == nullptr) {
        return nullptr;
    }
    auto server = dynamic_cast<ActuatorManager *>(object);
    if (server == nullptr) {
        delete object;
        return nullptr;
    }

    auto interfaceItem = new ActuatorInterfaceItem(interfaceName, metaObject);
    p->interfaceCollection.insert(interfaceItem->name.toLower(), interfaceItem);
    delete object;
    return interfaceItem;
}

ActuatorInterface *ActuatorManager::interfaceCreate(const QByteArray &interfaceName)
{

    auto interfaceItem = p->interfaceCollection.value(interfaceName.toLower());
    if (interfaceItem == nullptr)
        return nullptr;

    return interfaceItem->newObject<ActuatorInterface>();
}

Server *ActuatorManager::createServer(const QByteArray &service,
                                      const QByteArray &hostName,
                                      const QByteArray &passWord,
                                      const QByteArray &portNumber)
{


    ActuatorInterfaceItem *ActuatorInterface = p->interfaceCollection.value(service.toLower());

    if (ActuatorInterface == nullptr) {
        qWarning() << "invalid interface";
        return nullptr;
    }

    auto server = Server::createServer(this, ActuatorInterface, hostName, passWord, portNumber);

    auto serverUuid = server->uuid().toByteArray();
    if (p->servers.contains(serverUuid)) {
        delete server;
        return p->servers.value(serverUuid);
    }
    if (server == nullptr) {
        qWarning() << "no create server";
        return nullptr;
    }

    QObject::connect(server, &Server::destroyed, p, &ActuatorManagerPvt::serverDestroyed);
    p->servers.insert(serverUuid, server);
    return server;
}

Server *ActuatorManager::createServer(const QVariant &settings)
{
    auto vSetting = settings.toHash();
    auto service = vSetting.value(QByteArrayLiteral("service")).toByteArray().toLower();
    auto hostName = vSetting.value(QByteArrayLiteral("hostName")).toByteArray();
    auto passWord = vSetting.value(QByteArrayLiteral("passWord")).toByteArray();
    auto portNumber = vSetting.value(QByteArrayLiteral("portNumber")).toByteArray();
    return createServer(service, hostName, passWord, portNumber);
}

} // namespace QCrossCache
