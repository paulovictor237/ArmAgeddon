//+-------------------------------------------------------------------------------+
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//+-------------------------------------------------------------------------------+
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/LinearMath/Quaternion.h>

#include <ros/console.h>
using namespace std;

int main(int argc, char **argv)
{
//+-------------------------------------------------------------------------------+
  // iniciacao padrao para nodes
  ros::init(argc, argv, "AppGoHome");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();
  /* This sleep is ONLY to allow Rviz to come up */
  sleep(2.0);
//+-------------------------------------------------------------------------------+
  // nome do grupo que sera movimentado
  static const std::string PLANNING_GROUP = "robot_arm";
  // linhas padrao para criar um grupo a ser movimentado
  moveit::planning_interface::MoveGroupInterface group(PLANNING_GROUP);
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  const robot_state::JointModelGroup* joint_model_group = group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
  // aqui inicia o programa de fato
//+-------------------------------------------------------------------------------+
  // Stop any trajectory execution, if one is active
  ROS_FATAL("Stop any trajectory execution");
  group.stop();
//+-------------------------------------------------------------------------------+
  ros::shutdown();

 return 0;
}
