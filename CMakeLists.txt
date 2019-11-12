cmake_minimum_required(VERSION 3.13)

include(FetchContent)

project(nod)

if(NOT DEFINED NOD_NODE_VERSION)
    set(NOD_NODE_VERSION v12.13.0)
endif()

if(NOT DEFINED NOD_NODE_OS)
    if (UNIX)
        if (APPLE)
            set(NOD_NODE_OS darwin)
        else()
            set(NOD_NODE_OS linux)
        endif()
    else()
        set(NOD_NODE_OS win32)
    endif()
endif()

if(NOT DEFINED NOD_NODE_ARCH)
    set(NOD_NODE_ARCH x64)
endif()

if(NOT DEFINED NOD_NODE_CONFIG)
    set(NOD_NODE_CONFIG "-nointl")
endif()

FetchContent_Declare(
    libnode
    URL https://github.com/patr0nus/libnode/releases/download/libnode-${NOD_NODE_VERSION}/libnode-${NOD_NODE_VERSION}-${NOD_NODE_OS}-${NOD_NODE_ARCH}${NOD_NODE_CONFIG}.zip
)
FetchContent_MakeAvailable(libnode)

add_library(nod STATIC src/nod.cc)
set_property(TARGET nod PROPERTY CXX_STANDARD 11)

target_include_directories(nod PUBLIC src/include)
target_link_libraries(nod libnode)

if("${NOD_ENABLE_TEST}" EQUAL "1")
    add_subdirectory(test)
endif()
