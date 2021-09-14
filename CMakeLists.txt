cmake_minimum_required(VERSION 3.17)
project(test_shared_ptr)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)

#set(CMAKE_BUILD_TYPE Release)

set(CFLAGS
        -m64
        -pthread
        -march=native
        -O3
        #        -ggdb
        ${WERROR_FLAGS})

set(INC_DIR /usr/include
        /usr/local/include
        )
set(LINK_DIR
        /usr/local/lib
        /usr/local/lib64
        /usr/lib64)

include_directories(${INC_DIR})
link_directories(${LINK_DIR})

link_libraries(libglog.a)

add_compile_options(${CFLAGS})

add_executable(test_shared_ptr main.cpp)

target_link_libraries(
        test_shared_ptr
        pthread
        libgflags.a
        libglog.a
)