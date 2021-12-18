QT += core
QT += network
QT += websockets

CONFIG += silent
CONFIG += c++17
CONFIG += silent
CONFIG -=qtquickcompiler

INCLUDEPATH+=$$PWD

HEADERS += \
    $$PWD/private/p_qcrosscache_actuator_local.h \
    $$PWD/private/p_qcrosscache_actuator_memcached.h \
    $$PWD/qcrosscache_actuator_interface.h \
    $$PWD/qcrosscache.h \
    $$PWD/qcrosscache_actuator.h \
    $$PWD/qcrosscache_global.h \
    $$PWD/qcrosscache_server.h \
    $$PWD/qcrosscache_session.h

SOURCES += \
    $$PWD/private/p_qcrosscache_actuator_memcached.cpp \
    $$PWD/private/p_qcrosscache_actuator_local.cpp \
    $$PWD/qcrosscache_actuator_interface.cpp \
    $$PWD/qcrosscache_actuator.cpp \
    $$PWD/qcrosscache_server.cpp \
    $$PWD/qcrosscache_session.cpp

