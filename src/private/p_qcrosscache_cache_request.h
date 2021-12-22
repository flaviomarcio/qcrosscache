#pragma once

#include <QObject>
#include <QThread>
#include <QVariant>
#include <QMutex>
#include "../qcrosscache_types.h"

namespace QCrossCache {

class CacheRepository;
class CacheRequest : public QThread
{
    Q_OBJECT
public:
    //!
    //! \brief CacheRepository
    //! \param parent
    //!
    explicit CacheRequest();

    //!
    //!
    ~CacheRequest();

    //!
    //! \brief run
    //!
    void run() override;

    //!
    //! \brief start
    //! \param repository
    //!
    CacheRequest&start(CacheRepository*repository);

public:
    //!
    //! \brief getData
    //! \return
    //!
    const QByteArray &getData()const;

    //!
    //! \brief getList
    //! \return
    //!
    const QVector<QByteArray> &getList()const;
private:
    QByteArray data;
    QVector<QByteArray> list;
    CacheRepository*repository=nullptr;
signals:
    void requestFinished(CacheRequest*request);

    void cacheClear();
    void cacheGet(const QByteArray&key);
    void cacheList(const QByteArray &key);
    void cacheListKeys();
    void cachePut(const QByteArray&key, const QByteArray&data, const quint64 expiration);
    void cacheRemove(const QByteArray&key);
    void cacheTake(const QByteArray&key);

    void responseData(const QByteArray&data);
    void responseList(const QVector<QByteArray>&list);


    void repositoryCacheClear();
    void repositoryCacheGet(const QByteArray&key);
    void repositoryCacheList(const QByteArray &key);
    void repositoryCacheListKeys();
    void repositoryCachePut(const QByteArray&key, const QByteArray&data, const quint64 expiration);
    void repositoryCacheRemove(const QByteArray&key);
    void repositoryCacheTake(const QByteArray&key);

private slots:

    void onCacheClear();
    void onCacheGet(const QByteArray&key);
    void onCacheList(const QByteArray &key);
    void onCacheListKeys();
    void onCachePut(const QByteArray&key, const QByteArray&data, const quint64 expiration);
    void onCacheRemove(const QByteArray&key);
    void onCacheTake(const QByteArray&key);
    void onResponseData(const QByteArray&data);
    void onResponseList(const QVector<QByteArray>&list);
};
}
