//refereces
//  http://manpages.ubuntu.com/manpages/trusty/man3/libmemcached.3.html

#include "./p_qcrosscache_actuator_memcached.h"
#include "../qcrosscache_server.h"
#include <QDebug>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <libmemcached/memcached.h>

extern "C" {
#include <libmemcached/memcached.h>
}

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ActuatorMemcachedPvt*>(this->p)

class ActuatorMemcachedPvt{
public:
    ActuatorMemcached*parent=nullptr;
    memcached_server_st *memc_server_st = nullptr;
    memcached_st *memc_st;
    bool memc_connected=false;
    int expire_time = 0;
    uint32_t memc_flag = 0;
    //size_t value_length=0;
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

ActuatorMemcached::ActuatorMemcached(Server *server, const QByteArray &dataGroup) : ActuatorInterface(server, dataGroup)
{
    this->p=new ActuatorMemcachedPvt(this);
}

ActuatorMemcached::~ActuatorMemcached()
{
    dPvt();
    this->disconnect();
    delete&p;
}

bool ActuatorMemcached::connect()
{
    dPvt();
    if(p.memc_connected)
        return true;
    memcached_return rc;
    p.memc_st = memcached_create(nullptr);

    auto portNumber=this->server()->portNumber().toInt();
    if(portNumber<=0)
        portNumber=MEMCACHED_DEFAULT_PORT;

    p.memc_server_st = memcached_server_list_append(nullptr, this->server()->hostName(), portNumber, &rc);
    rc = memcached_server_push(p.memc_st, p.memc_server_st);
    if(rc==MEMCACHED_SUCCESS){
        p.memc_connected=true;
        return p.memc_connected;
    }
    qDebug()<<"couldn't add server\n";
    return false;
}

bool ActuatorMemcached::disconnect()
{
    dPvt();
    if(!p.memc_connected)
        return true;
    p.memc_connected=false;
    memcached_server_free(p.memc_server_st);
    return true;
}

bool ActuatorMemcached::isConnected()
{
    dPvt();
    return p.memc_connected;
}

bool ActuatorMemcached::clear()
{
    dPvt();
    if(!p.memc_connected)
        return false;
    auto rc=memcached_flush(p.memc_st,0);
    if(rc!=MEMCACHED_SUCCESS)
        return false;
    return true;
}

bool ActuatorMemcached::exists(const QByteArray &key)
{
    dPvt();
    if(!p.memc_connected)
        return false;
    auto ckey = key.toStdString();
    auto cgroup_key=this->dataGroup().toStdString();
    auto rc = memcached_exist_by_key(p.memc_st, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), ckey.length());
    if(rc==MEMCACHED_SUCCESS)
        return true;
    return false;
}

bool ActuatorMemcached::put(const QByteArray &key, const QByteArray &data, const quint64 expiration)
{
    dPvt();
    if(!p.memc_connected)
        return false;
    auto ckey = key.toStdString();
    auto cvalue = data.toStdString();
    auto cgroup_key=this->dataGroup().toStdString();
    auto rc = memcached_set_by_key(p.memc_st, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), ckey.length(), cvalue.c_str(), cvalue.length(), expiration, p.memc_flag);
    if(rc==MEMCACHED_SUCCESS)
        return true;
    return false;
}

QByteArray ActuatorMemcached::get(const QByteArray &key)
{
    dPvt();
    if(!p.memc_connected)
        return {};
    auto ckey = key.toStdString();
    auto cgroup_key=this->dataGroup().toStdString();
    memcached_return rc;
    size_t value_length=0;
    char *result = memcached_get_by_key(p.memc_st, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), ckey.length(), &value_length, &p.memc_flag, &rc);
    if(rc!=MEMCACHED_SUCCESS)
        return {};
    return result;
}

QByteArray ActuatorMemcached::take(const QByteArray &key)
{
    dPvt();
    if(!p.memc_connected)
        return {};
    auto ckey = key.toStdString();
    memcached_return rc;
    auto cgroup_key=this->dataGroup().toStdString();
    size_t value_length=0;
    char *result = memcached_get_by_key(p.memc_st, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), ckey.length(), &value_length, &p.memc_flag, &rc);
    if(rc!=MEMCACHED_SUCCESS)
        return {};

    rc = memcached_delete_by_key(p.memc_st, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), ckey.length(), 0);
    if(rc!=MEMCACHED_SUCCESS)
        return {};
    return result;
}

bool ActuatorMemcached::remove(const QByteArray &key)
{
    dPvt();
    if(!p.memc_connected)
        return {};
    auto ckey = key.toStdString();
    auto cgroup_key=this->dataGroup().toStdString();
    auto rc = memcached_delete_by_key(p.memc_st, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), ckey.length(), 0);
    if(rc==MEMCACHED_SUCCESS)
        return true;
    return false;
}

QVector<QByteArray> ActuatorMemcached::list(const QByteArray &key)
{
    Q_UNUSED(key);
    qWarning()<<tr("no implemented");
    return {};
}

QVector<QByteArray> ActuatorMemcached::listKeys()
{
    qWarning()<<tr("no implemented");
    return {};
}

} // namespace QCrossCache
