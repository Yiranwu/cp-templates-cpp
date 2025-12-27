# Testing Infrastructure

This directory contains unit tests for the `cp-templates-cpp` project, implemented using [Google Test](https://github.com/google/googletest).

## Prerequisites

*   CMake 3.15 or later
*   A C++23 compatible compiler (Clang recommended on macOS)

## Building Tests

Tests are disabled by default in the main build to save time. To build them, you must enable the `BUILD_TESTS` option.

1.  **Configure the project with tests enabled:**

    ```bash
    cmake -S . -B build_tests -DBUILD_TESTS=ON
    ```

    *   `-S .`: Source directory (project root).
    *   `-B build_tests`: Build directory (can be named anything, e.g., `build` or `cmake-build-debug`).
    *   `-DBUILD_TESTS=ON`: **Required** to include the `tests/` subdirectory and testing targets.

2.  **Build the tests:**

    ```bash
    cmake --build build_tests
    ```

## Running Tests

After building, you can run the test executables directly or use `ctest`.

### Option 1: Run specific test executable
The compiled test binaries are located in `build_tests/tests/`.

```bash
./build_tests/tests/test_BIT
```

### Option 2: Run all tests using CTest
```bash
cd build_tests
ctest --output-on-failure
```

## Adding New Tests

1.  Create a new `.cpp` file in the appropriate subdirectory (e.g., `tests/ds/test_MyDS.cpp`).
2.  Add the new executable to `tests/CMakeLists.txt`:
    ```cmake
    add_executable(test_MyDS ds/test_MyDS.cpp polyfill.cpp)
    target_link_libraries(test_MyDS GTest::gtest_main)
    gtest_discover_tests(test_MyDS)
    ```
    *   **Note:** Include `polyfill.cpp` in the source list if you run into linker errors regarding `std::__1::__hash_memory` on macOS/Clang.

## Troubleshooting

*   **Linker Errors (std::__1::__hash_memory):**
    If you see "Undefined symbols for architecture arm64: std::__1::__hash_memory", ensure `polyfill.cpp` is included in your test executable target in `tests/CMakeLists.txt`. This is a workaround for an issue with `-fexperimental-library` on AppleClang.
