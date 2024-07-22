
add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE core.cpp core.h)

# PROJECT CODE
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/core-include
        ${CMAKE_SOURCE_DIR}/plugin
        ${CMAKE_SOURCE_DIR}/batteries/plugin-import
)
add_dependencies(${PROJECT_NAME} core-plugins)

# EXTERNAL LIBRARIES
find_library(LIBARCHIVE_LIBRARY REQUIRED
        NAMES archive
        PATHS /lib/x86_64-linux-gnu/)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ssl3
        ${LIBARCHIVE_LIBRARY}
        jsoncpp_lib
        cpr::cpr
        whereami
)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${LIBARCHIVE_INCLUDE_DIRS}
        libs/json/include
        libs/cpr/include
)

