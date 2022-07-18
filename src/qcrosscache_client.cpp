#include "./qcrosscache_client.h"
#include "./qcrosscache_actuator_interface.h"
#include "./qcrosscache_actuator_manager.h"
#include "./qcrosscache_server.h"
#include <QVariantHash>
#include <QVariantList>

namespace QCrossCache {

class ClientPvt
{
public:
    Client *parent = nullptr;
    ActuatorInterface *interface = nullptr;

    explicit ClientPvt(Client *parent, ActuatorInterface *interface)
    {
        this->parent = parent;
        this->interface = interface;
        if (this->interface != nullptr)
            this->interface->setParent(parent);
    }

    virtual ~ClientPvt()
    {
        if (this->interface != nullptr)
            delete this->interface;
    }
};

Client::Client(QObject *parent) : QObject{parent}
{
    auto acLocal = ActuatorManager::instance().interfaceCreate(QByteArrayLiteral("local"));
    this->p = new ClientPvt(this, acLocal);
}

Client::Client(const QByteArray &dataGroup, QObject *parent) : QObject{parent}
{
    Q_UNUSED(dataGroup);
    auto acLocal = ActuatorManager::instance().interfaceCreate(QByteArrayLiteral("local"));
    acLocal->setDataGroup(dataGroup);
    this->p = new ClientPvt(this, acLocal);
}

Client::Client(ActuatorInterface *interface, QObject *parent) : QObject{parent}
{
    this->p = new ClientPvt(this, interface);
}

Client::~Client()
{
    delete p;
}

Server *Client::server()
{

    if (p->interface == nullptr)
        return nullptr;
    return p->interface->server();
}

const QByteArray &Client::dataGroup() const
{

    if (p->interface == nullptr) {
        static QByteArray dataGroup;
        return dataGroup;
    }
    return p->interface->dataGroup();
}

bool Client::connect()
{

    if (p->interface == nullptr)
        return false;
    return p->interface->connect();
}

bool Client::disconnect()
{

    if (p->interface == nullptr)
        return false;
    return p->interface->disconnect();
}

bool Client::isConnected()
{

    if (p->interface == nullptr)
        return false;
    return p->interface->isConnected();
}

bool Client::clear()
{

    if (p->interface == nullptr)
        return false;
    return p->interface->clear();
}

bool Client::exists(const QByteArray &key)
{

    if (p->interface == nullptr)
        return false;
    return p->interface->exists(key);
}

bool Client::put(const QByteArray &key, const QByteArray &data, const quint64 expiration)
{

    if (p->interface == nullptr)
        return false;
    return p->interface->put(key, data, expiration);
}

QByteArray Client::get(const QByteArray &key)
{

    if (p->interface == nullptr)
        return {};
    return p->interface->get(key);
}

QByteArray Client::take(const QByteArray &key)
{

    if (p->interface == nullptr)
        return {};
    return p->interface->take(key);
}

bool Client::remove(const QByteArray &key)
{

    if (p->interface == nullptr)
        return false;
    return p->interface->remove(key);
}

QVector<QByteArray> Client::list(const QByteArray &key)
{

    if (p->interface == nullptr)
        return {};
    return p->interface->list(key);
}

QVector<QByteArray> Client::listKeys()
{

    if (p->interface == nullptr)
        return {};
    return p->interface->listKeys();
}

Client *clientForLocal(QObject *parent)
{
    auto interface = ActuatorManager::instance().interfaceCreate(QByteArrayLiteral("local"));
    if (interface == nullptr)
        return nullptr;

    return new Client(interface, parent);
}

Client *clientForMemcached(QObject *parent)
{
    auto interface = ActuatorManager::instance().interfaceCreate(QByteArrayLiteral("mancached"));
    if (interface == nullptr)
        return nullptr;

    return new Client(interface, parent);
}

Client *clientForMongoDb(QObject *parent)
{
    auto interface = ActuatorManager::instance().interfaceCreate(QByteArrayLiteral("mongodb"));
    if (interface == nullptr)
        return nullptr;
    return new Client(interface, parent);
}

Client *clientForRedis(QObject *parent)
{
    auto interface = ActuatorManager::instance().interfaceCreate(QByteArrayLiteral("redis"));
    if (interface == nullptr)
        return nullptr;
    return new Client(interface, parent);
}

} // namespace QCrossCache
