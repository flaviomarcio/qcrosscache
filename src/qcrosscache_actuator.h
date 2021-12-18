#pragma once

#include <QObject>
#include "./qcrosscache_actuator_interface.h"

namespace QCrossCache {

class Session;

//!
//! \brief The Actuator class
//!
class Q_CROSSCACHE_EXPORT Actuator : public QCrossCache::ActuatorInterface
{
    Q_OBJECT
public:

    //!
    //! \brief Actuator
    //! \param parent
    //!
    Q_INVOKABLE explicit Actuator(QObject*parent = nullptr);

    //!
    //! \brief Actuator
    //! \param parent
    //! \param session
    //!
    Q_INVOKABLE explicit Actuator(QObject *parent, Session *session, const QByteArray &dataGroup);

    //!
    //!
    ~Actuator();

    //!
    //! \brief put
    //! \param key
    //! \param data
    //! \return
    //!
    Q_INVOKABLE virtual bool put(const QByteArray&key, QByteArray &data);

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
private:
    void*p=nullptr;
signals:
};

}
