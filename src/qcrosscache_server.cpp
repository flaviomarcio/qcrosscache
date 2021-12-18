#include "./qcrosscache_server.h"
#include "./qcrosscache_actuator_interface.h"

#include <QVariantHash>
#include <QVariantMap>
#include <QVariantList>

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ServerPvt*>(this->p)

class ServerPvt{
public:
    Server *parent=nullptr;
    QByteArray hostName;
    QByteArray passWord;
    QByteArray portNumber;
    QByteArray dataGroup;
    explicit ServerPvt(Server *parent)
    {
        this->parent=parent;
    }

    virtual ~ServerPvt()
    {
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

Server *Server::createServer(const QByteArray &hostName, const QByteArray &passWord, const QByteArray &portNumber, const QByteArray &dataGroup)
{
    Q_UNUSED(hostName)
    Q_UNUSED(passWord)
    Q_UNUSED(portNumber)
    Q_UNUSED(dataGroup)
    return nullptr;
}

Server *Server::createServer(const QVariant &settings)
{
    auto vSetting=settings.toHash();
    auto hostName=vSetting.value(QByteArrayLiteral("hostName")).toByteArray();
    auto passWord=vSetting.value(QByteArrayLiteral("passWord")).toByteArray();
    auto portNumber=vSetting.value(QByteArrayLiteral("portNumber")).toByteArray();
    auto dataGroup=vSetting.value(QByteArrayLiteral("dataGroup")).toByteArray();
    return createServer(hostName, passWord, portNumber, dataGroup);
}

const QByteArray &Server::hostName() const
{
    dPvt();
    return p.hostName;
}

void Server::setHostName(const QByteArray &value)
{
    dPvt();
    if (p.hostName == value)
        return;
    p.hostName = value;
    emit hostNameChanged();
}

const QByteArray &Server::passWord() const
{
    dPvt();
    return p.passWord;
}

void Server::setPassWord(const QByteArray &value)
{
    dPvt();
    if (p.passWord == value)
        return;
    p.passWord = value;
    emit passWordChanged();
}

const QByteArray &Server::portNumber() const
{
    dPvt();
    return p.portNumber;
}

void Server::setPortNumber(const QByteArray &value)
{
    dPvt();
    if (p.portNumber == value)
        return;
    p.portNumber = value;
    emit portNumberChanged();
}

const QByteArray &Server::dataGroup() const
{
    dPvt();
    return p.dataGroup;
}

void Server::setDataGroup(const QByteArray &value)
{
    dPvt();
    if (p.dataGroup == value)
        return;
    p.dataGroup = value;
    emit dataGroupChanged();
}

}
