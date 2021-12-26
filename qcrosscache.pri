QT += core
QT += network
QT += websockets

CONFIG += silent
CONFIG += c++17
CONFIG += silent

#libmamcached
LIBS += -lmemcached

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/src

HEADERS += \
        $$PWD/include/QCrossCache

include($$PWD/src/qcrosscache.pri)
