#include "./p_qcrosscache_actuator_memcached.h"
#include "../qcrosscache_session.h"

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ActuatorMemcachedPvt*>(this->p)

class ActuatorMemcachedPvt{
public:
    ActuatorMemcached*parent=nullptr;
    QMetaObject*actuatorMetaObject=nullptr;
    explicit ActuatorMemcachedPvt(ActuatorMemcached *parent)
    {
        this->parent=parent;
    }

    virtual ~ActuatorMemcachedPvt()
    {
    }
};


ActuatorMemcached::ActuatorMemcached(QObject *parent) : ActuatorInterface(parent)
{
    this->p=new ActuatorMemcachedPvt(this);
}

ActuatorMemcached::ActuatorMemcached(QObject *parent, Session *session, const QByteArray &dataGroup) : ActuatorInterface(parent, session, dataGroup)
{
    this->p=new ActuatorMemcachedPvt(this);
}

ActuatorMemcached::~ActuatorMemcached()
{
    dPvt();
    delete&p;
}

bool ActuatorMemcached::put(const QByteArray &key, QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorMemcached::get(const QByteArray &key, QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorMemcached::take(const QByteArray &key, QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorMemcached::remove(const QByteArray &key)
{
    Q_UNUSED(key)
    return false;
}

bool ActuatorMemcached::list(const QByteArray &key, QVector<QByteArray> &listKeys)
{
    Q_UNUSED(key)
    Q_UNUSED(listKeys)
    return false;
}

bool ActuatorMemcached::listKeys(const QByteArray &key, QVector<QByteArray> &listKeys)
{
    Q_UNUSED(key)
    Q_UNUSED(listKeys)
    return false;
}

} // namespace QCrossCache
