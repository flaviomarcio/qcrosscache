#include "./p_qcrosscache_actuator_local.h"
#include "../qcrosscache_session.h"

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ActuatorLocalPvt*>(this->p)

class ActuatorLocalPvt{
public:
    ActuatorLocal*parent=nullptr;
    QMetaObject*actuatorMetaObject=nullptr;
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

ActuatorLocal::ActuatorLocal(QObject *parent, Session *session, const QByteArray &dataGroup) : ActuatorInterface(parent, session, dataGroup)
{
    this->p=new ActuatorLocalPvt(this);
}

ActuatorLocal::~ActuatorLocal()
{
    dPvt();
    delete&p;
}

bool ActuatorLocal::put(const QByteArray &key, QByteArray &data)
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
