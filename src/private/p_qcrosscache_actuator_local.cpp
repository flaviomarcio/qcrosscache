#include "./p_qcrosscache_actuator_local.h"
#include "../qcrosscache_server.h"
#include "../qcrosscache_pool.h"

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ActuatorLocalPvt*>(this->p)

class ActuatorLocalPvt{
public:
    ActuatorLocal*parent=nullptr;
    QMetaObject*actuatorMetaObject=nullptr;
    Pool&instance=QCrossCache::Pool::instance();
    explicit ActuatorLocalPvt(ActuatorLocal *parent)
    {
        this->parent=parent;
    }
    virtual ~ActuatorLocalPvt()
    {
    }
};


ActuatorLocal::ActuatorLocal(QObject *parent) : ActuatorInterface(parent)
{
    this->p=new ActuatorLocalPvt(this);
}

ActuatorLocal::ActuatorLocal(Server *server, const QByteArray &dataGroup) : ActuatorInterface(server, dataGroup)
{
    this->p=new ActuatorLocalPvt(this);
}

ActuatorLocal::~ActuatorLocal()
{
    dPvt();
    delete&p;
}

bool ActuatorLocal::connect()
{
    dPvt();
    return p.instance.isStarted();
}

bool ActuatorLocal::disconnect()
{
    return true;
}

bool ActuatorLocal::clear()
{
    dPvt();
    p.instance.cacheClear(this->dataGroup());
    return true;
}

bool ActuatorLocal::put(const QByteArray &key, const QByteArray &data, const quint64 expiration)
{
    dPvt();
    p.instance.cachePut(this->dataGroup(), key, data, expiration);
    return true;
}

QByteArray ActuatorLocal::get(const QByteArray &key)
{
    dPvt();
    return p.instance.cacheGet(this->dataGroup(), key);
}

QByteArray ActuatorLocal::take(const QByteArray &key)
{
    dPvt();
    return p.instance.cacheTake(this->dataGroup(), key);
}

bool ActuatorLocal::remove(const QByteArray &key)
{
    dPvt();
    p.instance.cacheRemove(this->dataGroup(), key);
    return true;
}

QVector<QByteArray> ActuatorLocal::list(const QByteArray &key)
{
    dPvt();
    return p.instance.cacheList(this->dataGroup(), key);
}

QVector<QByteArray> ActuatorLocal::listKeys()
{
    dPvt();
    return p.instance.cacheListKeys(this->dataGroup());
}

} // namespace QCrossCache
