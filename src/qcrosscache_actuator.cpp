#include "./qcrosscache_actuator.h"
#include "./qcrosscache_session.h"

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ActuatorPvt*>(this->p)

class ActuatorPvt{
public:
    Actuator*parent=nullptr;
    ActuatorInterface*actuatorSession=nullptr;
    Session*session=nullptr;
    QMetaObject*actuatorMetaObject=nullptr;
    explicit ActuatorPvt(Actuator *parent, Session*session)
    {
        this->parent=parent;
        this->session=session;
    }

    virtual ~ActuatorPvt()
    {
    }
};

Actuator::Actuator(QObject *parent):ActuatorInterface(parent)
{
    this->p=new ActuatorPvt(this,nullptr);

}

Actuator::Actuator(QObject *parent, Session *session, const QByteArray &dataGroup):ActuatorInterface(parent, session, dataGroup)
{
    this->p=new ActuatorPvt(this, session);
}

Actuator::~Actuator()
{
    dPvt();
    delete&p;
}

bool Actuator::put(const QByteArray &key, QByteArray &data)
{
    dPvt();
    if(p.actuatorSession==nullptr)
        return false;
    return p.actuatorSession->put(key, data);
}

bool Actuator::get(const QByteArray &key, QByteArray &data)
{
    dPvt();
    if(p.actuatorSession==nullptr)
        return false;
    return p.actuatorSession->get(key, data);
}

bool Actuator::take(const QByteArray &key, QByteArray &data)
{
    dPvt();
    if(p.actuatorSession==nullptr)
        return false;
    return p.actuatorSession->take(key, data);
}

bool Actuator::remove(const QByteArray &key)
{
    dPvt();
    if(p.actuatorSession==nullptr)
        return false;
    return p.actuatorSession->remove(key);
}

bool Actuator::list(const QByteArray &key, QVector<QByteArray> &listKeys)
{
    dPvt();
    if(p.actuatorSession==nullptr)
        return false;
    return p.actuatorSession->list(key, listKeys);
}

bool Actuator::listKeys(const QByteArray &key, QVector<QByteArray> &listKeys)
{
    dPvt();
    if(p.actuatorSession==nullptr)
        return false;
    return p.actuatorSession->listKeys(key, listKeys);
}

}
