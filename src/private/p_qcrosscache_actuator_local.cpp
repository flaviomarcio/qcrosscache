#include "./p_qcrosscache_actuator_local.h"
#include "../qcrosscache_pool.h"
#include "../qcrosscache_server.h"

namespace QCrossCache {

class ActuatorLocalPvt
{
public:
    ActuatorLocal *parent = nullptr;
    QMetaObject *actuatorMetaObject = nullptr;
    Pool &instance = QCrossCache::Pool::instance();
    explicit ActuatorLocalPvt(ActuatorLocal *parent) { this->parent = parent; }
    virtual ~ActuatorLocalPvt() {}
};

ActuatorLocal::ActuatorLocal(QObject *parent) : ActuatorInterface(parent)
{
    this->p = new ActuatorLocalPvt{this};
}

ActuatorLocal::ActuatorLocal(Server *server, const QByteArray &dataGroup)
    : ActuatorInterface(server, dataGroup)
{
    this->p = new ActuatorLocalPvt{this};
}

ActuatorLocal::~ActuatorLocal()
{
    delete p;
}

bool ActuatorLocal::connect()
{

    return p->instance.isStarted();
}

bool ActuatorLocal::disconnect()
{
    return true;
}

bool ActuatorLocal::clear()
{

    p->instance.cacheClear(this->dataGroup());
    return true;
}

bool ActuatorLocal::put(const QByteArray &key, const QByteArray &data, const quint64 expiration)
{

    p->instance.cachePut(this->dataGroup(), key, data, expiration);
    return true;
}

QByteArray ActuatorLocal::get(const QByteArray &key)
{

    return p->instance.cacheGet(this->dataGroup(), key);
}

QByteArray ActuatorLocal::take(const QByteArray &key)
{

    return p->instance.cacheTake(this->dataGroup(), key);
}

bool ActuatorLocal::remove(const QByteArray &key)
{

    p->instance.cacheRemove(this->dataGroup(), key);
    return true;
}

QVector<QByteArray> ActuatorLocal::list(const QByteArray &key)
{

    return p->instance.cacheList(this->dataGroup(), key);
}

QVector<QByteArray> ActuatorLocal::listKeys()
{

    return p->instance.cacheListKeys(this->dataGroup());
}

} // namespace QCrossCache
