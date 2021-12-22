#pragma once

#include <QObject>
#include <QThread>
#include <QVariant>
#include <QMutex>
#include "../qcrosscache_pool.h"
#include "../qcrosscache_types.h"

namespace QCrossCache {

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
public slots:
    void cacheGet(const QByteArray&key);
    void cacheTake(const QByteArray&key);
    void cachePut(const QByteArray&key, const QByteArray&data, const quint64 expiration);
    void cacheRemove(const QByteArray&key);
    void cacheList(const QByteArray &key);
    void cacheListKeys();
    void cacheClear();
private:
    void*p=nullptr;
signals:

};

}
