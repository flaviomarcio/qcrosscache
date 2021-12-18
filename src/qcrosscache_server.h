#pragma once

#include <QObject>
#include <QVariant>
#include "./qcrosscache_global.h"

namespace QCrossCache {

//!
//! \brief The Server class
//!
class Q_CROSSCACHE_EXPORT Server : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QByteArray hostName READ hostName WRITE setHostName NOTIFY hostNameChanged)
    Q_PROPERTY(QByteArray passWord READ passWord WRITE setPassWord NOTIFY passWordChanged)
    Q_PROPERTY(QByteArray portNumber READ portNumber WRITE setPortNumber NOTIFY portNumberChanged)
    Q_PROPERTY(QByteArray dataGroup READ dataGroup WRITE setDataGroup NOTIFY dataGroupChanged)

    //!
    //! \brief Server
    //! \param parent
    //!
    explicit Server(QObject *parent = nullptr);

    //!
    //!
    ~Server();

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

    //!
    //! \brief hostName
    //! \return
    //!
    const virtual QByteArray &hostName() const;

    //!
    //! \brief setHostName
    //! \param value
    //!
    virtual void setHostName(const QByteArray &value);

    //!
    //! \brief passWord
    //! \return
    //!
    const virtual QByteArray &passWord() const;

    //!
    //! \brief setPassWord
    //! \param value
    //!
    virtual void setPassWord(const QByteArray &value);

    //!
    //! \brief portNumber
    //! \return
    //!
    const virtual QByteArray &portNumber() const;

    //!
    //! \brief setPortNumber
    //! \param value
    //!
    virtual void setPortNumber(const QByteArray &value);

    //!
    //! \brief dataGroup
    //! \return
    //!
    const virtual QByteArray &dataGroup() const;

    //!
    //! \brief setDataGroup
    //! \param value
    //!
    virtual void setDataGroup(const QByteArray &value);
private:
    void*p=nullptr;
signals:
    void hostNameChanged();
    void passWordChanged();
    void portNumberChanged();
    void dataGroupChanged();
};


}
