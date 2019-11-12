//
// Created by Wang, Chi on 2019/11/12.
//

#include "gtest/gtest.h"
#include <nod.h>
#include <thread>
#include <chrono>


TEST(nod, run_script_file) {
    nod_start(nullptr, "console.log('hello nod')", true, nullptr);
}
