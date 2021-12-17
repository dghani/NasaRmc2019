cmake_minimum_required(VERSION 2.8.3)
project(tfr_read_torque)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

find_package(GTest REQUIRED)

catkin_package(
)

include_directories(
    include/${PROJECT_NAME}
    ${catkin_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
)

add_executable(read_torque
    src/read_torque.cpp
)

