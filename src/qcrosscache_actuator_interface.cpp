#include "./qcrosscache_actuator_interface.h"
#include "./qcrosscache_server.h"
#include <QVariantHash>
#include <QVariantList>

namespace QCrossCache {

class ActuatorInterfacePvt
{
public:
    ActuatorInterface *parent = nullptr;
    Server *server = nullptr;
    Server serverDefault;
    bool connected = false;
    QByteArray dataGroup = QByteArrayLiteral("default");
    explicit ActuatorInterfacePvt(ActuatorInterface *parent,
                                  Server *server,
                                  const QByteArray &dataGroup)
        : parent{parent}, server{server},serverDefault{parent},dataGroup{dataGroup}
    {
    }

    virtual ~ActuatorInterfacePvt() {}
};

ActuatorInterface::ActuatorInterface(QObject *parent) : QObject{parent}, p{new ActuatorInterfacePvt(this, nullptr, {})}
{
}

ActuatorInterface::ActuatorInterface(Server *server, const QByteArray &dataGroup) : QObject{server}, p{new ActuatorInterfacePvt(this, server, dataGroup)}
{
}

ActuatorInterface::~ActuatorInterface()
{
    delete p;
}

Server *ActuatorInterface::server()
{

    if (p->server != nullptr)
        return p->server;
    return &p->serverDefault;
}

const QByteArray &ActuatorInterface::dataGroup() const
{

    if (p->dataGroup.isEmpty())
        p->dataGroup = QByteArrayLiteral(".");
    return p->dataGroup;
}

ActuatorInterface &ActuatorInterface::setDataGroup(const QByteArray &value)
{

    p->dataGroup = value;
    return *this;
}

bool ActuatorInterface::connect()
{
    return false;
}

bool ActuatorInterface::disconnect()
{
    return false;
}

bool ActuatorInterface::isConnected()
{
    return false;
}

bool ActuatorInterface::clear()
{
    return false;
}

bool ActuatorInterface::exists(const QByteArray &key)
{
    Q_UNUSED(key)
    return false;
}

bool ActuatorInterface::put(const QByteArray &key, const QByteArray &data, const quint64 expiration)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    Q_UNUSED(expiration)
    return false;
}

QByteArray ActuatorInterface::get(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

QByteArray ActuatorInterface::take(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

bool ActuatorInterface::remove(const QByteArray &key)
{
    Q_UNUSED(key)
    return false;
}

QVector<QByteArray> ActuatorInterface::list(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

QVector<QByteArray> ActuatorInterface::listKeys()
{
    return {};
}

} // namespace QCrossCache
