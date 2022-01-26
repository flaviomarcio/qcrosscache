CONFIG(Q_CROSSCACHE_MEMCACHED){
HEADERS += \
    $$PWD/private/p_qcrosscache_actuator_memcached.h

SOURCES += \
    $$PWD/private/p_qcrosscache_actuator_memcached.cpp
}

CONFIG(Q_CROSSCACHE_REDIS){
HEADERS += \
    $$PWD/private/p_qcrosscache_actuator_redis.h

SOURCES += \
    $$PWD/private/p_qcrosscache_actuator_redis.cpp
}

CONFIG(Q_CROSSCACHE_MONGODB){
HEADERS += \
    $$PWD/private/p_qcrosscache_actuator_mongodb.h

SOURCES += \
    $$PWD/private/p_qcrosscache_actuator_mongodb.cpp
}

HEADERS += \
    $$PWD/private/p_qcrosscache_actuator_local.h \
    $$PWD/private/p_qcrosscache_cache_repository.h \
    $$PWD/private/p_qcrosscache_cache_request.h \
    $$PWD/private/p_qcrosscache_pool.h \
    $$PWD/qcrosscache.h \
    $$PWD/qcrosscache_actuator_interface.h \
    $$PWD/qcrosscache_actuator_manager.h \
    $$PWD/qcrosscache_client.h \
    $$PWD/qcrosscache_global.h \
    $$PWD/qcrosscache_pool.h \
    $$PWD/qcrosscache_server.h \
    $$PWD/qcrosscache_types.h


SOURCES += \
    $$PWD/private/p_qcrosscache_actuator_local.cpp \
    $$PWD/private/p_qcrosscache_cache_repository.cpp \
    $$PWD/private/p_qcrosscache_cache_request.cpp \
    $$PWD/private/p_qcrosscache_pool.cpp \
    $$PWD/qcrosscache_actuator_interface.cpp \
    $$PWD/qcrosscache_actuator_manager.cpp \
    $$PWD/qcrosscache_client.cpp \
    $$PWD/qcrosscache_pool.cpp \
    $$PWD/qcrosscache_server.cpp \
    $$PWD/qcrosscache_types.cpp
