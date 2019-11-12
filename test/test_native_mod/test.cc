//
// Created by Wang, Chi on 2019/11/12.
//

#include "gtest/gtest.h"
#include <nod.h>
#include <thread>
#include <chrono>

namespace {
    napi_value Method(napi_env env, napi_callback_info args) {
        napi_value greeting;
        napi_status status;

        status = napi_create_string_utf8(env, "world", NAPI_AUTO_LENGTH, &greeting);
        if (status != napi_ok) return nullptr;
        return greeting;
    }
    napi_value init_mod(napi_env env, napi_value exports) {
        napi_status status;
        napi_value fn;

        status = napi_create_function(env, nullptr, 0, Method, nullptr, &fn);
        if (status != napi_ok) return nullptr;

        status = napi_set_named_property(env, exports, "hello", fn);
        if (status != napi_ok) return nullptr;
        return exports;
    }
}

TEST(nod, run_script_file) {
    nod_start(nullptr, "console.log(_nod_native_mod.hello())", true, init_mod);
}
