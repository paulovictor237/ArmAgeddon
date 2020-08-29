cmake_minimum_required(VERSION 2.8.3)
project(armageddon_joint_states)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  serial
  std_msgs
  sensor_msgs
)

## Declare a catkin package
catkin_package(
  CATKIN_DEPENDS
    serial
    std_msgs
    sensor_msgs
)

## Build talker and listener
include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(joint_interface_node src/joint_interface_node.cpp)
target_link_libraries(joint_interface_node ${catkin_LIBRARIES})
