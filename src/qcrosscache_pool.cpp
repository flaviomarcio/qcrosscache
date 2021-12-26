#include "./private/p_qcrosscache_pool.h"
#include <QCoreApplication>

namespace QCrossCache {

static Pool*__instance=nullptr;

static void deinit()
{
    __instance->stop();
    __instance->deleteLater();
    __instance=nullptr;
}

static void init()
{
    __instance=new Pool();
    __instance->setObjectName(__instance->metaObject()->className());
    __instance->start();
    qAddPostRoutine(deinit);
}

Q_COREAPP_STARTUP_FUNCTION(init)

#define dPvt()\
auto&p = *reinterpret_cast<PoolPvt*>(this->p)



Pool::Pool(QObject *parent) : QObject(parent)
{
    this->p=new PoolPvt(this);
}

Pool::~Pool()
{
    dPvt();
    delete&p;
}

Pool &Pool::start()
{
    dPvt();
    p.start();
    return*this;
}

Pool &Pool::stop()
{
    dPvt();
    p.stop();
    return*this;
}

bool Pool::isStarted()
{
    dPvt();
    return p.isStarted();
}

Pool &Pool::instance()
{
    return*__instance;
}

Pool &Pool::cacheClearAll()
{
    dPvt();
    p.cacheClearAll();
    return*this;
}

Pool&Pool::cacheClear(const QByteArray &dataGroup)
{
    dPvt();
    p.cacheClear(dataGroup);
    return*this;
}

Pool&Pool::cachePut(const QByteArray &dataGroup, const QByteArray &key, const QByteArray &data, const quint64 expiration)
{
    dPvt();
    p.cachePut(dataGroup, key, data, expiration);
    return*this;
}

Pool&Pool::cacheRemove(const QByteArray &dataGroup, const QByteArray &key)
{
    dPvt();
    p.cacheRemove(dataGroup, key);
    return*this;
}

QByteArray Pool::cacheGet(const QByteArray &dataGroup, const QByteArray &key)
{
    dPvt();
    return p.cacheGet(dataGroup, key);
}

QByteArray Pool::cacheTake(const QByteArray &dataGroup, const QByteArray &key)
{
    dPvt();
    return p.cacheTake(dataGroup, key);
}

QVector<QByteArray> Pool::cacheList(const QByteArray &dataGroup, const QByteArray&key)
{
    dPvt();
    return p.cacheList(dataGroup, key);
}

QVector<QByteArray> Pool::cacheListKeys(const QByteArray &dataGroup)
{
    dPvt();
    return p.cacheListKeys(dataGroup);
}

}
