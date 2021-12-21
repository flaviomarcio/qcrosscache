#include "./qcrosscache_client.h"
#include "./qcrosscache_server.h"
#include "./qcrosscache_actuator_interface.h"
#include <QVariantList>
#include <QVariantHash>

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ClientPvt*>(this->p)

class ClientPvt{
public:
    Client *parent=nullptr;
    ActuatorInterface*interface=nullptr;

    explicit ClientPvt(Client *parent, ActuatorInterface*interface)
    {
        this->parent=parent;
        this->interface=interface;
        if(this->interface!=nullptr)
            this->interface->setParent(parent);
    }

    virtual ~ClientPvt()
    {
    }
};

Client::Client(QObject *parent):QObject(parent)
{
    this->p=new ClientPvt(this, nullptr);
}

Client::Client(QObject *parent, ActuatorInterface*interface) : QObject(parent)
{
    this->p=new ClientPvt(this, interface);
}

Client::~Client()
{
    dPvt();
    delete&p;
}

Server *Client::server()
{
    dPvt();
    if(p.interface==nullptr)
        return nullptr;
    return p.interface->server();
}

QByteArray Client::dataGroup() const
{
    dPvt();
    if(p.interface==nullptr)
        return {};
    return p.interface->dataGroup();
}

bool Client::connect()
{
    dPvt();
    if(p.interface==nullptr)
        return false;
    return p.interface->connect();
}

bool Client::disconnect()
{
    dPvt();
    if(p.interface==nullptr)
        return false;
    return p.interface->disconnect();
}

bool Client::isConnected()
{
    dPvt();
    if(p.interface==nullptr)
        return false;
    return p.interface->isConnected();
}

bool Client::clear()
{
    dPvt();
    if(p.interface==nullptr)
        return false;
    return p.interface->clear();
}

bool Client::exists(const QByteArray &key)
{
    dPvt();
    if(p.interface==nullptr)
        return false;
    return p.interface->exists(key);
}

bool Client::put(const QByteArray &key, const QByteArray &data, const quint64 expiration)
{
    dPvt();
    if(p.interface==nullptr)
        return false;
    return p.interface->put(key, data, expiration);
}

QByteArray Client::get(const QByteArray &key)
{
    dPvt();
    if(p.interface==nullptr)
        return {};
    return p.interface->get(key);
}

QByteArray Client::take(const QByteArray &key)
{
    dPvt();
    if(p.interface==nullptr)
        return {};
    return p.interface->take(key);
}

bool Client::remove(const QByteArray &key)
{
    dPvt();
    if(p.interface==nullptr)
        return false;
    return p.interface->remove(key);
}

QVector<QByteArray> Client::list(const QByteArray &key)
{
    dPvt();
    if(p.interface==nullptr)
        return {};
    return p.interface->list(key);
}

QVector<QByteArray> Client::listKeys(const QByteArray &key)
{
    dPvt();
    if(p.interface==nullptr)
        return {};
    return p.interface->listKeys(key);
}

}
