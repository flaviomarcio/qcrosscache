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
    void requestFineshed(CacheRequest*request);
    void responseData(const QByteArray&data);
    void responseList(const QVector<QByteArray>&list);
    void cacheGet(const QByteArray&key);
    void cacheTake(const QByteArray&key);
    void cacheList(const QByteArray &key);
    void cacheListKeys();
private slots:

    void onResponseData(const QByteArray&data);

    void onResponseList(const QVector<QByteArray>&list);

    void onCacheGet(const QByteArray&key);

    void onCacheTake(const QByteArray&key);

    void onCacheList(const QByteArray &key);

    void onCacheListKeys();
};
}
