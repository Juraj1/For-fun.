cmake_minimum_required(VERSION 3.30)
project(virtual_fast_pimpl)

add_subdirectory(src)

include_directories(    iface
                        mock
)

SET(APP_EXE binary)

ADD_EXECUTABLE( ${APP_EXE}
                main.cpp
                mock/MockIface.cpp
)

TARGET_LINK_LIBRARIES( ${APP_EXE}
                       impl )
