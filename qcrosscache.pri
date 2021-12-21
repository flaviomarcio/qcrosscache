QT += core
QT += network
QT += websockets

CONFIG += silent
CONFIG += c++17
CONFIG += silent
CONFIG -=qtquickcompiler

#libmamcached
LIBS += -lmemcached
INCLUDEPATH += $$PWD/include

HEADERS += \
        $$PWD/include/QCrossCache

include($$PWD/src/qcrosscache.pri)
