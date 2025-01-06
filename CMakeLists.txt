cmake_minimum_required(VERSION 3.30)
project(classy-clash)

set(CMAKE_CXX_STANDARD 20)

add_executable(classy-clash main.cpp)

include_directories(C:/raylib/include)
target_link_libraries(classy-clash C:/raylib/lib/libraylib.a)
target_link_libraries(classy-clash gdi32 winmm shell32)
