TARGET = QCrossCache
TEMPLATE = lib

HEADERS += \
	$$PWD/include/QCrossCache
	
#libmamcached
LIBS += -lmemcached

include($$PWD/src/qcrosscache.pri)
