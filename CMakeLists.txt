cmake_minimum_required(VERSION 3.26)
project(ddt-core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ENABLE_EXPORTS ON)

add_subdirectory(libs/json)
add_subdirectory(libs/cpr)
add_subdirectory(core/core-plugins)
add_subdirectory(batteries)


add_subdirectory(core/src)
add_subdirectory(core/interface)
