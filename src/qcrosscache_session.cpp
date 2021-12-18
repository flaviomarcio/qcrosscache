#include "./qcrosscache_session.h"
#include "./qcrosscache_server.h"

namespace QCrossCache {


#define dPvt()\
auto&p = *reinterpret_cast<SessionPvt*>(this->p)

class SessionPvt{
public:
    Server *server=nullptr;
    Session *parent=nullptr;
    QByteArray hostName;
    QByteArray passWord;
    QByteArray portNumber;
    QByteArray dataGroup;
    QMetaObject*interfaceMetaObject=nullptr;
    explicit SessionPvt(Session *parent)
    {
        this->parent=parent;
    }

    virtual ~SessionPvt()
    {
    }
};

Session::Session(QObject *parent) : QObject(parent)
{
    this->p=new SessionPvt(this);
}

Session::~Session()
{
    dPvt();
    delete&p;
}

QMetaObject *Session::interfaceMetaObject()
{
    dPvt();
    return p.interfaceMetaObject;
}

Server &Session::server()
{
    dPvt();
    return *p.server;
}

const QByteArray &Session::dataGroup() const
{
    dPvt();
    return p.dataGroup;
}

void Session::setDataGroup(const QByteArray &value)
{
    dPvt();
    if (p.dataGroup == value)
        return;
    p.dataGroup = value;
    emit dataGroupChanged();
}

}
