cmake_minimum_required(VERSION 3.14)
project(
    QCrossCache
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -Wextra -Werror -Wno-unused-function")

if(NOT DEFINED QT_DEFAULT_MAJOR_VERSION)
    set(QT_DEFAULT_MAJOR_VERSION 5)
endif()

find_package(Qt5Core)
find_package(Qt5Network)

if(MSVC)
    add_compile_options(/W3 /WX /Zc:lambda)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

add_subdirectory(src)

foreach(plugin ${Qt5Core_PLUGINS})
  get_target_property(_loc ${plugin} LOCATION)
  message("Plugin ${plugin} is at location ${_loc}")
endforeach()

foreach(plugin ${Qt5Network_PLUGINS})
  get_target_property(_loc ${plugin} LOCATION)
  message("Plugin ${plugin} is at location ${_loc}")
endforeach()

########## Private ##########
if(NOT DEFINED LIBMEMCACHED_PUBLIC_VAR_NS)
    set(LIBMEMCACHED_PUBLIC_VAR_NS "LIBMEMCACHED")
endif(NOT DEFINED LIBMEMCACHED_PUBLIC_VAR_NS)
if(NOT DEFINED LIBMEMCACHED_PRIVATE_VAR_NS)
    set(LIBMEMCACHED_PRIVATE_VAR_NS "_${LIBMEMCACHED_PUBLIC_VAR_NS}")
endif(NOT DEFINED LIBMEMCACHED_PRIVATE_VAR_NS)

function(libmemcached_debug _VARNAME)
    if(${LIBMEMCACHED_PUBLIC_VAR_NS}_DEBUG)
        if(DEFINED ${LIBMEMCACHED_PUBLIC_VAR_NS}_${_VARNAME})
            message("${LIBMEMCACHED_PUBLIC_VAR_NS}_${_VARNAME} = ${${LIBMEMCACHED_PUBLIC_VAR_NS}_${_VARNAME}}")
        else(DEFINED ${LIBMEMCACHED_PUBLIC_VAR_NS}_${_VARNAME})
            message("${LIBMEMCACHED_PUBLIC_VAR_NS}_${_VARNAME} = <UNDEFINED>")
        endif(DEFINED ${LIBMEMCACHED_PUBLIC_VAR_NS}_${_VARNAME})
    endif(${LIBMEMCACHED_PUBLIC_VAR_NS}_DEBUG)
endfunction(libmemcached_debug)

# Alias all libMemcached_FIND_X variables to LIBMEMCACHED_FIND_X
# Workaround for find_package: no way to force case of variable's names it creates (I don't want to change MY coding standard)
# ---
# NOTE: only prefix is considered, not full name of the variables to minimize conflicts with string(TOUPPER) for example
# libMemcached_foo becomes LIBMEMCACHED_foo not libMemcached_FOO as this is two different variables
set(${LIBMEMCACHED_PRIVATE_VAR_NS}_FIND_PKG_PREFIX "libMemcached")
get_directory_property(${LIBMEMCACHED_PRIVATE_VAR_NS}_CURRENT_VARIABLES VARIABLES)
foreach(${LIBMEMCACHED_PRIVATE_VAR_NS}_VARNAME ${${LIBMEMCACHED_PRIVATE_VAR_NS}_CURRENT_VARIABLES})
    if(${LIBMEMCACHED_PRIVATE_VAR_NS}_VARNAME MATCHES "^${${LIBMEMCACHED_PRIVATE_VAR_NS}_FIND_PKG_PREFIX}")
        string(REGEX REPLACE "^${${LIBMEMCACHED_PRIVATE_VAR_NS}_FIND_PKG_PREFIX}" "${LIBMEMCACHED_PUBLIC_VAR_NS}" ${LIBMEMCACHED_PRIVATE_VAR_NS}_NORMALIZED_VARNAME ${${LIBMEMCACHED_PRIVATE_VAR_NS}_VARNAME})
        set(${${LIBMEMCACHED_PRIVATE_VAR_NS}_NORMALIZED_VARNAME} ${${${LIBMEMCACHED_PRIVATE_VAR_NS}_VARNAME}})
    endif(${LIBMEMCACHED_PRIVATE_VAR_NS}_VARNAME MATCHES "^${${LIBMEMCACHED_PRIVATE_VAR_NS}_FIND_PKG_PREFIX}")
endforeach(${LIBMEMCACHED_PRIVATE_VAR_NS}_VARNAME)

########## Public ##########
find_path(
    ${LIBMEMCACHED_PUBLIC_VAR_NS}_INCLUDE_DIRS
    NAMES memcache.h
    PATH_SUFFIXES "libmemcached-1.0"
)

if(${LIBMEMCACHED_PUBLIC_VAR_NS}_INCLUDE_DIRS)

    find_library(
        ${LIBMEMCACHED_PUBLIC_VAR_NS}_LIBRARIES
        NAMES memcached
    )

    file(STRINGS "${${LIBMEMCACHED_PUBLIC_VAR_NS}_INCLUDE_DIRS}/configure.h" ${LIBMEMCACHED_PRIVATE_VAR_NS}_VERSION_STRING LIMIT_COUNT 1 REGEX "# *define +LIBMEMCACHED_VERSION_STRING *\"[0-9]+\\.[0-9]+\\.[0-9]+\"")
    string(REGEX REPLACE "# *define +LIBMEMCACHED_VERSION_STRING *\"([0-9.]+)\"" "\\1" ${LIBMEMCACHED_PUBLIC_VAR_NS}_VERSION ${${LIBMEMCACHED_PRIVATE_VAR_NS}_VERSION_STRING})
    string(REGEX MATCHALL "[0-9]+" ${LIBMEMCACHED_PRIVATE_VAR_NS}_VERSION_PARTS ${${LIBMEMCACHED_PUBLIC_VAR_NS}_VERSION})
    list(GET ${LIBMEMCACHED_PRIVATE_VAR_NS}_VERSION_PARTS 0 ${LIBMEMCACHED_PUBLIC_VAR_NS}_MAJOR_VERSION)
    list(GET ${LIBMEMCACHED_PRIVATE_VAR_NS}_VERSION_PARTS 1 ${LIBMEMCACHED_PUBLIC_VAR_NS}_MINOR_VERSION)
    list(GET ${LIBMEMCACHED_PRIVATE_VAR_NS}_VERSION_PARTS 2 ${LIBMEMCACHED_PUBLIC_VAR_NS}_PATCH_VERSION)

    include(FindPackageHandleStandardArgs)
    if(${LIBMEMCACHED_PUBLIC_VAR_NS}_FIND_REQUIRED AND NOT ${LIBMEMCACHED_PUBLIC_VAR_NS}_FIND_QUIETLY)
        find_package_handle_standard_args(
            ${LIBMEMCACHED_PUBLIC_VAR_NS}
            REQUIRED_VARS ${LIBMEMCACHED_PUBLIC_VAR_NS}_LIBRARIES ${LIBMEMCACHED_PUBLIC_VAR_NS}_INCLUDE_DIRS
            VERSION_VAR ${LIBMEMCACHED_PUBLIC_VAR_NS}_VERSION
        )
    else(${LIBMEMCACHED_PUBLIC_VAR_NS}_FIND_REQUIRED AND NOT ${LIBMEMCACHED_PUBLIC_VAR_NS}_FIND_QUIETLY)
        find_package_handle_standard_args(${LIBMEMCACHED_PUBLIC_VAR_NS} "libmemcached not found" ${LIBMEMCACHED_PUBLIC_VAR_NS}_LIBRARIES ${LIBMEMCACHED_PUBLIC_VAR_NS}_INCLUDE_DIRS)
    endif(${LIBMEMCACHED_PUBLIC_VAR_NS}_FIND_REQUIRED AND NOT ${LIBMEMCACHED_PUBLIC_VAR_NS}_FIND_QUIETLY)

else(${LIBMEMCACHED_PUBLIC_VAR_NS}_INCLUDE_DIRS)

    if(${LIBMEMCACHED_PUBLIC_VAR_NS}_FIND_REQUIRED AND NOT ${LIBMEMCACHED_PUBLIC_VAR_NS}_FIND_QUIETLY)
        message(FATAL_ERROR "Could not find libmemcached include directory")
    endif(${LIBMEMCACHED_PUBLIC_VAR_NS}_FIND_REQUIRED AND NOT ${LIBMEMCACHED_PUBLIC_VAR_NS}_FIND_QUIETLY)

endif(${LIBMEMCACHED_PUBLIC_VAR_NS}_INCLUDE_DIRS)

mark_as_advanced(
    ${LIBMEMCACHED_PUBLIC_VAR_NS}_INCLUDE_DIRS
    ${LIBMEMCACHED_PUBLIC_VAR_NS}_LIBRARIES
)

# IN (args)
libmemcached_debug("FIND_REQUIRED")
libmemcached_debug("FIND_QUIETLY")
libmemcached_debug("FIND_VERSION")
# OUT
# Linking
libmemcached_debug("INCLUDE_DIRS")
libmemcached_debug("LIBRARIES")
# Version
libmemcached_debug("MAJOR_VERSION")
libmemcached_debug("MINOR_VERSION")
libmemcached_debug("PATCH_VERSION")
libmemcached_debug("VERSION")

# Files generated by MOC, RCC, and UIC may produce clang-tidy warnings. We generate a dummy .clang-tidy file
# in the binary directory that disables all clang-tidy checks except one that will never match.  This one
# check is necessary; clang-tidy reports an error when no checks are enabled. Since the Qt code generators
# will generate source files in the binary tree, clang-tidy will load the configuration from this dummy file
# when the sources are built.
file(
    WRITE "${CMAKE_BINARY_DIR}/.clang-tidy"
    "
---
Checks: '-*,llvm-twine-local'
...
"
)

#feature_summary(
#    INCLUDE_QUIET_PACKAGES
#    WHAT ALL
#    FATAL_ON_MISSING_REQUIRED_PACKAGES
#)
