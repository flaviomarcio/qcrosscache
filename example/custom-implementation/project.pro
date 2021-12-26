TARGET = QCrossCache_CustomClient
TEMPLATE = lib

include($$PWD/../../qcrosscache.pri)

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/your_customs_impl.h
