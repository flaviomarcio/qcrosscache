#include "./p_qcrosscache_pool.h"
#include "./p_qcrosscache_cache_repository.h"
#include "./p_qcrosscache_cache_request.h"
#include <QCoreApplication>
#include <QDateTime>
#include <QTimer>

namespace QCrossCache {

PoolPvt::PoolPvt(Pool *parent)
{
    this->parent=parent;
}

PoolPvt::~PoolPvt()
{
    this->stop();
}

void PoolPvt::start()
{
    if(started)
        return;
    this->stop();
    started=true;
}

void PoolPvt::stop()
{
    QMutexLocker locker(&mutexCache);
    for(auto&thread:hashRepository){
        thread->quit();
    }
    for(auto&thread:hashRepository){
        thread->wait();
        delete thread;
    }
    this->hashRepository.clear();
}

bool PoolPvt::isStarted()
{
    return this->started;
}

QVector<QByteArray> PoolPvt::cacheGroups()
{
    return QVector<QByteArray>::fromList(this->hashRepository.keys());
}

void PoolPvt::cacheClearAll()
{
    auto dataGroupList=this->hashRepository.keys();
    for(auto&dataGroup:dataGroupList){
        auto request=this->cacheRequest(dataGroup);
        if(request==nullptr)
            return;
        emit request->cacheClear();
        request->wait();
    }
}

void PoolPvt::cacheClear(const QByteArray &dataGroup)
{
    auto request=this->cacheRequest(dataGroup);
    if(request==nullptr)
        return;
    emit request->cacheClear();
}

void PoolPvt::cachePut(const QByteArray &dataGroup, const QByteArray &key, const QByteArray &data, const quint64 expiration)
{
    auto request=this->cacheRequest(dataGroup);
    if(request==nullptr)
        return;
    emit request->cachePut(key, data, expiration);
}

void PoolPvt::cacheRemove(const QByteArray &dataGroup, const QByteArray &key)
{
    auto request=this->cacheRequest(dataGroup);
    if(request==nullptr)
        return;
    emit request->cacheRemove(key);
}

const QByteArray PoolPvt::cacheGet(const QByteArray &dataGroup, const QByteArray &key)
{
    auto request=this->cacheRequest(dataGroup);
    if(request==nullptr)
        return {};
    emit request->cacheGet(key);
    request->wait();
    return request->getData();
}

const QByteArray PoolPvt::cacheTake(const QByteArray &dataGroup, const QByteArray &key)
{
    auto request=this->cacheRequest(dataGroup);
    if(request==nullptr)
        return {};
    emit request->cacheTake(key);
    request->wait();
    return request->getData();
}

const QVector<QByteArray> PoolPvt::cacheList(const QByteArray &dataGroup, const QByteArray &key)
{
    auto request=this->cacheRequest(dataGroup);
    if(request==nullptr)
        return {};
    emit request->cacheList(key);
    request->wait();
    return request->getList();
}

const QVector<QByteArray> PoolPvt::cacheListKeys(const QByteArray &dataGroup)
{
    auto request=this->cacheRequest(dataGroup);
    if(request==nullptr)
        return {};
    emit request->cacheListKeys();
    request->wait();
    return request->getList();
}

CacheRepository *PoolPvt::cacheRepository(const QByteArray &dataGroup)
{
    QMutexLocker locker(&mutexCache);
    auto repository=this->hashRepository.value(dataGroup.toLower());
    if(repository==nullptr){
        repository=new CacheRepository();
        repository->start();
        while(repository->eventDispatcher()==nullptr)
            QThread::msleep(1);
        this->hashRepository.insert(dataGroup.toLower(),repository);
    }
    return repository;
}

CacheRequest *PoolPvt::cacheRequest(const QByteArray &dataGroup)
{
    auto repository=this->cacheRepository(dataGroup);
    if(repository==nullptr)
        return nullptr;
    auto thread=requestList.isEmpty()?nullptr:requestList.takeFirst();
    if(thread==nullptr)
        thread=new CacheRequest();
    return&thread->start(repository);
}

void PoolPvt::onrequestFinished(CacheRequest *request)
{
    request->quit();
    request->wait();
    this->requestList<<request;
}


}
