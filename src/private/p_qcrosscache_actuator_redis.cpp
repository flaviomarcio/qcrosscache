//https://github.com/tdv/redis-cpp

#include "./p_qcrosscache_actuator_redis.h"
#include "../qcrosscache_server.h"
#include <QDebug>

namespace QCrossCache {

class ActuatorRedisPvt
{
public:
    ActuatorRedis *parent = nullptr;
    explicit ActuatorRedisPvt(ActuatorRedis *parent):parent{parent} {}
    virtual ~ActuatorRedisPvt() { this->disconnect(); }
    bool disconnect() { return true; }
};

ActuatorRedis::ActuatorRedis(QObject *parent) : ActuatorInterface{parent}, p{new ActuatorRedisPvt{this}}
{
}

ActuatorRedis::ActuatorRedis(Server *server, const QByteArray &dataGroup)
    : ActuatorInterface{server, dataGroup}, p{new ActuatorRedisPvt{this}}
{
}

ActuatorRedis::~ActuatorRedis()
{
    delete p;
}

bool ActuatorRedis::connect()
{
    return true;
}

bool ActuatorRedis::disconnect()
{

    return p->disconnect();
}

bool ActuatorRedis::isConnected()
{
    return true;
}

bool ActuatorRedis::clear()
{
    return true;
}

bool ActuatorRedis::exists(const QByteArray &key)
{
    Q_UNUSED(key)
    return true;
}

bool ActuatorRedis::put(const QByteArray &key, const QByteArray &data, const quint64 expiration)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    Q_UNUSED(expiration)
    return true;
}

QByteArray ActuatorRedis::get(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

QByteArray ActuatorRedis::take(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

bool ActuatorRedis::remove(const QByteArray &key)
{
    Q_UNUSED(key)
    return false;
}

QVector<QByteArray> ActuatorRedis::list(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

QVector<QByteArray> ActuatorRedis::listKeys()
{
    qWarning() << tr("no implemented");
    return {};
}

} // namespace QCrossCache
