#pragma once

#include <QObject>
#include <QThread>
#include <QVariant>
#include <QMutex>
#include "./qcrosscache_global.h"
#include "./qcrosscache_types.h"

namespace QCrossCache {

//!
//! \brief The Pool class
//!
class Q_CROSSCACHE_EXPORT Pool : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief Pool
    //! \param parent
    //!
    explicit Pool(QObject *parent = nullptr);

    //!
    //!
    ~Pool();

    //!
    //! \brief start
    //! \return
    //!
    virtual Pool&start();

    //!
    //! \brief stop
    //! \return
    //!
    virtual Pool&stop();

    //!
    //! \brief isStarted
    //! \return
    //!
    virtual bool isStarted();

    //!
    //! \brief instance
    //! \return
    //!
    static Pool&instance();

public slots:
    //!
    //! \brief cacheClearAll
    //! \return
    //!
    Pool &cacheClearAll();

    //!
    //! \brief cacheClear
    //! \param dataGroup
    //! \return
    //!
    Pool &cacheClear(const QByteArray &dataGroup);

    //!
    //! \brief cachePut
    //! \param dataGroup
    //! \param key
    //! \param data
    //! \param expiration
    //! \return
    //!
    Pool &cachePut(const QByteArray&dataGroup, const QByteArray&key, const QByteArray&data, const quint64 expiration);

    //!
    //! \brief cacheRemove
    //! \param dataGroup
    //! \param key
    //! \return
    //!
    Pool &cacheRemove(const QByteArray&dataGroup, const QByteArray&key);

    //!
    //! \brief cacheGet
    //! \param dataGroup
    //! \param key
    //! \return
    //!
    QByteArray cacheGet(const QByteArray&dataGroup, const QByteArray&key);


    //!
    //! \brief cacheTake
    //! \param dataGroup
    //! \param key
    //! \return
    //!
    QByteArray cacheTake(const QByteArray&dataGroup, const QByteArray&key);

    //!
    //! \brief cacheList
    //! \param dataGroup
    //! \param key
    //! \return
    //!
    QVector<QByteArray> cacheList(const QByteArray&dataGroup, const QByteArray &key);

    //!
    //! \brief cacheListKeys
    //! \param dataGroup
    //! \return
    //!
    QVector<QByteArray> cacheListKeys(const QByteArray&dataGroup);
private:
    void*p=nullptr;
signals:

};

}
