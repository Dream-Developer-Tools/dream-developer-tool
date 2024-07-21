

add_subdirectory(pm)

add_custom_target(core-plugins)
add_dependencies(core-plugins pm)