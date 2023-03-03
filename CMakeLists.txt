cmake_minimum_required(VERSION 3.24)
project(nb-asio)

set(CMAKE_CXX_STANDARD 17)

# nb-asio-lib target
#set(NB_ASIO_LIB ${PROJECT_NAME}-lib)
#add_library(${NB_ASIO_LIB}


# example target
set(EXAMPLE ${PROJECT_NAME}-example)
add_executable(${EXAMPLE}
        examples/multi_thread.cpp
        )

target_include_directories(${EXAMPLE} PUBLIC
        ./
        michael-scott-queue/include
        )

