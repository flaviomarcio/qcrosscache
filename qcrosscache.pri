QT += core
QT += network

CONFIG += silent
CONFIG += c++17

#libmamcached
LIBS += -lmemcached

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/src

HEADERS += \
        $$PWD/include/QCrossCache

include($$PWD/src/qcrosscache.pri)
