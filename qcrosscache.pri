QT += core
QT += network

CONFIG += c++17

QTREFORCE_QCROSSCACHE=true
DEFINES+=QTREFORCE_QCROSSCACHE

#!CONFIG(Q_CROSSCACHE_MEMCACHED):message("QCrossCache: libmemcached removed")

CONFIG(Q_CROSSCACHE_MEMCACHED){
    #libmamcached
    !exists(/usr/lib/x86_64-linux-gnu/libmemcached.so){
        message("QCrossCache: libmemcached dont exists")
        message("QCrossCache: libmemcached removedy")
        CONFIG-=Q_CROSSCACHE_MEMCACHED
        DEFINES-=Q_CROSSCACHE_MEMCACHED
    }
    else{
        #message("QCrossCache: libmemcached included")
        LIBS += -lmemcached
        Q_CROSSCACHE_MEMCACHED=true
        DEFINES+=Q_CROSSCACHE_MEMCACHED
    }
}

HEADERS += \
        $$PWD/include/QCrossCache

include($$PWD/src/qcrosscache.pri)
