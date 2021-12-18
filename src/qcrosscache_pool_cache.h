#pragma once

#include <QObject>
#include <QThread>
#include <QVariant>
#include <QMutex>
#include "./qcrosscache_global.h"
#include "./qcrosscache_types.h"

namespace QCrossCache {

//!
//! \brief The PoolCache class
//!
class Q_CROSSCACHE_EXPORT PoolCache : public QThread
{
    Q_OBJECT
public:
    //!
    //! \brief PoolCache
    //! \param parent
    //!
    explicit PoolCache(QObject *parent = nullptr);

    //!
    //!
    ~PoolCache();

    //!
    //! \brief instance
    //! \return
    //!
    static PoolCache&instance();

    //!
    //! \brief run
    //!
    void run() override;
public slots:
    void cacheGet(const QByteArray&dataGroup, const QByteArray&key, PoolCacheResponseData response);
    void cachePut(const QByteArray&dataGroup, const QByteArray&key, const QByteArray&data);
    void cacheRemove(const QByteArray&dataGroup, const QByteArray&key);
    void cacheList(const QByteArray&dataGroup, const QByteArray &key, const PoolCacheResponseKeys response);
    void cacheListKeys(const QByteArray&dataGroup, const PoolCacheResponseKeys keys);
private:

    //!
    //! \brief clear
    //!
    PoolCache &clear();
private:
    void*p=nullptr;
signals:

};

}
