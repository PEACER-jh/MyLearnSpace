cmake_minimum_required(VERSION 3.8)
project(learn_bt)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS coroutine QUIET)
find_package(Curses QUIET)
find_package(Threads REQUIRED)
# find_package(behaviortree_cpp REQUIRED)
# message(STATIC ${behahaviortree_cpp_LIBRARIES})

list(APPEND BEHAVIOR_TREE_EXTERNAL_LIBRARIES
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
    ${Boost_LIBRARIES} 
    ${CURSES_LIBRARIES} )

include_directories(include
                    /usr/local/include/behaviortree_cpp)

# file(GLOB my_tree_source ${PROJECT_SOURCE_DIR}/src/mytree.cpp)
# add_library(learn_mytree ${my_tree_source})

add_library(learn_mytree ${PROJECT_SOURCE_DIR}/src/mytree.cpp)
add_library(learn_blackboard_port ${PROJECT_SOURCE_DIR}/src/blackboard_port.cpp)
add_library(learn_generic_port ${PROJECT_SOURCE_DIR}/src/generic_port.cpp)
add_library(learn_reactive_port ${PROJECT_SOURCE_DIR}/src/reactive.cpp)
add_library(learn_sub_tree ${PROJECT_SOURCE_DIR}/src/subtree.cpp)
add_library(learn_remap_port ${PROJECT_SOURCE_DIR}/src/remap_port.cpp)
add_library(learn_multi_tree ${PROJECT_SOURCE_DIR}/src/multi_xml.cpp)

# target_link_libraries(learn_bt behavior_tree::behavior_tree)
add_executable(main ./text/main.cpp)
add_executable(main_bp ./text/main_bp.cpp)
add_executable(main_gp ./text/main_gp.cpp)
add_executable(main_re ./text/main_re.cpp)
add_executable(main_sb ./text/main_sub.cpp)
add_executable(main_rm ./text/main_rm.cpp)
add_executable(main_ml ./text/main_mul.cpp)

target_link_libraries(main 
    learn_mytree 
    /usr/local/lib/libbehaviortree_cpp.so
    ${BEHAVIOR_TREE_EXTERNAL_LIBRARIES})

target_link_libraries(main_bp 
    learn_blackboard_port
    /usr/local/lib/libbehaviortree_cpp.so
    ${BEHAVIOR_TREE_EXTERNAL_LIBRARIES})

target_link_libraries(main_gp 
    learn_generic_port
    /usr/local/lib/libbehaviortree_cpp.so
    ${BEHAVIOR_TREE_EXTERNAL_LIBRARIES})

target_link_libraries(main_re
    learn_reactive_port 
    /usr/local/lib/libbehaviortree_cpp.so
    ${BEHAVIOR_TREE_EXTERNAL_LIBRARIES})

target_link_libraries(main_sb
    learn_sub_tree 
    /usr/local/lib/libbehaviortree_cpp.so
    ${BEHAVIOR_TREE_EXTERNAL_LIBRARIES})

target_link_libraries(main_rm
    learn_remap_port 
    /usr/local/lib/libbehaviortree_cpp.so
    ${BEHAVIOR_TREE_EXTERNAL_LIBRARIES})

target_link_libraries(main_ml
    learn_multi_tree
    /usr/local/lib/libbehaviortree_cpp.so
    ${BEHAVIOR_TREE_EXTERNAL_LIBRARIES})