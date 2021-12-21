#include "./qcrosscache_actuator_interface.h"
#include "./qcrosscache_server.h"
#include <QVariantList>
#include <QVariantHash>

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ActuatorInterfacePvt*>(this->p)

class ActuatorInterfacePvt{
public:
    ActuatorInterface*parent=nullptr;
    Server*server=nullptr;
    bool connected=false;
    QByteArray dataGroup;
    explicit ActuatorInterfacePvt(ActuatorInterface *parent, Server *server, const QByteArray &dataGroup)
    {
        this->parent=parent;
        this->server=server;
        this->dataGroup=dataGroup;
    }

    virtual ~ActuatorInterfacePvt()
    {
    }
};

ActuatorInterface::ActuatorInterface(QObject *parent) : QObject(parent)
{
    this->p=new ActuatorInterfacePvt(this, nullptr, QByteArray());
}

ActuatorInterface::ActuatorInterface(Server *server, const QByteArray &dataGroup) : QObject(server)
{
    this->p=new ActuatorInterfacePvt(this, server, dataGroup);
}

ActuatorInterface::~ActuatorInterface()
{
    dPvt();
    delete&p;
}

Server *ActuatorInterface::server()
{
    dPvt();
    return p.server;
}

QByteArray &ActuatorInterface::dataGroup() const
{
    dPvt();
    return p.dataGroup;
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

QVector<QByteArray> ActuatorInterface::listKeys(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

}
