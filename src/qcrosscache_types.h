#pragma once

#include <QObject>

//!
//! \brief PoolCacheResponse
//!
typedef std::function<void*(const QByteArray&data)> PoolCacheResponseData;

//!
//! \brief PoolCacheResponseKeys
//!
typedef std::function<void*(QList<QByteArray>)> PoolCacheResponseKeys;
