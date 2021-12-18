#pragma once

#include <QObject>
#include <QVariant>
#include "./qcrosscache_global.h"

namespace QCrossCache {

class ActuatorInterfaceItem;
class Server;


//!
//! \brief The ActuatorInterface class
//!
class Q_CROSSCACHE_EXPORT ActuatorInterface : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief ActuatorInterface
    //! \param parent
    //!
    Q_INVOKABLE explicit ActuatorInterface(QObject *parent = nullptr);

    //!
    //! \brief ActuatorInterface
    //! \param groupData
    //! \param parent
    //!
    Q_INVOKABLE explicit ActuatorInterface(Server*server, const QByteArray &dataGroup);

    //!
    //!
    ~ActuatorInterface();

    //!
    //! \brief dataGroup
    //! \return
    //!
    virtual QByteArray &dataGroup()const;

    //!
    //! \brief connect
    //! \return
    //!
    virtual bool connect();

    //!
    //! \brief disconnect
    //! \return
    //!
    virtual bool disconnect();

    //!
    //! \brief isConnected
    //! \return
    //!
    virtual bool isConnected();

    //!
    //! \brief exists
    //! \param key
    //! \return
    //!
    Q_INVOKABLE virtual bool exists(const QByteArray&key);

    //!
    //! \brief put
    //! \param key
    //! \param data
    //! \return
    //!
    Q_INVOKABLE virtual bool put(const QByteArray&key, const QByteArray&data);

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    Q_INVOKABLE virtual bool get(const QByteArray&key, QByteArray&data);

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    Q_INVOKABLE virtual bool take(const QByteArray&key, QByteArray &data);

    //!
    //! \brief remove
    //! \param key
    //! \return
    //!
    Q_INVOKABLE virtual bool remove(const QByteArray&key);

    //!
    //! \brief list
    //! \param key
    //! \param listKeys
    //! \return
    //!
    Q_INVOKABLE virtual bool list(const QByteArray&key, QVector<QByteArray>&listKeys);

    //!
    //! \brief listKeys
    //! \param key
    //! \param listKeys
    //! \return
    //!
    Q_INVOKABLE virtual bool listKeys(const QByteArray&key, QVector<QByteArray>&listKeys);

private:
    void*p=nullptr;
signals:
};

}
