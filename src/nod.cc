//
// Created by Wang, Chi on 2019/11/12.
//

#include <vector>
#include <string>
#include <node/node_start.h>
#include "nod.h"

namespace {
    int startNodeWithArgs(const std::vector<const char*> &args) {
        //node_start requires the strings in argv to be allocated in a continuous memory
        std::size_t argv_mem_size = 0;
        std::vector<std::size_t> arg_lens(args.size());
        for (std::size_t i = 0; i < args.size(); i++) {
            arg_lens[i] = strlen(args[i]);
            argv_mem_size += arg_lens[i] + 1;
        }

        static std::vector<char> argv_mem(argv_mem_size);
        static std::vector<char*> argv(args.size());

        char *argv_cur = argv_mem.data();
        for (std::size_t i = 0; i < args.size(); i++) {
            const char *c_arg = args[i];
            size_t c_arg_len = strlen(c_arg);
            std::copy(c_arg, c_arg + c_arg_len + 1, argv_cur);
            argv[i] = argv_cur;
            argv_cur += c_arg_len + 1;
        }

        return node_start((int)args.size(), argv.data());
    }
}

extern "C" void nod_start(const char* argv0, const char* filename, bool eval, napi_addon_register_func reg_func) {
    if (argv0 == nullptr) {
        argv0 = "node";
    }

    std::string preloadCode;
    if (reg_func != nullptr) {
        static napi_module _module =
                {
                        NAPI_MODULE_VERSION,
                        0,
                        __FILE__,
                        reg_func,
                        "_nod_native_mod",
                        nullptr,
                        { 0 },
                };
        napi_module_register(&_module);
        preloadCode = "global._nod_native_mod = process._linkedBinding('_nod_native_mod');";
    }

    preloadCode += "const filename = process.argv[1];";
    if (eval) {
        preloadCode += "require('vm').runInThisContext(filename, { filename: 'nod.entry' });";
    }
    else {
        preloadCode += "require(filename);";
    }

    exit(startNodeWithArgs({ argv0, "-e", preloadCode.c_str(), filename }));
}
