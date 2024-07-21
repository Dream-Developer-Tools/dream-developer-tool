project(pm)

add_library(${PROJECT_NAME} SHARED PackageManagerPlugin.cpp PackageManagerPlugin.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/plugin)

# copy the so to ROOT_BUILD_DIR/app/plugins
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/app/plugins/${PROJECT_NAME}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
)