#pragma once

#include <QObject>
#include <QMutex>
#include <QHash>
#include <QList>
#include <QVector>
#include <QByteArray>
#include <QDateTime>
#include "./qcrosscache_global.h"


namespace QCrossCache {

class Server;
class ActuatorInterface;

enum Service{
    Local=0, Memcached=1
};

//!
//! \brief The ActuatorInterfaceItem class
//!
class ActuatorInterfaceItem{
public:
    QByteArray name;
    QMetaObject metaObject;

    //!
    //! \brief ActuatorInterfaceItem
    //!
    explicit ActuatorInterfaceItem();

    //!
    //! \brief ActuatorInterfaceItem
    //! \param serviceName
    //! \param serviceMetaObject
    //!
    explicit ActuatorInterfaceItem(const QByteArray&serviceName, const QMetaObject&serviceMetaObject);

    //!
    //! \brief newObject
    //! \param parent
    //! \return
    //!
    template <class T=QObject>
    T*newObject(Server*server=nullptr, const QByteArray&dataGroup=QByteArray())
    {
        auto __object=this->metaObject.newInstance(Q_ARG(Server*, server), Q_ARG(QByteArray, dataGroup));
        if(__object==nullptr)
            return nullptr;
        auto __return=dynamic_cast<T*>(__object);
        if(__return==nullptr){
            delete __object;
            return nullptr;
        }
        return __return;
    }
};


//!
//! \brief ActuatorInterfaceCollection
//!
typedef QHash<QByteArray, ActuatorInterfaceItem*> ActuatorInterfaceCollection;

}
