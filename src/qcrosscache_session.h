#pragma once

#include <QObject>
#include "./qcrosscache_global.h"

namespace QCrossCache {

class Server;

//!
//! \brief The Session class
//!
class Q_CROSSCACHE_EXPORT Session : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QByteArray dataGroup READ dataGroup WRITE setDataGroup NOTIFY dataGroupChanged)

    //!
    //! \brief Session
    //! \param parent
    //!
    explicit Session(QObject *parent = nullptr);

    //!
    //!
    ~Session();

    //!
    //! \brief interfaceMetaObject
    //! \return
    //!
    virtual QMetaObject*interfaceMetaObject();

    //!
    //! \brief server
    //! \return
    //!
    virtual Server&server();

    //!
    //! \brief dataGroup
    //! \return
    //!
    const virtual QByteArray &dataGroup() const;
    virtual void setDataGroup(const QByteArray &value);

private:
    void*p=nullptr;
signals:
    void dataGroupChanged();
};

}
