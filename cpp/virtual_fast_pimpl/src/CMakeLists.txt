cmake_minimum_required(VERSION 3.30)
project(virtual_fast_pimpl)

option(OS_A "LINUX" ON)
option(OS_B "QNX" OFF)

if(OS_A)
  add_definitions(-DOS_A)
  add_compile_definitions(OS_A)
  add_subdirectory(OS_A)
  set(INCLUDE_DIRS OS_A/include)
  set(LIB_SRC OS_A/impl.cpp)
else()
  add_definitions(-DOS_B)
  add_compile_definitions(OS_B)
  add_subdirectory(OS_B)
  set(INCLUDE_DIRS OS_B/include)
  set(LIB_SRC OS_B/impl.cpp)
endif()

add_library(
        impl STATIC
        iface.cpp
        ${LIB_SRC}
)

set_target_properties( impl 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "../lib"
    LIBRARY_OUTPUT_DIRECTORY "../lib"
)

include_directories(
        include
        ../iface
        ${INCLUDE_DIRS}
)




