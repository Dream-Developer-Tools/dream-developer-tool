project(ddt)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME}  PRIVATE ${CMAKE_SOURCE_DIR}/core/src)
target_link_libraries(${PROJECT_NAME} PRIVATE ddt-core)
# override the output directory
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app)