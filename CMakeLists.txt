cmake_minimum_required(VERSION 3.10)
project(konio)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Detect if we're being built as a subdirectory
if(NOT DEFINED KCORE_TARGETS_AVAILABLE)
    # Independent build - need to find libkcore
    find_package(PkgConfig QUIET)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(KCORE libkcore)
    endif()
    
    if(NOT KCORE_FOUND)
        # Try to find it in system paths
        find_library(KCORE_LIBRARY kcore REQUIRED)
        set(LIBKCORE_LIB ${KCORE_LIBRARY})
    else()
        set(LIBKCORE_LIB ${KCORE_LIBRARIES})
    endif()
else()
    set(LIBKCORE_LIB_STATIC kcore_static)
    set(LIBKCORE_LIB_SHARED kcore_shared)
endif()

# Source files
set(KONIO_SOURCES
    src/kutil.c
    src/writer/writer.c
    src/reader/reader.c
    src/directory/directory.c
)

# Static library
add_library(konio_static STATIC ${KONIO_SOURCES})
target_include_directories(konio_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)
if(LIBKCORE_INCLUDE_DIR)
    target_include_directories(konio_static PRIVATE ${LIBKCORE_INCLUDE_DIR})
endif()
if(DEFINED KCORE_TARGETS_AVAILABLE)
    target_link_libraries(konio_static PRIVATE ${LIBKCORE_LIB_STATIC})
else()
    target_link_libraries(konio_static PRIVATE ${LIBKCORE_LIB})
endif()
set_target_properties(konio_static PROPERTIES
    VERSION 0.0.0
    PUBLIC_HEADER "src/konio.h"
    OUTPUT_NAME konio
)

# Shared library
add_library(konio_shared SHARED ${KONIO_SOURCES})
target_include_directories(konio_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)
if(LIBKCORE_INCLUDE_DIR)
    target_include_directories(konio_shared PRIVATE ${LIBKCORE_INCLUDE_DIR})
endif()
if(DEFINED KCORE_TARGETS_AVAILABLE)
    target_link_libraries(konio_shared PRIVATE ${LIBKCORE_LIB_SHARED})
else()
    target_link_libraries(konio_shared PRIVATE ${LIBKCORE_LIB})
endif()
set_target_properties(konio_shared PROPERTIES
    VERSION 0.0.0
    PUBLIC_HEADER "src/konio.h"
    OUTPUT_NAME konio
)

# Default alias (static by default for convenience)
add_library(konio ALIAS konio_static)

# Install both
install(TARGETS konio_static konio_shared
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)
