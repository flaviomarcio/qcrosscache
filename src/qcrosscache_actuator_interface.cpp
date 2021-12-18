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

bool ActuatorInterface::put(const QByteArray &key, QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorInterface::get(const QByteArray &key, QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorInterface::take(const QByteArray &key, QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorInterface::remove(const QByteArray &key)
{
    Q_UNUSED(key)
    return false;
}

bool ActuatorInterface::list(const QByteArray &key, QVector<QByteArray> &listKeys)
{
    Q_UNUSED(key)
    Q_UNUSED(listKeys)
    return false;
}

bool ActuatorInterface::listKeys(const QByteArray &key, QVector<QByteArray> &listKeys)
{
    Q_UNUSED(key)
    Q_UNUSED(listKeys)
    return false;
}

}
