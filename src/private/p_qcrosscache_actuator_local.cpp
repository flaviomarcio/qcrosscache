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

bool ActuatorLocal::clear()
{
    return false;
}

bool ActuatorLocal::put(const QByteArray &key, const QByteArray &data, const quint64 expiration)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    Q_UNUSED(expiration)
    return false;
}

QByteArray ActuatorLocal::get(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

QByteArray ActuatorLocal::take(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

bool ActuatorLocal::remove(const QByteArray &key)
{
    Q_UNUSED(key)
    return false;
}

QVector<QByteArray> ActuatorLocal::list(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

QVector<QByteArray> ActuatorLocal::listKeys(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

} // namespace QCrossCache
