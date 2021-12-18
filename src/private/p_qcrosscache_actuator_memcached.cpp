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
    QMetaObject*actuatorMetaObject=nullptr;

    memcached_server_st *servers = nullptr;
    memcached_st *memc;
    memcached_return rc;
    int expire_time = 0;
    uint32_t flag = 0;


    explicit ActuatorMemcachedPvt(ActuatorMemcached *parent)
    {
        this->parent=parent;
    }

    virtual ~ActuatorMemcachedPvt()
    {
    }

    memcached_st *init()
    {
        memcached_st *memcached = nullptr;
        memcached_server_st *cache;
        memcached = memcached_create(nullptr);
        cache = memcached_server_list_append(nullptr,"127.0.0.1",11211,&rc);
        memcached_server_push(memcached,cache);
        memcached_server_list_free(cache);
        return memcached;
    }

    bool addServers()
    {
        memc = memcached_create(nullptr);
        servers = memcached_server_list_append(nullptr,"127.0.0.1",11211,&rc);
        rc = memcached_server_push(memc,servers);

        if(rc==MEMCACHED_SUCCESS){
            qDebug()<<"Added server successfully\n";
            return true;
        }else{
            qDebug()<<"couldn't add server\n";
            return false;
        }
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

QByteArray ActuatorMemcached::service() const
{
    return QByteArray();
}

bool ActuatorMemcached::put(const QByteArray &key, QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorMemcached::get(const QByteArray &key, QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorMemcached::take(const QByteArray &key, QByteArray &data)
{
    Q_UNUSED(key)
    Q_UNUSED(data)
    return false;
}

bool ActuatorMemcached::remove(const QByteArray &key)
{
    Q_UNUSED(key)
    return false;
}

bool ActuatorMemcached::list(const QByteArray &key, QVector<QByteArray> &listKeys)
{
    Q_UNUSED(key)
    Q_UNUSED(listKeys)
    return false;
}

bool ActuatorMemcached::listKeys(const QByteArray &key, QVector<QByteArray> &listKeys)
{
    Q_UNUSED(key)
    Q_UNUSED(listKeys)
    return false;
}

} // namespace QCrossCache
