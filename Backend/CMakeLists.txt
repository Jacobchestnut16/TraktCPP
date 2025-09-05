cmake_minimum_required(VERSION 4.0)
project(Backend)

set(CMAKE_CXX_STANDARD 20)

set(Qt5_DIR /opt/homebrew/opt/qt@5/lib/cmake/Qt5)  # or qt6 if using Qt6

find_package(Qt5 REQUIRED Core Network)
include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(Backend src/main.cpp)
add_executable(AppTest tests/apiTest.cpp)

target_link_libraries(Backend
        Qt5::Core
        Qt5::Network
)