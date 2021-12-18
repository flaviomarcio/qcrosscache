#include "./p_qcrosscache_actuator_memcached.h"
#include <QDebug>

extern "C" {
#include <libmemcached/memcached.h>
}

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<ActuatorMemcachedPvt*>(this->p)

class ActuatorMemcachedPvt{
public:
    ActuatorMemcached*parent=nullptr;
    memcached_server_st *servers = nullptr;
    memcached_st *memc;
    memcached_return rc=MEMCACHED_FAILURE;
    int expire_time = 0;
    uint32_t flag = 0;


    explicit ActuatorMemcachedPvt(ActuatorMemcached *parent)
    {
        this->parent=parent;
    }

    virtual ~ActuatorMemcachedPvt()
    {
    }

    bool setCacheData(QString key, QString value)
    {
        auto ckey = key.toStdString();
        char *cvalue = value.toLocal8Bit().data();
        rc = memcached_set_by_key(memc, "g",1, ckey.c_str(), key.length(), cvalue, value.length(), expire_time, flag);
        if(rc==MEMCACHED_SUCCESS) return true;
        else return false;
    }

    bool getCacheData(QString key,QString &value,size_t &value_length,uint32_t &flags)
    {
        qDebug()<<value_length;
        auto ckey = key.toStdString();
        char *result = memcached_get_by_key(memc, "g",1, ckey.c_str(), ckey.length(), &value_length, &flags,&rc);
        if(rc==MEMCACHED_SUCCESS){
            value = QString::fromUtf8(result);
            return true;
        }else return false;

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
    delete&p;
}

bool ActuatorMemcached::connect()
{
    dPvt();
    p.memc = memcached_create(nullptr);
    p.servers = memcached_server_list_append(nullptr, "127.0.0.1", 11211, &p.rc);
    p.rc = memcached_server_push(p.memc, p.servers);
    memcached_free(p.memc);
    if(p.rc==MEMCACHED_SUCCESS)
        return true;
    qDebug()<<"couldn't add server\n";
    return false;
}

bool ActuatorMemcached::disconnect()
{
    dPvt();
    memcached_free(p.memc);
    return false;
}

bool ActuatorMemcached::isConnected()
{
    return false;
}

bool ActuatorMemcached::exists(const QByteArray &key)
{
    dPvt();
    auto ckey = key.toStdString();
    auto cgroup_key=this->dataGroup().toStdString();
    auto rc = memcached_exist_by_key(p.memc, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), ckey.length());
    if(rc==MEMCACHED_SUCCESS)
        return true;
    return false;
}

bool ActuatorMemcached::put(const QByteArray &key, const QByteArray &data)
{
    dPvt();
    auto ckey = key.toStdString();
    auto cvalue = data.toStdString();
    auto cgroup_key=this->dataGroup().toStdString();
    p.rc = memcached_set_by_key(p.memc, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), key.length(), cvalue.c_str(), data.length(), 0/*expire_time*/, 0/*flag*/);
    if(p.rc==MEMCACHED_SUCCESS)
        return true;
    return false;
}

bool ActuatorMemcached::get(const QByteArray &key, QByteArray &data)
{
    dPvt();
    auto ckey = key.toStdString();
    memcached_return rc;
    auto cgroup_key=this->dataGroup().toStdString();
    char *result = memcached_get_by_key(p.memc, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), ckey.length(), 0/*value_length*/, 0/*flags*/, &rc);
    if(rc!=MEMCACHED_SUCCESS)
        return true;
    data = result;
    return true;
}

bool ActuatorMemcached::take(const QByteArray &key, QByteArray &data)
{
    dPvt();
    auto ckey = key.toStdString();
    memcached_return rc;
    auto cgroup_key=this->dataGroup().toStdString();
    char *result = memcached_get_by_key(p.memc, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), ckey.length(), 0/*value_length*/, 0/*flags*/, &rc);
    if(rc!=MEMCACHED_SUCCESS)
        return false;

    data = result;
    rc = memcached_delete_by_key(p.memc, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), ckey.length(), 0/*value_length*/);
    if(rc==MEMCACHED_SUCCESS)
        return true;
    return false;
}

bool ActuatorMemcached::remove(const QByteArray &key)
{
    dPvt();
    auto ckey = key.toStdString();
    auto cgroup_key=this->dataGroup().toStdString();
    auto rc = memcached_delete_by_key(p.memc, cgroup_key.c_str(), cgroup_key.length(), ckey.c_str(), ckey.length(), 0/*value_length*/);
    if(rc==MEMCACHED_SUCCESS)
        return true;
    return false;
}

} // namespace QCrossCache
