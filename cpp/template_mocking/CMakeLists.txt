cmake_minimum_required(VERSION 3.30)
project(template_mocking)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(template_mocking main.cpp
        src/A.cpp
        src/A.h
        src/impl.cpp
        src/impl.h
        test/hello_test.cpp)


target_include_directories(
        template_mocking PUBLIC
        src
)


target_link_libraries(
        template_mocking
        gtest
        gtest_main
        impl
)

target_link_directories(
        template_mocking PUBLIC
        lib
)

# testing
enable_testing()

add_executable(
        tests
        test/hello_test.cpp
)

target_link_directories(
        tests PUBLIC
        lib
)

target_link_libraries(
        tests
        GTest::gtest_main
        impl
)

target_include_directories(
        tests PUBLIC
        src
)

include(GoogleTest)
gtest_discover_tests(tests)

set(UNIT_TEST tests)
add_custom_command(
        TARGET ${UNIT_TEST}
        COMMENT "Run tests"
        POST_BUILD
        COMMAND ${UNIT_TEST}
)

add_test(NAME hello_test COMMAND tests)
