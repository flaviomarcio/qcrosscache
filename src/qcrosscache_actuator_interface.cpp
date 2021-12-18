#include "./qcrosscache_actuator_interface.h"
#include "./qcrosscache_session.h"
#include <QVariantList>
#include <QVariantHash>

namespace QCrossCache {

static QVector<const QMetaObject*>&make_static_interface_metaobject()
{
    static QVector<const QMetaObject*>__return;
    return __return;
}

#define dPvt()\
auto&p = *reinterpret_cast<ActuatorInterfacePvt*>(this->p)

class ActuatorInterfacePvt{
public:
    ActuatorInterface*parent=nullptr;
    Session*session=nullptr;
    QByteArray dataGroup;
    explicit ActuatorInterfacePvt(ActuatorInterface *parent, Session *session, const QByteArray &dataGroup)
    {
        this->parent=parent;
        this->session=session;
        if(session!=nullptr && dataGroup.isEmpty())
            this->dataGroup=session->dataGroup();
        else
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

ActuatorInterface::ActuatorInterface(QObject *parent, Session *session, const QByteArray &dataGroup) : QObject(parent)
{
    this->p=new ActuatorInterfacePvt(this, session, dataGroup);
}

ActuatorInterface::~ActuatorInterface()
{
    dPvt();
    delete&p;
}

const QVector<const QMetaObject *> &ActuatorInterface::interfaceRegistered()
{
    auto&metaobjectList=make_static_interface_metaobject();
    return metaobjectList;
}

const QMetaObject&ActuatorInterface::registerInterface(const QMetaObject &metaObject)
{
    auto object=metaObject.newInstance();
    if(object==nullptr){
        return ActuatorInterface::staticMetaObject;
    }
    auto server=dynamic_cast<ActuatorInterface*>(object);
    if(server==nullptr){
        delete object;
        return ActuatorInterface::staticMetaObject;
    }
    auto&metaobjectList=make_static_interface_metaobject();
    metaobjectList<<&metaObject;
    delete object;
    return metaObject;
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

Server *ActuatorInterface::createServer(const QByteArray &hostName, const QByteArray &passWord, const QByteArray &portNumber, const QByteArray &dataGroup)
{
    Q_UNUSED(hostName)
    Q_UNUSED(passWord)
    Q_UNUSED(portNumber)
    Q_UNUSED(dataGroup)
    return nullptr;
}

Server *ActuatorInterface::createServer(const QVariant &settings)
{
    auto vSetting=settings.toHash();
    auto hostName=vSetting.value(QByteArrayLiteral("hostName")).toByteArray();
    auto passWord=vSetting.value(QByteArrayLiteral("passWord")).toByteArray();
    auto portNumber=vSetting.value(QByteArrayLiteral("portNumber")).toByteArray();
    auto dataGroup=vSetting.value(QByteArrayLiteral("dataGroup")).toByteArray();
    return createServer(hostName, passWord, portNumber, dataGroup);
}

}
