#include "./p_qcrosscache_cache_repository.h"
#include "./p_qcrosscache_cache_request.h"

namespace QCrossCache {

struct CacheItem
{
public:
    QByteArray data;
    QDateTime expiration;

    explicit CacheItem() {}

    void setData(const QByteArray &data, const qint64 expirationMs = 0)
    {
        this->data = data;
        if (expirationMs <= 0)
            expiration = QDateTime();
        else
            expiration = QDateTime::currentDateTime().addMSecs(expirationMs);
    }

    QByteArray toData() const
    {
        if (expiration.isValid() && expiration < QDateTime::currentDateTime())
            return {};
        return data;
    }
};

typedef QHash<QByteArray, CacheItem> CacheCollection;

class CacheRepositoryPvt : public QObject
{
public:
    CacheRepository *parent = nullptr;
    QByteArray dataGroup;
    CacheCollection cacheCollection;
    explicit CacheRepositoryPvt(CacheRepository *parent) : QObject{parent}, parent{parent}
    {
    }

};

CacheRepository::CacheRepository(QObject *parent) : QThread{parent}, p{new CacheRepositoryPvt{this}}
{
}

CacheRepository::~CacheRepository()
{
    delete p;
}

void CacheRepository::run()
{
    this->exec();
}

void CacheRepository::cacheGet(const QByteArray &key)
{
    auto threadResponse = dynamic_cast<CacheRequest *>(QObject::sender());
    if (threadResponse == nullptr)
        return;
    const auto &item = p->cacheCollection.value(key);
    emit threadResponse->responseData(item.data);
}

void CacheRepository::cacheTake(const QByteArray &key)
{
    auto threadResponse = dynamic_cast<CacheRequest *>(QObject::sender());
    if (threadResponse == nullptr)
        return;
    if (!p->cacheCollection.contains(key)) {
        emit threadResponse->responseData("");
        return;
    }
    const auto &item = p->cacheCollection.take(key);
    emit threadResponse->responseData(item.data);
}

void CacheRepository::cachePut(const QByteArray &key,
                               const QByteArray &data,
                               const quint64 expiration)
{
    auto &item = p->cacheCollection[key];
    item.setData(data, expiration);
}

void CacheRepository::cacheRemove(const QByteArray &key)
{
    p->cacheCollection.remove(key);
}

void CacheRepository::cacheList(const QByteArray &key)
{
    auto threadResponse = dynamic_cast<CacheRequest *>(QObject::sender());
    if (threadResponse == nullptr)
        return;
    QVector<QByteArray> list;
    QHashIterator<QByteArray, CacheItem> i(p->cacheCollection);
    while (i.hasNext()) {
        i.next();
        if (i.key().startsWith(key))
            list << i.key();
    }
    emit threadResponse->responseList(list);
}

void CacheRepository::cacheListKeys()
{
    auto threadResponse = dynamic_cast<CacheRequest *>(QObject::sender());
    if (threadResponse == nullptr)
        return;
    auto list = QVector<QByteArray>::fromList(p->cacheCollection.keys());
    emit threadResponse->responseList(list);
}

void CacheRepository::cacheClear()
{

    p->cacheCollection.clear();
}

} // namespace QCrossCache
