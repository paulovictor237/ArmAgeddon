//+-------------------------------------------------------------------------------+
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//+-------------------------------------------------------------------------------+
#include <moveit/move_group_interface/move_group_interface.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "AppGoRandom", ros::init_options::AnonymousName);
  // start a ROS spinning thread
  ros::AsyncSpinner spinner(1);
  spinner.start();
  // this connecs to a running instance of the move_group node
	moveit::planning_interface::MoveGroupInterface group("robot_arm");
  // specify that our target will be a random one
  
  moveit::planning_interface::MoveItErrorCode success;
  group.setPlannerId("RRTConnectkConfigDefault");
  group.setPlanningTime(10.0);
  
  // do{
    group.setRandomTarget();
    success = group.move();
    ROS_INFO("Visualizing plan 1 (pose goal) %s: %d",success.val ? "SUCCESS":"FAILED",success.val);
  // }while(success.val!=1);

  // plan the motion and then move the group to the sampled target 
  
  // ros::waitForShutdown();
  ros::shutdown();
  return 0;
}
