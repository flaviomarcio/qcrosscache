#include "./p_qcrosscache_actuator_local.h"
#include "../qcrosscache_server.h"
#include "../qcrosscache_pool_cache.h"

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ActuatorLocalPvt*>(this->p)

class ActuatorLocalPvt{
public:
    ActuatorLocal*parent=nullptr;
    QMetaObject*actuatorMetaObject=nullptr;
    PoolCache&instance=QCrossCache::PoolCache::instance();
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
    dPvt();
    QObject::connect(this, &ActuatorLocal::requestCache, &p.instance, &PoolCache::cacheGet);
}

ActuatorLocal::ActuatorLocal(Server *server, const QByteArray &dataGroup) : ActuatorInterface(server, dataGroup)
{
    this->p=new ActuatorLocalPvt(this);
    dPvt();
    QObject::disconnect(this, &ActuatorLocal::requestCache, &p.instance, &PoolCache::cacheGet);
}

ActuatorLocal::~ActuatorLocal()
{
    dPvt();
    delete&p;
}

bool ActuatorLocal::put(const QByteArray &key, const QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorLocal::get(const QByteArray &key, QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorLocal::take(const QByteArray &key, QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorLocal::remove(const QByteArray &key)
{
    Q_UNUSED(key)
    return false;
}

bool ActuatorLocal::list(const QByteArray &key, QVector<QByteArray> &listKeys)
{
    Q_UNUSED(key)
    Q_UNUSED(listKeys)
    return false;
}

bool ActuatorLocal::listKeys(const QByteArray &key, QVector<QByteArray> &listKeys)
{
    Q_UNUSED(key)
    Q_UNUSED(listKeys)
    return false;
}

} // namespace QCrossCache
