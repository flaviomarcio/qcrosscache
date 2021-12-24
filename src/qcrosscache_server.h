#pragma once

#include <QObject>
#include <QVariant>
#include <QUuid>
#include "./qcrosscache_global.h"
#include "./qcrosscache_types.h"
#include "./qcrosscache_client.h"

namespace QCrossCache {
class ActuatorInterface;

//!
//! \brief The Server class
//!
class Q_CROSSCACHE_EXPORT Server : public QObject
{
    Q_OBJECT
    friend class ActuatorManager;
public:

    enum Service{
        Local=0, Memcached=1
    };

    Q_ENUM(Service)

    Q_PROPERTY(QUuid uuid READ uuid)
    Q_PROPERTY(QByteArray service READ service WRITE setService NOTIFY hostNameChanged)
    Q_PROPERTY(QByteArray hostName READ hostName WRITE setHostName NOTIFY hostNameChanged)
    Q_PROPERTY(QByteArray passWord READ passWord WRITE setPassWord NOTIFY passWordChanged)
    Q_PROPERTY(QByteArray portNumber READ portNumber WRITE setPortNumber NOTIFY portNumberChanged)

    //!
    //! \brief Server
    //! \param parent
    //!
    explicit Server(QObject *parent = nullptr);

    //!
    //!
    ~Server();
private:
    //!
    //! \brief createServer
    //! \param hostName
    //! \param passWord
    //! \param portNumber
    //! \param dataGroup
    //! \return
    //!
    static Server*createServer(QObject *parent, ActuatorInterfaceItem*ActuatorInterface, const QByteArray&hostName, const QByteArray&passWord, const QByteArray&portNumber);
public:
    //!
    //! \brief createClient
    //! \param dataGroup
    //! \return
    //!
    virtual Client*createClient(const QByteArray &dataGroup=QByteArray());

    //!
    //! \brief uuid
    //! \return
    //!
    const QUuid &uuid();

    //!
    //! \brief service
    //! \return
    //!
    const virtual QByteArray &service() const;

    //!
    //! \brief setService
    //! \param value
    //!
    virtual Server&setService(const QByteArray &value);

    //!
    //! \brief hostName
    //! \return
    //!
    const virtual QByteArray &hostName() const;

    //!
    //! \brief setHostName
    //! \param value
    //!
    virtual Server&setHostName(const QByteArray &value);

    //!
    //! \brief passWord
    //! \return
    //!
    const virtual QByteArray &passWord() const;

    //!
    //! \brief setPassWord
    //! \param value
    //!
    virtual Server&setPassWord(const QByteArray &value);

    //!
    //! \brief portNumber
    //! \return
    //!
    const virtual QByteArray &portNumber() const;

    //!
    //! \brief setPortNumber
    //! \param value
    //!
    virtual Server&setPortNumber(const QByteArray &value);

    //!
    //! \brief setPortNumber
    //! \param value
    //! \return
    //!
    virtual Server&setPortNumber(const qlonglong &value);



private:
    void*p=nullptr;
signals:
    void serviceChanged();
    void hostNameChanged();
    void passWordChanged();
    void portNumberChanged();
    void dataGroupChanged();
};


}
