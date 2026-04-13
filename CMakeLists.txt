project(libkonio)

add_library(libkonio SHARED
    src/konio.h
    src/kutil.c
    src/writer/writer.c
    src/reader/reader.c
    src/directory/directory.c
)

target_include_directories(libkonio PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

if(LIBKCORE_INCLUDE_DIR)
    target_include_directories(libkonio PRIVATE ${LIBKCORE_INCLUDE_DIR})
endif()

target_link_libraries(libkonio PRIVATE ${LIBKCORE_LIB})

set_target_properties(libkonio PROPERTIES
    VERSION 0.0.0
    PUBLIC_HEADER "src/konio.h"
)

install(TARGETS libkonio
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)
