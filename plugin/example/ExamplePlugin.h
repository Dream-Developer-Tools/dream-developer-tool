#ifndef EXAMPLEPLUGIN_H
#define EXAMPLEPLUGIN_H

#include "../plugin.h"

#define VERSION "0.1.0" // This is the version of the plugin

const ExamplePlugin = Plugin {
    name: "Example",
    runCommand: fn(pluginCalled: &str, argc: i32, argv: *const *const i8) -> ReturnData {
        if pluginCalled == "example" {
            let command = unsafe { std::ffi::CStr::from_ptr(argv[0]).to_str().unwrap() };
            if command == "version" || command == "v" {
                return ReturnData { VERSION, SUCCESS };
            }
        }
        ReturnData { "UC", UNKNOWN_COMMAND }
    },
    registerPlugin: fn() {}
};

#endif //EXAMPLEPLUGIN_H
