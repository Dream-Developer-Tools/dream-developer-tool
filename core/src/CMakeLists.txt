

add_library(${PROJECT_NAME} SHARED
        Core.cpp Core.h
        calls/CoreCalls.h
        plugin-manager/PluginManager.h
        calls/Requests.h
        calls/TarUtils.h
        Helpers.h
        calls/Requests.h
        commands/CoreCommands.cpp
        commands/CoreCommands.h
)

# PROJECT CODE
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/core-include
        ${CMAKE_SOURCE_DIR}/plugin
        ${CMAKE_SOURCE_DIR}/batteries/plugin-import
)
add_dependencies(${PROJECT_NAME} core-plugins)

# EXTERNAL LIBRARIES
find_library(LIBARCHIVE_LIBRARY REQUIRED
        NAMES archive
        PATHS /lib/x86_64-linux-gnu/)

target_link_libraries(${PROJECT_NAME} PUBLIC
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


# make a copy of the ddt-core library to the root directory of the build
# for binding purposes
add_custom_command(TARGET ddt-core POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ddt-core> ${CMAKE_BINARY_DIR}/app
)
