cmake_minimum_required(VERSION 3.30)
project(mocking_fast_pimpl)

set(INCLUDE_DIRS include)
set(LIB_SRC IImpl.cpp)

add_library(
        impl STATIC
        IImpl.cpp
        impl.cpp
        ${LIB_SRC}
)

set_target_properties( impl
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "../lib"
        LIBRARY_OUTPUT_DIRECTORY "../lib"
)

target_compile_options(impl PRIVATE "-O0" "-Werror")

include_directories(
        include
        ../iface
        ../impl
        ${INCLUDE_DIRS}
)
