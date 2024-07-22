

add_library(whereami STATIC whereami.c
        include/whereami.h)
target_include_directories(whereami PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)