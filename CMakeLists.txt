cmake_minimum_required(VERSION 3.10)
project(konio)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(konio SHARED
    src/konio.h
    src/kutil.c
    src/writer/writer.c
    src/reader/reader.c
    src/directory/directory.c
)

target_include_directories(konio PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

if(LIBKCORE_INCLUDE_DIR)
    target_include_directories(konio PRIVATE ${LIBKCORE_INCLUDE_DIR})
endif()

target_link_libraries(konio PRIVATE ${LIBKCORE_LIB})

set_target_properties(konio PROPERTIES
    VERSION 0.0.0
    PUBLIC_HEADER "src/konio.h"
)

install(TARGETS konio
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)
