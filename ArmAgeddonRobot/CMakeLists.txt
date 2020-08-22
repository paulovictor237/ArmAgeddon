#===========================================================================
# ... ArmAgeddonRobot (2020) ...
#===========================================================================
cmake_minimum_required(VERSION 3.0.2)
project(ArmAgeddonRobot)

find_package(catkin REQUIRED)

catkin_package()

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
#===========================================================================
# ... ws_moveit/src/moveit_tutorials/CMakeLists.txt ...
#===========================================================================
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(catkin REQUIRED COMPONENTS
    interactive_markers
    moveit_core
    moveit_visual_tools
    moveit_ros_planning
    moveit_ros_planning_interface
    moveit_ros_perception
    pluginlib
    geometric_shapes
    pcl_ros
    pcl_conversions
    rosbag
    tf2_ros
    tf2_eigen
    tf2_geometry_msgs
)

find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED system filesystem date_time thread)

set(THIS_PACKAGE_INCLUDE_DIRS doc/interactivity/include)

## Build ##
include_directories(${THIS_PACKAGE_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIRS})

#===========================================================================
# ... Mastering ROS for Robotics Programming (2018) ...
#===========================================================================
# find_package(catkin REQUIRED COMPONENTS
#   cmake_modules
#   roscpp
#   std_msgs
# )
# set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
# ## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
# ## Build ##
# include_directories(${catkin_INCLUDE_DIRS})

### Declare a cpp executable
# add_executable(pick_place_3 src/pick_place_3.cpp)
# add_dependencies(pick_place_3 seven_dof_arm_test_generate_messages_cpp)
# target_link_libraries(pick_place_3 ${catkin_LIBRARIES})
#===========================================================================
# ... ## Testing ## ...
#===========================================================================

# ... listener ...
add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
install(TARGETS listener DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

## Declare a cpp executable
add_executable(GoHome src/GoHome.cpp)
target_link_libraries(GoHome ${catkin_LIBRARIES})
install(TARGETS GoHome DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

## Declare a cpp executable
add_executable(GoRandom src/GoRandom.cpp)
target_link_libraries(GoRandom ${catkin_LIBRARIES})
install(TARGETS GoRandom DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

## Declare a cpp executable
add_executable(CartesianPath src/CartesianPath.cpp)
target_link_libraries(CartesianPath ${catkin_LIBRARIES})
install(TARGETS CartesianPath DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})