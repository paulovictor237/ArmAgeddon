# ... Packs originais do MoveIt ...
cmake_minimum_required(VERSION 3.1.3)
project(ArmAgeddon)

find_package(catkin REQUIRED)

catkin_package()

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  PATTERN "setup_assistant.launch" EXCLUDE)
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

# ... moveit_tutorials/doc/move_group_python_interface ...
# install(PROGRAMS
#   scripts/move_group_python_interface_tutorial.py
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

# install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

# ... moveit_tutorials/doc/move_group_interface ...
# add_executable(move_group_interface_tutorial src/move_group_interface_tutorial.cpp)
# target_link_libraries(move_group_interface_tutorial ${catkin_LIBRARIES} ${Boost_LIBRARIES})
# install(TARGETS move_group_interface_tutorial DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

# install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

# ... Mastering ROS for Robotics Programming (2018) ...

### Find catkin macros and libraries
### if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
### is used, also find other catkin packages
# find_package(catkin REQUIRED COMPONENTS
#   cmake_modules
#   interactive_markers
#   moveit_core
#   moveit_visual_tools
#   moveit_ros_planning
#   moveit_ros_planning_interface
#   moveit_ros_perception
#   pluginlib
#   roscpp
#   std_msgs
# )

### Declare a cpp executable
# add_executable(pick_place_3 src/pick_place_3.cpp)
# add_dependencies(pick_place_3 seven_dof_arm_test_generate_messages_cpp)
# target_link_libraries(pick_place_3 ${catkin_LIBRARIES})