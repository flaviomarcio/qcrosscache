QT += testlib

CONFIG += testcase
CONFIG += console
CONFIG += silent
CONFIG -= debug_and_release
QT -= gui

TEMPLATE = app
TARGET = QCrossCacheTest

INCLUDEPATH+=$$PWD/../src

QCROSSCACHE_TEST_MODE=true
QMAKE_CXXFLAGS += -DQCROSSCACHE_TEST_MODE=\\\"$$QCROSSCACHE_TEST_MODE\\\"

LIBS += -lgmock
LIBS += -lgtest


include($$PWD/test/qcrosscache-test.pri)

