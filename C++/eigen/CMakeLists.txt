CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(eigen_learn)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-O3")

include_directories("/usr/include/eigen3")

add_executable(ch1 eigen1.cpp)
add_executable(ch2 eigen2.cpp)
add_executable(ch3 eigen3.cpp)

add_executable(ch4 eigen4.cpp)
