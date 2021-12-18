#include "./qcrosscache_types.h"


namespace QCrossCache {

ActuatorInterfaceItem::ActuatorInterfaceItem()
{
}

ActuatorInterfaceItem::ActuatorInterfaceItem(const QByteArray &serviceName, const QMetaObject &serviceMetaObject)
{
    this->name=serviceName.toLower();
    this->metaObject=serviceMetaObject;
}

}
