#include "./private/p_qcrosscache_pool.h"
#include <QCoreApplication>

namespace QCrossCache {

Q_GLOBAL_STATIC(Pool, staticPool)

static void deinit()
{
    staticPool->stop();
}

static void init()
{
    staticPool->start();
    qAddPostRoutine(deinit);
}

Q_COREAPP_STARTUP_FUNCTION(init)


Pool::Pool(QObject *parent) : QObject{parent}, p{new PoolPvt{this}}
{
}

Pool::~Pool()
{
    delete p;
}

Pool &Pool::start()
{
    p->start();
    return *this;
}

Pool &Pool::stop()
{
    p->stop();
    return *this;
}

bool Pool::isStarted()
{
    return p->isStarted();
}

Pool &Pool::instance()
{
    return *staticPool;
}

Pool &Pool::cacheClearAll()
{
    p->cacheClearAll();
    return *this;
}

Pool &Pool::cacheClear(const QByteArray &dataGroup)
{
    p->cacheClear(dataGroup);
    return *this;
}

Pool &Pool::cachePut(const QByteArray &dataGroup,
                     const QByteArray &key,
                     const QByteArray &data,
                     const quint64 expiration)
{
    p->cachePut(dataGroup, key, data, expiration);
    return *this;
}

Pool &Pool::cacheRemove(const QByteArray &dataGroup, const QByteArray &key)
{
    p->cacheRemove(dataGroup, key);
    return *this;
}

QByteArray Pool::cacheGet(const QByteArray &dataGroup, const QByteArray &key)
{
    return p->cacheGet(dataGroup, key);
}

QByteArray Pool::cacheTake(const QByteArray &dataGroup, const QByteArray &key)
{
    return p->cacheTake(dataGroup, key);
}

QVector<QByteArray> Pool::cacheList(const QByteArray &dataGroup, const QByteArray &key)
{
    return p->cacheList(dataGroup, key);
}

QVector<QByteArray> Pool::cacheListKeys(const QByteArray &dataGroup)
{
    return p->cacheListKeys(dataGroup);
}

} // namespace QCrossCache
