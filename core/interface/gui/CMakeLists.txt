
add_custom_target(ddt-gui
#        COMMAND yarn tauri build
#        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src-tauri/target/release/ddt-gui ${CMAKE_BINARY_DIR}/app
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ddt-core
        COMMENT "Building DDT GUI"
)