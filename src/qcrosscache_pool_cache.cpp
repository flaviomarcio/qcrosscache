#include "./qcrosscache_pool_cache.h"
#include <QCoreApplication>

namespace QCrossCache {

static PoolCache*__instance=nullptr;

static void deinit()
{
    __instance->quit();
    __instance->wait();
    __instance->deleteLater();
    __instance=nullptr;
}

static void init()
{
    __instance=new PoolCache();
    __instance->setObjectName(__instance->metaObject()->className());
    __instance->start();
    qAddPostRoutine(deinit);
}

Q_COREAPP_STARTUP_FUNCTION(init);

#define dPvt()\
auto&p = *reinterpret_cast<PoolCachePvt*>(this->p)


typedef QHash<QByteArray,QByteArray> PoolCacheItem;
typedef QHash<QByteArray,PoolCacheItem*> PoolCacheGroup;

class PoolCachePvt{
public:
    PoolCache*parent=nullptr;
    QByteArray dataGroup;
    PoolCacheGroup*cacheGroup=nullptr;
    explicit PoolCachePvt(PoolCache *parent)
    {
        this->parent=parent;
    }

    virtual ~PoolCachePvt()
    {
    }

    void init()
    {
        this->cacheGroup=new PoolCacheGroup();
    }

    void clear()
    {
        if(this->cacheGroup==nullptr)
            return;
        auto vList=this->cacheGroup->values();
        for(auto&v:vList)
            delete v;
        delete this->cacheGroup;
        this->cacheGroup=nullptr;
    }
};

PoolCache::PoolCache(QObject *parent) : QThread(parent)
{
    this->p=new PoolCachePvt(this);
}

PoolCache::~PoolCache()
{
    dPvt();
    delete&p;
}

PoolCache &PoolCache::instance()
{
    return*__instance;
}

void PoolCache::run()
{
    dPvt();
    p.init();
    this->exec();
    p.clear();
}

void PoolCache::cacheGet(const QByteArray &dataGroup, const QByteArray &key, PoolCacheResponseData response)
{
    dPvt();
    auto cacheList=p.cacheGroup->value(dataGroup);

    if(cacheList==nullptr){
        response(QByteArray());
        return;
    }

    auto data=cacheList->value(key);
    response(data);
}

void PoolCache::cachePut(const QByteArray &dataGroup, const QByteArray &key, const QByteArray &data)
{
    dPvt();
    auto cacheList=p.cacheGroup->value(dataGroup);

    if(cacheList==nullptr){
        cacheList=new PoolCacheItem();
        p.cacheGroup->insert(dataGroup,cacheList);
    }
    cacheList->insert(key, data);
}

void PoolCache::cacheRemove(const QByteArray &dataGroup, const QByteArray &key)
{
    dPvt();
    auto cacheList=p.cacheGroup->value(dataGroup);

    if(cacheList==nullptr)
        return;

    cacheList->remove(key);
}

void PoolCache::cacheList(const QByteArray &dataGroup, const QByteArray&key,PoolCacheResponseKeys response)
{
    dPvt();
    auto cacheList=p.cacheGroup->value(dataGroup);

    if(cacheList==nullptr){
        response(QList<QByteArray>{});
        return;
    }

    QList<QByteArray> list;
    QHashIterator<QByteArray, QByteArray> i(*cacheList);
    while(i.hasNext()){
        i.next();
        if(i.key().startsWith(key))
            list<<i.key();
    }
    response(list);
}

void PoolCache::cacheListKeys(const QByteArray &dataGroup, const PoolCacheResponseKeys response)
{
    dPvt();
    auto cacheList=p.cacheGroup->value(dataGroup);

    if(cacheList==nullptr){
        response(QList<QByteArray>());
        return;
    }

    auto v=cacheList->keys();
    response(v);
}

PoolCache&PoolCache::clear()
{
    dPvt();
    p.clear();
    return*this;
}

}
