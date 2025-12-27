cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 23)
set(use_gcc_flag OFF)
if(use_gcc_flag)
    # gcc do not support address sanitizer on arm64 architecture
    set(CMAKE_C_COMPILER "/usr/local/bin/gcc-14")
    set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-14")
else()
    # Use brew installed compilers because system compilers are lagged in version
    set(CMAKE_C_COMPILER "/usr/local/opt/llvm/bin/clang")
    set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")
endif()

project(cf_base)

# If debugging, may need to skip some flags.
# Had experience of watches not working before turning flags off.
set(debug_flag ON)

if(use_gcc_flag)
    # Use only for resolving codeforces CE due to discrepancy of local and remote env
    set(CMAKE_CXX_FLAGS "-Wall -DLOCAL")
else()
    if(debug_flag)
        set(CMAKE_CXX_FLAGS "-Wall -DLOCAL -fsanitize=address -fexperimental-library")
    else()
        # For meanings of the options, refer to: https://codeforces.com/blog/entry/15547
        # The last line is custom added.
        #   -DLOCAL is for file input locally
        #   -fexperimental-library is for non officially supported libraries such as std::format
        set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal \
            -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align\
            -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address\
            -fsanitize=undefined -fno-sanitize-recover -fstack-protector\
            -DLOCAL -fexperimental-library")
    endif()
endif()

add_executable(cf_main main.cpp)
set_target_properties(cf_main PROPERTIES LINK_FLAGS -Wl,-stack_size,10240000)
#add_executable(cf_checker sol_checker.cpp cf-lib/SegmentTree.h cf-lib/BlockedList.h)

#add_executable(cf_datagen generate_test_case.cpp)
#add_executable(repro repro_hash.cpp tests/polyfill.cpp)
#add_executable(cf_datagen_t generate_test_case_t.cpp)

#add_executable(perf_test uptodate.cpp)
#set_target_properties(perf_test PROPERTIES LINK_FLAGS -Wl,-stack_size,102400000)

#add_executable(gt gt_sol.cpp)

option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()