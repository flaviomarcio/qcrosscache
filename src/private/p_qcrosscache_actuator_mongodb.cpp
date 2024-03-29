//http://mongocxx.org/
//https://docs.mongodb.com/drivers/cxx/
#include "./p_qcrosscache_actuator_mongodb.h"
#include "../qcrosscache_server.h"
#include <QDebug>

namespace QCrossCache {

class ActuatorMongoDbPvt
{
public:
    ActuatorMongoDb *parent = nullptr;
    explicit ActuatorMongoDbPvt(ActuatorMongoDb *parent):parent{parent} {}
    virtual ~ActuatorMongoDbPvt() { this->disconnect(); }
    bool disconnect() { return true; }
};

ActuatorMongoDb::ActuatorMongoDb(QObject *parent) : ActuatorInterface{parent}, p{new ActuatorMongoDbPvt{this}}
{
}

ActuatorMongoDb::ActuatorMongoDb(Server *server, const QByteArray &dataGroup)
    : ActuatorInterface{server, dataGroup}, p{new ActuatorMongoDbPvt{this}}
{
}

ActuatorMongoDb::~ActuatorMongoDb()
{
    delete p;
}

bool ActuatorMongoDb::connect()
{
    return true;
}

bool ActuatorMongoDb::disconnect()
{
    return p->disconnect();
}

bool ActuatorMongoDb::isConnected()
{
    return true;
}

bool ActuatorMongoDb::clear()
{
    return true;
}

bool ActuatorMongoDb::exists(const QByteArray &key)
{
    Q_UNUSED(key)
    return true;
}

bool ActuatorMongoDb::put(const QByteArray &key, const QByteArray &data, const quint64 expiration)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    Q_UNUSED(expiration)
    return true;
}

QByteArray ActuatorMongoDb::get(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

QByteArray ActuatorMongoDb::take(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

bool ActuatorMongoDb::remove(const QByteArray &key)
{
    Q_UNUSED(key)
    return false;
}

QVector<QByteArray> ActuatorMongoDb::list(const QByteArray &key)
{
    Q_UNUSED(key)
    return {};
}

QVector<QByteArray> ActuatorMongoDb::listKeys()
{
    qWarning() << tr("no implemented");
    return {};
}

} // namespace QCrossCache
