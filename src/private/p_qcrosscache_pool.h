#pragma once

#include <QObject>
#include <QThread>
#include <QVariant>
#include <QMutex>
#include "../qcrosscache_pool.h"
#include "../qcrosscache_types.h"

namespace QCrossCache {

class CacheRepository;
class CacheRequest;

//!
//! \brief The PoolPvt class
//!
class PoolPvt{
public:
    QMutex mutexCache;
    QHash<QByteArray, CacheRepository*> hashRepository;
    QVector<CacheRequest*> requestList;
    Pool*parent=nullptr;
    bool started=false;
    explicit PoolPvt(Pool *parent);

    virtual ~PoolPvt();

    void start();

    void stop();

    bool isStarted();

    QVector<QByteArray> cacheGroups();

    void cacheClearAll();

    void cacheClear(const QByteArray&dataGroup);

    void cachePut(const QByteArray&dataGroup, const QByteArray&key, const QByteArray&data, const quint64 expiration);

    void cacheRemove(const QByteArray&dataGroup, const QByteArray&key);

    const QByteArray cacheGet(const QByteArray&dataGroup, const QByteArray&key);

    const QByteArray cacheTake(const QByteArray&dataGroup, const QByteArray&key);

    const QVector<QByteArray> cacheList(const QByteArray&dataGroup, const QByteArray &key);

    const QVector<QByteArray> cacheListKeys(const QByteArray&dataGroup);

private:
    CacheRepository*cacheRepository(const QByteArray&dataGroup);

    CacheRequest*cacheRequest(const QByteArray&dataGroup);
private slots:
    void onrequestFinished(CacheRequest*request);
};

}
