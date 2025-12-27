include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Define a helper library for the template configuration if needed
# But since cp_template.h is header-only and spread out, we might just include directories.

# Test executables
enable_testing()

# Include directories for the library
include_directories(${CMAKE_SOURCE_DIR})

# Test for BIT
add_executable(test_BIT ds/test_BIT.cpp polyfill.cpp)
target_link_libraries(test_BIT GTest::gtest_main)
gtest_discover_tests(test_BIT)
