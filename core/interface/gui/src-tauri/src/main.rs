// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

struct ReturnData {
    data: String,
    status: i32,
}

use libc::{c_int, c_char};
use libloading::{Library, Symbol};

#[tauri::command]
fn list_plugins() -> (String, i32) {
    ("Hello from Rust!".to_string(), 0)
}


fn main() {
    unsafe {
        let lib: Library = Library::new("./libddt-core.so").unwrap();
        // let run: Symbol<unsafe extern fn(plugin: String, argc: c_int, argv: *const c_char, gui_mode: u8) -> ReturnData> = lib.get(b"runCoreCommand").unwrap();
        // let ARGV = CString::new("version").expect("CString::new failed");
        // let result = run("core".parse().unwrap(), 1, ARGV.as_ptr(), true as u8);
        let run: Symbol<unsafe extern fn(gui_mode: c_int) -> ReturnData> = lib.get(b"a").unwrap();
        const TRUE: c_int = 0;
        let result = run(TRUE);

        list_plugins();
        tauri::Builder::default()
            .invoke_handler(tauri::generate_handler![list_plugins])
            .run(tauri::generate_context!())
            .expect("error while running tauri application");
    }
}
