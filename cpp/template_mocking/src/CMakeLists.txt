cmake_minimum_required(VERSION 3.30)
project(template_mocking)

add_library(
        impl STATIC
        A.cpp
        impl.cpp
        ${LIB_SRC}
)

set_target_properties( impl
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "../lib"
        LIBRARY_OUTPUT_DIRECTORY "../lib"
)

target_compile_options(impl PRIVATE "-Oz" "-Werror")
