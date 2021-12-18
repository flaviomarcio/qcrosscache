#include "./qcrosscache_server.h"
#include "./qcrosscache_actuator_interface.h"
#include "./qcrosscache_types.h"
#include <QDebug>
#include <QVariantHash>
#include <QVariantMap>
#include <QVariantList>
#include <QCryptographicHash>

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ServerPvt*>(this->p)

class ServerPvt{
public:
    Server *parent=nullptr;
    QUuid uuid;
    QByteArray service;
    QByteArray hostName;
    QByteArray passWord;
    QByteArray portNumber;
    ActuatorInterfaceItem *actuatorInterface=nullptr;
    explicit ServerPvt(Server *parent)
    {
        this->parent=parent;
    }

    virtual ~ServerPvt()
    {
    }

    Server&makeData()
    {
        auto serverData=(service+QByteArrayLiteral(".")+hostName+QByteArrayLiteral(".")+passWord+QByteArrayLiteral(".")+portNumber+QByteArrayLiteral(".")).toLower();
        this->uuid=QUuid::fromString(QString::fromUtf8(QCryptographicHash::hash(serverData, QCryptographicHash::Md5).toHex()));
        return*this->parent;
    }
};

Server::Server(QObject *parent) : QObject(parent)
{
    this->p=new Server(parent);
}

Server::~Server()
{
    dPvt();
    delete&p;
}

Server *Server::createServer(QObject*parent, ActuatorInterfaceItem *actuatorInterface, const QByteArray &hostName, const QByteArray &passWord, const QByteArray &portNumber)
{
    auto server=new Server(parent);
    auto p =static_cast<ServerPvt*>(server->p);
    p->actuatorInterface=actuatorInterface;
    p->hostName=hostName;
    p->passWord=passWord;
    p->portNumber=portNumber;
    p->makeData();
    return server;
}

const QUuid &Server::uuid()
{
    dPvt();
    return p.uuid;
}

const QByteArray &Server::service() const
{
    dPvt();
    return p.service;
}

Server &Server::setService(const QByteArray &value)
{
    dPvt();
    if (p.service == value)
        return p.makeData();
    p.service = value;
    emit serviceChanged();
    return p.makeData();
}

const QByteArray &Server::hostName() const
{
    dPvt();
    return p.hostName;
}

Server &Server::setHostName(const QByteArray &value)
{
    dPvt();
    if (p.hostName == value)
        return p.makeData();
    p.hostName = value;
    emit hostNameChanged();
    return p.makeData();
}

const QByteArray &Server::passWord() const
{
    dPvt();
    return p.passWord;
}

Server &Server::setPassWord(const QByteArray &value)
{
    dPvt();
    if (p.passWord == value)
        return p.makeData();
    p.passWord = value;
    emit passWordChanged();
    return p.makeData();
}

const QByteArray &Server::portNumber() const
{
    dPvt();
    return p.portNumber;
}

Server &Server::setPortNumber(const QByteArray &value)
{
    dPvt();
    if (p.portNumber == value)
        return p.makeData();
    p.portNumber = value;
    emit portNumberChanged();
    return p.makeData();
}

ActuatorInterface *Server::createActuator(const QByteArray &dataGroup)
{
    dPvt();
    auto interface=p.actuatorInterface->newObject<ActuatorInterface>(this, dataGroup);

    if(interface==nullptr){
        qWarning()<<QStringLiteral("invalid interface to metaObject: ")+p.actuatorInterface->metaObject.className();
        return nullptr;
    }

    if(interface->metaObject()->className()!=p.actuatorInterface->metaObject.className()){
        qWarning()<<QStringLiteral("incompatible interface(%1) vs metaObject(%2)").arg(interface->metaObject()->className(), p.actuatorInterface->metaObject.className());
        return nullptr;
    }
    return interface;
}

}
