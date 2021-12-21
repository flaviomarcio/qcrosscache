#include "./qcrosscache_actuator_manager.h"
#include "./qcrosscache_types.h"
#include "./qcrosscache_server.h"
#include "./qcrosscache_actuator_interface.h"
#include <QVariantList>
#include <QDebug>
#include <QVariantHash>
#include <QCryptographicHash>


namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ActuatorManagerPvt*>(this->p)

class ActuatorManagerPvt:public QObject{
public:
    ActuatorManager*parent=nullptr;
    ActuatorInterfaceCollection interfaceCollection;
    QHash<QByteArray, Server*> servers;
    explicit ActuatorManagerPvt(ActuatorManager *parent):QObject(parent)
    {
        this->parent=parent;
    }

    virtual ~ActuatorManagerPvt()
    {
    }
public slots:
    void serverDestroyed(QObject *object=nullptr)
    {
        auto server=dynamic_cast<Server*>(object);
        this->servers.remove(server->uuid().toByteArray());
    }
};

ActuatorManager::ActuatorManager(QObject *parent) : QObject(parent)
{
    this->p=new ActuatorManagerPvt(this);
}


ActuatorManager::~ActuatorManager()
{
    dPvt();
    delete&p;
}

ActuatorManager &ActuatorManager::instance()
{
    static ActuatorManager __instance;
    return __instance;
}

const ActuatorInterfaceCollection &ActuatorManager::interfaceRegistered()
{
    dPvt();
    return p.interfaceCollection;
}

ActuatorInterfaceItem*ActuatorManager::registerInterface(const QByteArray &serviceName, const QMetaObject &metaObject)
{
    auto object=metaObject.newInstance();
    if(object==nullptr){
        return nullptr;
    }
    auto server=dynamic_cast<ActuatorManager*>(object);
    if(server==nullptr){
        delete object;
        return nullptr;
    }
    dPvt();
    ActuatorInterfaceItem*interfaceItem=new ActuatorInterfaceItem(serviceName, metaObject);
    p.interfaceCollection.insert(interfaceItem->name, interfaceItem);
    delete object;
    return interfaceItem;
}

Server *ActuatorManager::createServer(const QByteArray &service, const QByteArray &hostName, const QByteArray &passWord, const QByteArray &portNumber)
{
    dPvt();

    ActuatorInterfaceItem *ActuatorInterface=p.interfaceCollection.value(service.toLower());

    if(ActuatorInterface==nullptr){
        qWarning()<<"invalid interface";
        return nullptr;
    }

    auto server=Server::createServer(this, ActuatorInterface, hostName, passWord, portNumber);

    auto serverUuid=server->uuid().toByteArray();
    if(p.servers.contains(serverUuid)){
        delete server;
        return p.servers.value(serverUuid);
    }
    if(server==nullptr){
        qWarning()<<"no create server";
        return nullptr;
    }

    QObject::connect(server, &Server::destroyed,&p, &ActuatorManagerPvt::serverDestroyed);
    p.servers[serverUuid]=server;
    return server;
}

Server *ActuatorManager::createServer(const QVariant &settings)
{
    auto vSetting=settings.toHash();
    auto service=vSetting.value(QByteArrayLiteral("service")).toByteArray().toLower();
    auto hostName=vSetting.value(QByteArrayLiteral("hostName")).toByteArray();
    auto passWord=vSetting.value(QByteArrayLiteral("passWord")).toByteArray();
    auto portNumber=vSetting.value(QByteArrayLiteral("portNumber")).toByteArray();
    return createServer(service, hostName, passWord, portNumber);
}

}
