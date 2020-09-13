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
#include "std_msgs/String.h"
using namespace std;

//+-------------------------------------------------------------------------------+
// 1. O topico funciona como uma thread.
// 2. Para passar parâmetros para uma thread no ROS eh necessario criar uma classe

// %Tag(CLASS_WITH_DECLARATION)%
class Listener
{
public:
  moveit::planning_interface::MoveGroupInterface *group;
  string signal;
  void callback(const std_msgs::String::ConstPtr& msg);
};
// %EndTag(CLASS_WITH_DECLARATION)%

// aqui declaramos a funcao (thread)
void Listener::callback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  this->signal=msg->data.c_str();
  if(signal=="STOP"){
    ROS_FATAL("Stop any trajectory in execution");
    this->group->stop();
  }
}
//+-------------------------------------------------------------------------------+

int main(int argc, char **argv)
{
//+-------------------------------------------------------------------------------+
  // iniciacao padrao para nodes
  ros::init(argc, argv, "AppGoHome");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(2);
  spinner.start();
  /* This sleep is ONLY to allow Rviz to come up */
  // sleep(2.0);
//+-------------------------------------------------------------------------------+
  // nome do grupo que sera movimentado
  static const std::string PLANNING_GROUP = "robot_arm";
  // linhas padrao para criar um grupo a ser movimentado
  moveit::planning_interface::MoveGroupInterface group(PLANNING_GROUP);
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  const robot_state::JointModelGroup* joint_model_group = group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
  // aqui inicia o programa de fato
//+-------------------------------------------------------------------------------+
  // Cria o Topico 'armageddon/stop_robot' para o node node_handle
  ROS_WARN("Lendo sinal do Drive");
  ROS_INFO("No tópico 'armageddon/stop_robot' digite 'STOP' para parar o robo");
  // %Tag(SUBSCRIBER)%
  Listener listener;
  listener.group=&group;
  ros::Subscriber sub = node_handle.subscribe("armageddon/stop_robot", 1000, &Listener::callback, &listener);
  // %EndTag(SUBSCRIBER)%
  // ros::spin();
  spinner.start();
  ros::waitForShutdown();
//+-------------------------------------------------------------------------------+
  ROS_WARN("FIM");
  ros::shutdown();

  return 0;
}
