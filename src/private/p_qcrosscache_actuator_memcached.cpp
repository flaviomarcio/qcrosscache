//refereces
//  http://manpages.ubuntu.com/manpages/trusty/man3/libmemcached.3.html

#include "./p_qcrosscache_actuator_memcached.h"
#include "../qcrosscache_server.h"
#include <QDebug>

#ifdef Q_CROSSCACHE_MEMCACHED
#include <iostream>
#include <libmemcached/memcached.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <QTcpSocket>
extern "C" {
#include <libmemcached/memcached.h>
}
#endif

namespace QCrossCache {

class ActuatorMemcachedPvt
{
public:
    ActuatorMemcached *parent = nullptr;
#ifdef Q_CROSSCACHE_MEMCACHED
    memcached_server_st *memc_server_st = nullptr;
    memcached_st *memc_st = nullptr;
    bool memc_connected = false;
    uint32_t memc_flag = 0;
#endif
    explicit ActuatorMemcachedPvt(ActuatorMemcached *parent) { this->parent = parent; }

    virtual ~ActuatorMemcachedPvt() { this->disconnect(); }

    bool disconnect()
    {
#ifdef Q_CROSSCACHE_MEMCACHED
        if (!this->memc_connected)
            return true;
        this->memc_connected = false;
        memcached_server_free(this->memc_server_st);
#endif
        return true;
    }
};

ActuatorMemcached::ActuatorMemcached(QObject *parent) : ActuatorInterface(parent)
{
    this->p = new ActuatorMemcachedPvt{this};
}

ActuatorMemcached::ActuatorMemcached(Server *server, const QByteArray &dataGroup)
    : ActuatorInterface(server, dataGroup)
{
    this->p = new ActuatorMemcachedPvt{this};
}

ActuatorMemcached::~ActuatorMemcached()
{
    delete p;
}

bool ActuatorMemcached::connect()
{
#ifndef Q_CROSSCACHE_MEMCACHED
    return ActuatorInterface::connect();
#else

    if (p->memc_connected)
        return true;
    memcached_return rc;
    p->memc_st = memcached_create(nullptr);

    auto hostName = this->server()->hostName();
    auto portNumber = this->server()->portNumber().toInt();
    if (portNumber <= 0)
        portNumber = MEMCACHED_DEFAULT_PORT;

    p->memc_server_st = memcached_server_list_append(nullptr, hostName, portNumber, &rc);
    rc = memcached_server_push(p->memc_st, p->memc_server_st);
    if (rc == MEMCACHED_SUCCESS) {
        p->memc_connected = true;
        return p->memc_connected;
    }
    qDebug() << "couldn't add server\n";
    return false;
#endif
}

bool ActuatorMemcached::disconnect()
{
#ifndef Q_CROSSCACHE_MEMCACHED
    return ActuatorInterface::disconnect();
#else

    return p->disconnect();
#endif
}

bool ActuatorMemcached::isConnected()
{
#ifndef Q_CROSSCACHE_MEMCACHED
    return ActuatorInterface::isConnected();
#else

    return p->memc_connected;
#endif
}

bool ActuatorMemcached::clear()
{
#ifndef Q_CROSSCACHE_MEMCACHED
    return ActuatorInterface::clear();
#else

    if (!p->memc_connected)
        return false;
    auto rc = memcached_flush(p->memc_st, 0);
    if (rc != MEMCACHED_SUCCESS)
        return false;
    return true;
#endif
}

bool ActuatorMemcached::exists(const QByteArray &key)
{
#ifndef Q_CROSSCACHE_MEMCACHED
    return ActuatorInterface::exists(key);
#else

    if (!p->memc_connected)
        return false;
    auto ckey = key.toStdString();
    auto cgroup_key = this->dataGroup().toStdString();
    auto rc = memcached_exist_by_key(p->memc_st,
                                     cgroup_key.c_str(),
                                     cgroup_key.length(),
                                     ckey.c_str(),
                                     ckey.length());
    if (rc == MEMCACHED_SUCCESS)
        return true;
    return false;
#endif
}

bool ActuatorMemcached::put(const QByteArray &key, const QByteArray &data, const quint64 expiration)
{
#ifndef Q_CROSSCACHE_MEMCACHED
    return ActuatorInterface::put(key, data, expiration);
#else

    if (!p->memc_connected)
        return false;
    auto ckey = key.toStdString();
    auto cvalue = data.toStdString();
    auto cgroup_key = this->dataGroup().toStdString();
    auto rc = memcached_set_by_key(p->memc_st,
                                   cgroup_key.c_str(),
                                   cgroup_key.length(),
                                   ckey.c_str(),
                                   ckey.length(),
                                   cvalue.c_str(),
                                   cvalue.length(),
                                   expiration,
                                   p->memc_flag);
    if (rc == MEMCACHED_SUCCESS)
        return true;
    return false;
#endif
}

QByteArray ActuatorMemcached::get(const QByteArray &key)
{
#ifndef Q_CROSSCACHE_MEMCACHED
    return ActuatorInterface::get(key);
#else

    if (!p->memc_connected)
        return {};
    auto ckey = key.toStdString();
    auto cgroup_key = this->dataGroup().toStdString();
    memcached_return rc;
    size_t value_length = 0;
    char *result = memcached_get_by_key(p->memc_st,
                                        cgroup_key.c_str(),
                                        cgroup_key.length(),
                                        ckey.c_str(),
                                        ckey.length(),
                                        &value_length,
                                        &p->memc_flag,
                                        &rc);
    if (rc != MEMCACHED_SUCCESS)
        return {};
    return result;
#endif
}

QByteArray ActuatorMemcached::take(const QByteArray &key)
{
#ifndef Q_CROSSCACHE_MEMCACHED
    return ActuatorInterface::take(key);
#else

    if (!p->memc_connected)
        return {};
    auto ckey = key.toStdString();
    memcached_return rc;
    auto cgroup_key = this->dataGroup().toStdString();
    size_t value_length = 0;
    char *result = memcached_get_by_key(p->memc_st,
                                        cgroup_key.c_str(),
                                        cgroup_key.length(),
                                        ckey.c_str(),
                                        ckey.length(),
                                        &value_length,
                                        &p->memc_flag,
                                        &rc);
    if (rc != MEMCACHED_SUCCESS)
        return {};

    rc = memcached_delete_by_key(p->memc_st,
                                 cgroup_key.c_str(),
                                 cgroup_key.length(),
                                 ckey.c_str(),
                                 ckey.length(),
                                 0);
    if (rc != MEMCACHED_SUCCESS)
        return {};
    return result;
#endif
}

bool ActuatorMemcached::remove(const QByteArray &key)
{
#ifndef Q_CROSSCACHE_MEMCACHED
    return ActuatorInterface::remove(key);
#else

    if (!p->memc_connected)
        return {};
    auto ckey = key.toStdString();
    auto cgroup_key = this->dataGroup().toStdString();
    auto rc = memcached_delete_by_key(p->memc_st,
                                      cgroup_key.c_str(),
                                      cgroup_key.length(),
                                      ckey.c_str(),
                                      ckey.length(),
                                      0);
    if (rc == MEMCACHED_SUCCESS)
        return true;
    return false;
#endif
}

QVector<QByteArray> ActuatorMemcached::list(const QByteArray &key)
{
#ifndef Q_CROSSCACHE_MEMCACHED
    return ActuatorInterface::list(key);
#else
    QVector<QByteArray> __return;
    auto hostName = this->server()->hostName();
    auto portNumber = this->server()->portNumber().toInt();
    if (portNumber <= 0)
        portNumber = MEMCACHED_DEFAULT_PORT;
    auto thread = new ActuatorMemcachedRequest(hostName,
                                               portNumber,
                                               QByteArrayLiteral("lru_crawler metadump all"));
    thread->start().wait();

    for (auto &line : thread->responseBody()) {
        //lru_crawler metadump all
        //    key=AAAA exp=-1 la=1640459601 cas=62 fetch=yes cls=1 size=69
        //    key=BBBB exp=-1 la=1640459909 cas=63 fetch=no cls=1 size=67
        //    key=CCCCC exp=-1 la=1640459912 cas=64 fetch=no cls=1 size=69
        //    key=AAAX exp=-1 la=1640459916 cas=65 fetch=no cls=1 size=68
        //    END
        if (!line.startsWith(QByteArrayLiteral("key")))
            continue;
        auto column = line.split(' ');
        if (column.isEmpty())
            continue;
        auto value = column.first().split('=').last();

        if (value.isEmpty())
            continue;

        if (!key.isEmpty() && !value.startsWith(key))
            continue;

        __return << value;
    }
    delete thread;
    return __return;
#endif
}

QVector<QByteArray> ActuatorMemcached::listKeys()
{
    return this->list(QByteArray());
}

} // namespace QCrossCache
