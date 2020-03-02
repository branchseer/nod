//
// Created by Wang, Chi on 2019/11/12.
//

#ifndef NOD_NOD_H
#define NOD_NOD_H

#include <node_api.h>

#ifdef __cplusplus
extern "C" {
#endif
    void nod_start(const char* argv0, const char* filename, bool eval, napi_addon_register_func reg_func);
#ifdef __cplusplus
}
#endif

#endif //NOD_NOD_H
