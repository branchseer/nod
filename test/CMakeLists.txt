cmake_minimum_required(VERSION 3.13)

include(FetchContent)
enable_testing()

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.10.0
)
FetchContent_MakeAvailable(googletest)

add_executable(nod_test test_run_script_file/test.cc)
target_link_libraries(nod_test nod gtest_main)
set_property(TARGET nod_test PROPERTY CXX_STANDARD 11)


file(GLOB test_dirs ${CMAKE_CURRENT_LIST_DIR}/test_*)
foreach(test_dir ${test_dirs})
    get_filename_component(test_name ${test_dir} NAME)
    add_executable(${test_name} ${test_dir}/test.cc)
    target_link_libraries(${test_name} nod gtest_main)
    set_target_properties(${test_name} PROPERTIES
        CXX_STANDARD 11
        RUNTIME_OUTPUT_DIRECTORY ${test_name}
    )
    if(EXISTS ${test_dir}/res)
        add_custom_command(TARGET ${test_name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${test_dir}/res $<TARGET_FILE_DIR:${test_name}>/res)
    endif ()
endforeach()
