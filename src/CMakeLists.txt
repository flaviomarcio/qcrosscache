set(crosscache_SRCS
    # cmake-format: sortable
    private/p_qcrosscache_actuator_local.cpp
    private/p_qcrosscache_actuator_memcached.cpp
    private/p_qcrosscache_actuator_mongodb.cpp
    private/p_qcrosscache_actuator_redis.cpp
    private/p_qcrosscache_cache_repository.cpp
    private/p_qcrosscache_cache_request.cpp
    private/p_qcrosscache_pool.cpp
    qcrosscache_types.cpp
    qcrosscache_server.cpp
    qcrosscache_pool.cpp
    qcrosscache_client.cpp
    qcrosscache_actuator_manager.cpp
    qcrosscache_actuator_interface.cpp
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    add_library(crosscache STATIC ${crosscache_SRCS})
else()
    add_library(crosscache SHARED ${crosscache_SRCS})
endif()

target_link_libraries(
    crosscache # cmake-format: sortable
)

install(TARGETS crosscache
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/qt/plugins/crosscache
)
