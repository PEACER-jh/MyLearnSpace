cmake_minimum_required(VERSION 3.10)
project(Ceres-Solver)

find_package(OpenCV 4 REQUIRED)
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})
include_directories(${OpenCV_LIBRARIES})

add_executable(functor functor.cpp)
target_link_libraries(functor ${CERES_LIBRARIES})

add_executable(squares squares.cpp)
target_link_libraries(squares ${CERES_LIBRARIES})

add_executable(derivatives derivatives.cpp)
target_link_libraries(derivatives ${CERES_LIBRARIES})

add_executable(powell powell.cpp)
target_link_libraries(powell ${CERES_LIBRARIES})

add_executable(curve curve.cpp)
target_link_libraries(curve ${CERES_LIBRARIES} ${OpenCV_LIBRARIES})