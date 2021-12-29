# If you're having trouble getting your things to build, visit the ROS
# tutorials at <http://wiki.ros.org/ROS/Tutorials> and also read the ROS
# CMake documentation at <http://wiki.ros.org/catkin/CMakeLists.txt>.

cmake_minimum_required(VERSION 2.8.3)
project(tfr_monitoring)


add_compile_options(-std=c++11)


find_package(catkin REQUIRED COMPONENTS
    roscpp
    tfr_can
    std_msgs
)

find_package(GTest REQUIRED)

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
## catkin_python_setup()


###################################
## catkin specific configuration ##
###################################

catkin_package()


###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${GTEST_INCLUDE_DIRS}
)

add_executable(monitoring_battery src/monitoring_battery.cpp)
add_dependencies(monitoring_battery ${catkin_EXPORTED_TARGETS})
target_link_libraries(monitoring_battery ${catkin_LIBRARIES})

add_executable(monitoring_arm_velocity src/monitoring_arm_velocity.cpp)
add_dependencies(monitoring_arm_velocity ${catkin_EXPORTED_TARGETS})
target_link_libraries(monitoring_arm_velocity ${catkin_LIBRARIES})

add_executable(read_arm_torque src/read_torque.cpp)
add_dependencies(read_arm_torque ${catkin_EXPORTED_TARGETS})
target_link_libraries(read_arm_torque ${catkin_LIBRARIES})


#############
## Testing ##
#############

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
