cmake_minimum_required(VERSION 3.22)
project(json)

set(CMAKE_CXX_STANDARD 20)

add_library(
        json
        sources/json/json.cpp
)

target_include_directories(json PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
add_executable(cli cli/main.cpp)

target_link_libraries(cli json)

