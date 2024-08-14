

add_subdirectory(cli)
add_subdirectory(gui)

add_custom_target(app
        DEPENDS ddt ddt-gui
)