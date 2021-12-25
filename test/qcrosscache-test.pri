include($$PWD/../qcrosscache.pri)

INCLUDEPATH+=$$PWD

CONFIG += console
CONFIG -= debug_and_release
CONFIG += testcase
LIBS += -L/usr/local/lib -lgmock
LIBS += -L/usr/local/lib -lgtest

Q_QCROSSCACHE_TEST=true
QMAKE_CXXFLAGS += -DQ_QCROSSCACHE_TEST=\\\"$$Q_QCROSSCACHE_TEST\\\"

HEADERS += \
    $$PWD/qcrosscache_test.h \
    $$PWD/qcrosscache_test_unit.h \
    $$PWD/qcrosscache_test_functional.h

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/qcrosscache_functional_interface_local.cpp \
    $$PWD/qcrosscache_functional_interface_mencached.cpp \
    $$PWD/qcrosscache_functional_interface_mongodb.cpp \
    $$PWD/qcrosscache_functional_interface_redis.cpp \
