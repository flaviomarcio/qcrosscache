QT += core
QT += network

CONFIG += silent
CONFIG += c++17

#exists(/usr/lib/x86_64-linux-gnu/libmemcached.so){
##libmamcached
#message("libmemcached included")
#LIBS += -lmemcached
#Q_CROSSCACHE_MEMCACHED=true
#QMAKE_CXXFLAGS += -DQ_CROSSCACHE_MEMCACHED=\\\"$$Q_CROSSCACHE_MEMCACHED\\\"
#}


#INCLUDEPATH += $$PWD/include
#INCLUDEPATH += $$PWD/src

HEADERS += \
        $$PWD/include/QCrossCache

include($$PWD/src/qcrosscache.pri)
