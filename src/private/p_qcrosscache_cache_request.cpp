#include "p_qcrosscache_cache_request.h"
#include "p_qcrosscache_cache_repository.h"

QCrossCache::CacheRequest::CacheRequest():QThread(nullptr)
{
    QObject::connect(this, &CacheRequest::responseData , this,  &CacheRequest::onResponseData );
    QObject::connect(this, &CacheRequest::responseList , this,  &CacheRequest::onResponseList );
    QObject::connect(this, &CacheRequest::cacheGet     , this,  &CacheRequest::onCacheGet     );
    QObject::connect(this, &CacheRequest::cacheTake    , this,  &CacheRequest::onCacheTake    );
    QObject::connect(this, &CacheRequest::cacheList    , this,  &CacheRequest::onCacheList    );
    QObject::connect(this, &CacheRequest::cacheListKeys, this,  &CacheRequest::onCacheListKeys);
}

QCrossCache::CacheRequest::~CacheRequest()
{

}

void QCrossCache::CacheRequest::run()
{
    this->exec();
}

QCrossCache::CacheRequest &QCrossCache::CacheRequest::start(CacheRepository *repository)
{
    this->data.clear();
    this->list.clear();
    this->repository=repository;
    QThread::start();
    while(this->eventDispatcher()!=nullptr)
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
    this->quit();
    emit requestFineshed(this);
}

void QCrossCache::CacheRequest::onResponseList(const QVector<QByteArray> &list)
{
    this->list=list;
    emit requestFineshed(this);
}

void QCrossCache::CacheRequest::onCacheGet(const QByteArray &key)
{
    emit repository->cacheGet(key, this);
}

void QCrossCache::CacheRequest::onCacheTake(const QByteArray &key)
{
    emit repository->cacheTake(key, this);
}

void QCrossCache::CacheRequest::onCacheList(const QByteArray &key)
{
    emit repository->cacheList(key, this);
}

void QCrossCache::CacheRequest::onCacheListKeys()
{
    emit repository->cacheListKeys(this);
}
