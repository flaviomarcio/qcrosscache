#pragma once

#include <QObject>
#include <QVariant>
#include "./qcrosscache_global.h"

#define Q_CROSSCACHE_REGISTER_INTERFACE(object)\
static auto const interface__##object=QCrossCache::ActuatorInterface::registerInterface(object::staticMetaObject);

namespace QCrossCache {

class Session;
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
    Q_INVOKABLE explicit ActuatorInterface(QObject *parent, Session *session, const QByteArray &dataGroup);

    //!
    //!
    ~ActuatorInterface();

    //!
    //! \brief interfaceRegistered
    //! \return
    //!
    static const QVector<const QMetaObject *> &interfaceRegistered();

    //!
    //! \brief interfaceRegister
    //! \param metaObject
    //!
    static const QMetaObject &registerInterface(const QMetaObject &metaObject);

    //!
    //! \brief put
    //! \param key
    //! \param data
    //! \return
    //!
    Q_INVOKABLE virtual bool put(const QByteArray&key, QByteArray&data);

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
    Q_INVOKABLE virtual bool take(const QByteArray&key, QByteArray&data);

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
protected:

    //!
    //! \brief createServer
    //! \param hostName
    //! \param passWord
    //! \param portNumber
    //! \param dataGroup
    //! \return
    //!
    static Server*createServer(const QByteArray&hostName, const QByteArray&passWord, const QByteArray&portNumber, const QByteArray&dataGroup=QByteArray());

    //!
    //! \brief createServer
    //! \param settings
    //! \return
    //!
    static Server*createServer(const QVariant&settings);
private:
    void*p=nullptr;
signals:
};

}
