cmake_minimum_required(VERSION 3.25)
project(ddt-core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ENABLE_EXPORTS ON)



add_subdirectory(${CMAKE_SOURCE_DIR}/libs/json)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/cpr)
add_subdirectory(${CMAKE_SOURCE_DIR}/core/core-plugins)
add_subdirectory(${CMAKE_SOURCE_DIR}/batteries)


add_subdirectory(core/src)
add_subdirectory(core/interface)


