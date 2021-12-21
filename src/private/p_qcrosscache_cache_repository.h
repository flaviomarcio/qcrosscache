#pragma once

#include <QObject>
#include <QThread>
#include <QVariant>
#include <QMutex>
#include "../qcrosscache_pool.h"
#include "../qcrosscache_types.h"

namespace QCrossCache {

class CacheRequest;

//!
//! \brief The CacheRepository class
//!
class CacheRepository : public QThread
{
    Q_OBJECT
public:
    //!
    //! \brief CacheRepository
    //! \param parent
    //!
    explicit CacheRepository(QObject *parent = nullptr);

    //!
    //!
    ~CacheRepository();

    //!
    //! \brief run
    //!
    void run() override;
signals:
    void cacheGet(const QByteArray&key, CacheRequest*responseThread);
    void cacheTake(const QByteArray&key, CacheRequest*responseThread);
    void cachePut(const QByteArray&key, const QByteArray&data, const quint64 experiation);
    void cacheRemove(const QByteArray&key);
    void cacheList(const QByteArray &key, CacheRequest*responseThread);
    void cacheListKeys(CacheRequest*responseThread);
    void cacheClear();
private:
    void*p=nullptr;
signals:

};

}
