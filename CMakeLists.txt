cmake_minimum_required(VERSION 3.15)
project(cf_base)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -DLOCAL -fsanitize=address")


add_executable(cf_main main.cpp)
set_target_properties(cf_main PROPERTIES LINK_FLAGS -Wl,-stack_size,5120000)

add_executable(cf_checker sol_checker.cpp cf-lib/SegmentTree.h cf-lib/BlockedList.h)

add_executable(cf_datagen generate_test_case.cpp)
add_executable(cf_datagen_t generate_test_case_t.cpp)

add_executable(perf_test uptodate.cpp)
set_target_properties(perf_test PROPERTIES LINK_FLAGS -Wl,-stack_size,102400000)
add_executable(gt gt_sol.cpp)