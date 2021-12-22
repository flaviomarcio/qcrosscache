#include "./p_qcrosscache_cache_request.h"
#include "./p_qcrosscache_cache_repository.h"

QCrossCache::CacheRequest::CacheRequest():QThread(nullptr)
{

}

QCrossCache::CacheRequest::~CacheRequest()
{

}

void QCrossCache::CacheRequest::run()
{
    QObject::connect(this, &CacheRequest::repositoryCacheClear   , this->repository, &CacheRepository::cacheClear   );
    QObject::connect(this, &CacheRequest::repositoryCacheGet     , this->repository, &CacheRepository::cacheGet     );
    QObject::connect(this, &CacheRequest::repositoryCacheList    , this->repository, &CacheRepository::cacheList    );
    QObject::connect(this, &CacheRequest::repositoryCacheListKeys, this->repository, &CacheRepository::cacheListKeys);
    QObject::connect(this, &CacheRequest::repositoryCachePut     , this->repository, &CacheRepository::cachePut     );
    QObject::connect(this, &CacheRequest::repositoryCacheRemove  , this->repository, &CacheRepository::cacheRemove  );
    QObject::connect(this, &CacheRequest::repositoryCacheTake    , this->repository, &CacheRepository::cacheTake    );

    QObject::connect(this, &CacheRequest::cacheClear   , this,  &CacheRequest::onCacheClear   );
    QObject::connect(this, &CacheRequest::cacheGet     , this,  &CacheRequest::onCacheGet     );
    QObject::connect(this, &CacheRequest::cacheList    , this,  &CacheRequest::onCacheList    );
    QObject::connect(this, &CacheRequest::cacheListKeys, this,  &CacheRequest::onCacheListKeys);
    QObject::connect(this, &CacheRequest::cachePut     , this,  &CacheRequest::onCachePut     );
    QObject::connect(this, &CacheRequest::cacheRemove  , this,  &CacheRequest::onCacheRemove  );
    QObject::connect(this, &CacheRequest::cacheTake    , this,  &CacheRequest::onCacheTake    );
    QObject::connect(this, &CacheRequest::responseData , this,  &CacheRequest::onResponseData );
    QObject::connect(this, &CacheRequest::responseList , this,  &CacheRequest::onResponseList );

    this->exec();

    QObject::connect(this, &CacheRequest::repositoryCacheClear   , this->repository, &CacheRepository::cacheClear   );
    QObject::connect(this, &CacheRequest::repositoryCacheGet     , this->repository, &CacheRepository::cacheGet     );
    QObject::connect(this, &CacheRequest::repositoryCacheList    , this->repository, &CacheRepository::cacheList    );
    QObject::connect(this, &CacheRequest::repositoryCacheListKeys, this->repository, &CacheRepository::cacheListKeys);
    QObject::connect(this, &CacheRequest::repositoryCachePut     , this->repository, &CacheRepository::cachePut     );
    QObject::connect(this, &CacheRequest::repositoryCacheRemove  , this->repository, &CacheRepository::cacheRemove  );
    QObject::connect(this, &CacheRequest::repositoryCacheTake    , this->repository, &CacheRepository::cacheTake    );

    QObject::disconnect(this, &CacheRequest::cacheClear   , this,  &CacheRequest::onCacheClear   );
    QObject::disconnect(this, &CacheRequest::cacheGet     , this,  &CacheRequest::onCacheGet     );
    QObject::disconnect(this, &CacheRequest::cacheList    , this,  &CacheRequest::onCacheList    );
    QObject::disconnect(this, &CacheRequest::cacheListKeys, this,  &CacheRequest::onCacheListKeys);
    QObject::disconnect(this, &CacheRequest::cachePut     , this,  &CacheRequest::onCachePut     );
    QObject::disconnect(this, &CacheRequest::cacheRemove  , this,  &CacheRequest::onCacheRemove  );
    QObject::disconnect(this, &CacheRequest::cacheTake    , this,  &CacheRequest::onCacheTake    );
    QObject::disconnect(this, &CacheRequest::responseData , this,  &CacheRequest::onResponseData );
    QObject::disconnect(this, &CacheRequest::responseList , this,  &CacheRequest::onResponseList );
}

QCrossCache::CacheRequest &QCrossCache::CacheRequest::start(CacheRepository *repository)
{
    this->repository=repository;
    this->data.clear();
    this->list.clear();
    QThread::start();
    while(this->eventDispatcher()==nullptr)
        QThread::msleep(1);
    return*this;
}

const QByteArray &QCrossCache::CacheRequest::getData() const
{
    return this->data;
}

const QVector<QByteArray> &QCrossCache::CacheRequest::getList() const
{
    return this->list;
}

void QCrossCache::CacheRequest::onResponseData(const QByteArray &data)
{
    this->data=data;
    emit requestFinished(this);
    this->quit();
}

void QCrossCache::CacheRequest::onResponseList(const QVector<QByteArray> &list)
{
    this->list=list;
    emit requestFinished(this);
    this->quit();
}

void QCrossCache::CacheRequest::onCacheClear()
{
    emit repositoryCacheClear();
}

void QCrossCache::CacheRequest::onCachePut(const QByteArray &key, const QByteArray &data, const quint64 expiration)
{
    emit repositoryCachePut(key, data, expiration);
}

void QCrossCache::CacheRequest::onCacheRemove(const QByteArray &key)
{
    emit repositoryCacheRemove(key);
}

void QCrossCache::CacheRequest::onCacheGet(const QByteArray &key)
{
    emit repositoryCacheGet(key);
}

void QCrossCache::CacheRequest::onCacheTake(const QByteArray &key)
{
    emit repositoryCacheTake(key);
}

void QCrossCache::CacheRequest::onCacheList(const QByteArray &key)
{
    emit repositoryCacheList(key);
}

void QCrossCache::CacheRequest::onCacheListKeys()
{
    emit repositoryCacheListKeys();
}
