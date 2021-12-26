#ifndef YourCustomClientImpl_H
#define YourCustomClientImpl_H

#include <QCrossCache>

//!
//! \brief The YourCustomClientImpl class
//!
class YourCustomClientImpl : public QCrossCache::ActuatorInterface
{
    Q_OBJECT
public:

    //!
    //! \brief YourCustomClientImpl
    //! \param parent
    //!
    Q_INVOKABLE explicit YourCustomClientImpl(QObject *parent = nullptr) : ActuatorInterface(parent)
    {
    }

    //!
    //! \brief YourCustomClientImpl
    //! \param server
    //! \param dataGroup
    //!
    explicit YourCustomClientImpl(QCrossCache::Server *server, const QByteArray &dataGroup) : ActuatorInterface(server, dataGroup)
    {
    }

    //!
    //!
    ~YourCustomClientImpl()
    {
    }

    //!
    //! \brief connect
    //! \return
    //!
    virtual bool connect()
    {
        return false;
    }

    //!
    //! \brief disconnect
    //! \return
    //!
    virtual bool disconnect()
    {
        return false;
    }

    //!
    //! \brief isConnected
    //! \return
    //!
    virtual bool isConnected()
    {
        return false;
    }

    //!
    //! \brief clear
    //! \return
    //!
    virtual bool clear()
    {
        return false;
    }

    //!
    //! \brief exists
    //! \param key
    //! \return
    //!
    virtual bool exists(const QByteArray&key)
    {
        Q_UNUSED(key)
        return false;
    }

    //!
    //! \brief put
    //! \param key
    //! \param data
    //! \return
    //!
    virtual bool put(const QByteArray&key, const QByteArray &data, const quint64 expiration=0)
    {
        Q_UNUSED(key)
        Q_UNUSED(data)
        Q_UNUSED(expiration)
        return false;
    }

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    virtual QByteArray get(const QByteArray&key)
    {
        Q_UNUSED(key)
        return {};
    }

    //!
    //! \brief get
    //! \param key
    //! \param data
    //! \return
    //!
    virtual QByteArray take(const QByteArray&key)
    {
        Q_UNUSED(key)
        return {};
    }

    //!
    //! \brief remove
    //! \param key
    //! \return
    //!
    virtual bool remove(const QByteArray&key)
    {
        Q_UNUSED(key)
        return false;
    }

    //!
    //! \brief list
    //! \param key
    //! \return
    //!
    virtual QVector<QByteArray> list(const QByteArray&key)
    {
        Q_UNUSED(key)
        return {};
    }

    //!
    //! \brief listKeys
    //! \param key
    //! \return
    //!
    virtual QVector<QByteArray> listKeys()
    {
        return {};
    }
};

//register interface client
Q_CROSSCACHE_REGISTER_INTERFACE(redis,YourCustomClientImpl)

#endif
