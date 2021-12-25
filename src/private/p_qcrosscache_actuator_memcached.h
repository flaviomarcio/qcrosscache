#pragma once

#include "../qcrosscache_actuator_interface.h"
#include "../qcrosscache_actuator_manager.h"
#include "../qcrosscache_server.h"
#include <QTcpSocket>
#include <QThread>
#include <QTimer>

namespace QCrossCache {



static const auto MEMCACHED_END_BLOCK=QByteArrayLiteral("END\r\n");

//!
//! \brief The ActuatorMemcachedRequest class
//!
class ActuatorMemcachedRequest : public QThread
{
    Q_OBJECT
private:
    QByteArray hostName;
    int portNumber;
    QByteArray reqBody;
    QVector<QByteArray> resBody;
    QTcpSocket*m_socket=nullptr;
public:
    //!
    //! \brief ActuatorMemcachedRequest
    //! \param actuator
    //! \param command
    //!
    explicit ActuatorMemcachedRequest(const QByteArray&hostName, const int portNumber, const QByteArray&reqBody):QThread(nullptr)
    {
        this->moveToThread(this);
        this->hostName=hostName;
        this->portNumber=portNumber;
        this->reqBody=reqBody;
    }

    //!
    //!
    ~ActuatorMemcachedRequest(){
    }

    QVector<QByteArray> responseBody()const
    {
        return this->resBody;
    }


    ActuatorMemcachedRequest&start()
    {
        QThread::start();
        while(this->eventDispatcher()==nullptr)
            QThread::msleep(1);
        return*this;
    }



    //!
    //! \brief run
    //!
    void run() override
    {
        if(m_socket!=nullptr)
            delete m_socket;
        m_socket = new QTcpSocket();
        this->resBody.clear();
        QTimer::singleShot(10, this, &ActuatorMemcachedRequest::call);
        this->exec();
        this->m_socket->close();
        m_socket->deleteLater();
        this->m_socket=nullptr;
    }

private slots:

    //!
    //! \brief call
    //!
    void call()
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
        QObject::connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), this, &ActuatorMemcachedRequest::onReplyError);
#else
        QObject::connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error), this, &ActuatorMemcachedRequest::onReplyError);
#endif
        QObject::connect(m_socket, &QTcpSocket::connected, this, &ActuatorMemcachedRequest::onConnected);
        m_socket->connectToHost(this->hostName, this->portNumber);
    }

    void onConnected()
    {
        if(!m_socket->waitForConnected()){
            this->quit();
            return;
        }
        m_socket->write(this->reqBody);
        m_socket->write("\n");
        m_socket->flush();
        while(m_socket->waitForReadyRead()){
            QByteArray line;
            while(m_socket->canReadLine()){
                line=m_socket->readLine();
                if(line==MEMCACHED_END_BLOCK)
                    break;
                this->resBody<<line;
            }
            if(line==MEMCACHED_END_BLOCK)
                break;
        }
        m_socket->disconnect();
        m_socket->deleteLater();
        this->quit();
    };

    void onReplyError(QAbstractSocket::SocketError e)
    {
        Q_UNUSED(e)
//        if(e!=QAbstractSocket::SocketError::RemoteHostClosedError)
//            this->onFinish();
        this->quit();
    };
};

//!
//! \brief The ActuatorMemcached class
//!
class ActuatorMemcached : public ActuatorInterface
{
    Q_OBJECT
public:

    //!
    //! \brief ActuatorMemcached
    //! \param parent
    //!
    Q_INVOKABLE explicit ActuatorMemcached(QObject *parent = nullptr);

    //!
    //! \brief ActuatorMemcached
    //! \param server
    //! \param dataGroup
    //!
    explicit ActuatorMemcached(Server *server, const QByteArray &dataGroup);

    //!
    //!
    ~ActuatorMemcached();

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
    //! \brief clear
    //! \return
    //!
    virtual bool clear();

    //!
    //! \brief exists
    //! \param key
    //! \return
    //!
    virtual bool exists(const QByteArray&key);

    //!
    //! \brief put
    //! \param key
    //! \param data
    //! \return
    //!
    virtual bool put(const QByteArray&key, const QByteArray &data, const quint64 expiration);

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    virtual QByteArray get(const QByteArray&key);

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    virtual QByteArray take(const QByteArray&key);

    //!
    //! \brief remove
    //! \param key
    //! \return
    //!
    virtual bool remove(const QByteArray&key);

    //!
    //! \brief list
    //! \param key
    //! \return
    //!
    virtual QVector<QByteArray> list(const QByteArray&key);

    //!
    //! \brief listKeys
    //! \param key
    //! \return
    //!
    virtual QVector<QByteArray> listKeys();

private:
    void*p=nullptr;
signals:
};

Q_CROSSCACHE_REGISTER_INTERFACE(memcached,ActuatorMemcached)

} // namespace QCrossCache
