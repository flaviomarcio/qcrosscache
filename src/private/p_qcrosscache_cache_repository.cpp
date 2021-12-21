#include "./p_qcrosscache_cache_repository.h"
#include "./p_qcrosscache_cache_request.h"
#include <QDateTime>

namespace QCrossCache {

#define dPvt()\
auto&p = *reinterpret_cast<CacheRepositoryPvt*>(this->p)

struct CacheItem{
public:
    QByteArray data;
    QDateTime expiration;

    explicit CacheItem(){
    }

    void setData(const QByteArray&data, const qint64 expirationMs=0)
    {
        this->data=data;
        if(expirationMs<=0)
            expiration=QDateTime();
        else
            expiration=QDateTime::currentDateTime().addMSecs(expirationMs);
    }

    QByteArray toData()const
    {
        if(expiration.isValid() && expiration<QDateTime::currentDateTime())
            return {};
        return data;
    }
};

typedef QHash<QByteArray, CacheItem> CacheCollection;

class CacheRepositoryPvt :public QObject{
public:
    CacheRepository*parent=nullptr;
    QByteArray dataGroup;
    CacheCollection cacheCollection;
    explicit CacheRepositoryPvt(CacheRepository *parent):QObject(parent)
    {
        this->parent=parent;
        QObject::connect(parent, &CacheRepository::cacheGet, this, &CacheRepositoryPvt::cacheGet);
        QObject::connect(parent, &CacheRepository::cacheTake, this, &CacheRepositoryPvt::cacheTake);
        QObject::connect(parent, &CacheRepository::cachePut, this, &CacheRepositoryPvt::cachePut);
        QObject::connect(parent, &CacheRepository::cacheRemove, this, &CacheRepositoryPvt::cacheRemove);
        QObject::connect(parent, &CacheRepository::cacheList, this, &CacheRepositoryPvt::cacheList);
        QObject::connect(parent, &CacheRepository::cacheListKeys, this, &CacheRepositoryPvt::cacheListKeys);
        QObject::connect(parent, &CacheRepository::cacheClear, this, &CacheRepositoryPvt::cacheClear);
    }

    virtual ~CacheRepositoryPvt()
    {
    }

public slots:

    void cacheGet(const QByteArray &key, CacheRequest*threadResponse)
    {
        const auto&item=this->cacheCollection.value(key);
        emit threadResponse->responseData(item.data);
    }

    void cacheTake(const QByteArray &key, CacheRequest*threadResponse)
    {
        if(this->cacheCollection.contains(key)){
            emit threadResponse->responseData("");
            return;
        }
        const auto&item=this->cacheCollection.take(key);
        emit threadResponse->responseData(item.data);
    }

    void cachePut(const QByteArray &key, const QByteArray &data, const quint64 expirationMs)
    {
        auto&item=this->cacheCollection[key];
        item.setData(data, expirationMs);
    }

    void cacheRemove(const QByteArray &key)
    {
        this->cacheCollection.remove(key);
    }

    void cacheList(const QByteArray&key, CacheRequest*threadResponse)
    {
        QList<QByteArray> list;
        QHashIterator<QByteArray, CacheItem> i(this->cacheCollection);
        while(i.hasNext()){
            i.next();
            if(i.key().startsWith(key))
                list<<i.key();
        }
        emit threadResponse->responseList(list);
    }

    void cacheListKeys(CacheRequest*threadResponse)
    {
        auto list=this->cacheCollection.keys();
        emit threadResponse->responseList(list);
    }

    void cacheClear()
    {
        cacheCollection.clear();
    }

};

CacheRepository::CacheRepository(QObject *parent) : QThread(parent)
{
    this->p=new CacheRepositoryPvt(this);
}

CacheRepository::~CacheRepository()
{
    dPvt();
    delete&p;
}

void CacheRepository::run()
{
    this->exec();
}


}
