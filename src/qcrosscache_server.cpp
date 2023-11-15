#include "./qcrosscache_server.h"
#include "./qcrosscache_actuator_interface.h"
#include "./qcrosscache_types.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QVariantHash>
#include <QVariantList>
#include <QVariantMap>

namespace QCrossCache {

class ServerPvt
{
public:
    Server *parent = nullptr;
    QUuid uuid;
    QByteArray service;
    QByteArray hostName = QByteArrayLiteral("localhost");
    QByteArray passWord;
    QByteArray portNumber;
    ActuatorInterfaceItem *ActuatorInterface = nullptr;
    explicit ServerPvt(Server *parent): parent{parent} {}

    virtual ~ServerPvt() {}

    Server &makeData()
    {
        auto serverData = (service + QByteArrayLiteral(".") + hostName + QByteArrayLiteral(".")
                           + passWord + QByteArrayLiteral(".") + portNumber + QByteArrayLiteral("."))
                              .toLower();
        this->uuid = QUuid::fromString(QString::fromUtf8(
            QCryptographicHash::hash(serverData, QCryptographicHash::Md5).toHex()));
        return *this->parent;
    }
};

Server::Server(QObject *parent) : QObject{parent}, p{new ServerPvt{this}}
{
}

Server::~Server()
{

    delete p;
}

Server *Server::createServer(QObject *parent,
                             ActuatorInterfaceItem *ActuatorInterface,
                             const QByteArray &hostName,
                             const QByteArray &passWord,
                             const QByteArray &portNumber)
{
    auto server = new Server{parent};
    auto p = static_cast<ServerPvt *>(server->p);
    p->ActuatorInterface = ActuatorInterface;
    p->hostName = hostName;
    p->passWord = passWord;
    p->portNumber = portNumber;
    p->makeData();
    return server;
}

Client *Server::createClient(const QByteArray &dataGroup)
{

    auto interface = p->ActuatorInterface->newObject<ActuatorInterface>(this, dataGroup);

    if (interface == nullptr) {
        qWarning() << QStringLiteral("invalid interface to metaObject: ")
                          + p->ActuatorInterface->metaObject.className();
        return nullptr;
    }

    if (interface->metaObject()->className() != p->ActuatorInterface->metaObject.className()) {
        qWarning() << QStringLiteral("incompatible interface(%1) vs metaObject(%2)")
                          .arg(interface->metaObject()->className(),
                               p->ActuatorInterface->metaObject.className());
        return nullptr;
    }
    if (!dataGroup.isEmpty())
        interface->setDataGroup(dataGroup);
    auto client = new Client{interface, this};
    return client;
}

const QUuid &Server::uuid()
{

    return p->uuid;
}

const QByteArray &Server::service() const
{

    return p->service;
}

Server &Server::setService(const QByteArray &value)
{

    if (p->service == value)
        return p->makeData();
    p->service = value;
    emit serviceChanged();
    return p->makeData();
}

const QByteArray &Server::hostName() const
{

    return p->hostName;
}

Server &Server::setHostName(const QByteArray &value)
{

    if (p->hostName == value)
        return p->makeData();
    p->hostName = value;
    emit hostNameChanged();
    return p->makeData();
}

const QByteArray &Server::passWord() const
{

    return p->passWord;
}

Server &Server::setPassWord(const QByteArray &value)
{

    if (p->passWord == value)
        return p->makeData();
    p->passWord = value;
    emit passWordChanged();
    return p->makeData();
}

const QByteArray &Server::portNumber() const
{

    return p->portNumber;
}

Server &Server::setPortNumber(const QByteArray &value)
{

    if (p->portNumber == value)
        return p->makeData();
    p->portNumber = value;
    emit portNumberChanged();
    return p->makeData();
}

Server &Server::setPortNumber(const qlonglong &value)
{

    if (p->portNumber.toLongLong() == value)
        return p->makeData();
    p->portNumber = QByteArray::number(value);
    emit portNumberChanged();
    return p->makeData();
}

} // namespace QCrossCache
