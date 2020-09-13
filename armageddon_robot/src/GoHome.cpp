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
  // PARA VER AS MENSAGENS PUBLICADAS EM ROS_INFO
  // rostopic type /rosout | rosmsg show
  // rostopic echo /rosout/msg
  // rqt_console
//+-------------------------------------------------------------------------------+
  // TIPOS DE MENSAGENS
  // https://wiki.ros.org/rosconsole
  ROS_WARN("TIPOS DE MENSAGENS");
  ROS_INFO("MSG INFO");
  ROS_WARN("MSG WARN");
  ROS_ERROR("MSG ERROR");
  ROS_FATAL("MSG FATAL");
//+-------------------------------------------------------------------------------+
  ROS_WARN("Reference Frame");
  ROS_INFO("PlanningFrame: %s", group.getPlanningFrame().c_str());
  ROS_WARN("Name of the end-effector");
  ROS_INFO("EndEffectorLink: %s", group.getEndEffectorLink().c_str());
  
  std::vector<std::string> nomes;
  int indice;

  ROS_WARN("Lista dos Grupos");
  indice=1;
  nomes = group.getJointModelGroupNames();
  // for (auto &valor : nomes) ROS_INFO("JointName: %s ", valor.c_str());
  for (auto &valor : nomes)ROS_INFO_STREAM("GroupName(" << indice++ << "): " << valor);
  
  ROS_WARN("Lista das Juntas");
  indice=1;
  nomes = group.getJointNames();
  // for (auto &valor : nomes) ROS_INFO("JointName: %s ", valor.c_str());
  for (auto &valor : nomes)ROS_INFO_STREAM("JointName(" << indice++ << "): " << valor);

  
  ROS_WARN("Lista dos elos");
  indice=1;
  nomes = group.getLinkNames();
  // for (auto &valor : nomes) ROS_INFO("LinkName: %s ", valor.c_str());
  for (auto &valor : nomes)ROS_INFO_STREAM("LinkName(" << indice++ << "): " << valor);

//+-------------------------------------------------------------------------------+
  //seta o movimento
  moveit::core::RobotStatePtr current_state = group.getCurrentState();
  std::vector<double> joint_group_positions;
  current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
  joint_group_positions[0] = 0.0;  // radians
  joint_group_positions[1] = 0.0;  // radians
  joint_group_positions[2] = 0.0;  // radians
  joint_group_positions[3] = 0.0;  // radians
  joint_group_positions[4] = 0.0;  // radians
  joint_group_positions[5] = 0.0;  // radians
  group.setJointValueTarget(joint_group_positions);
  //move o objeto
  ROS_WARN("INICIANDO GOHOME");
  group.move();
  indice=1;
  ROS_WARN("Lista das Juntas");
  // for (auto& valor : joint_group_positions)ROS_INFO("%f ",valor);
  for (auto &valor : joint_group_positions)ROS_INFO_STREAM("Joint(" << indice++ << "): " << valor);
//+-------------------------------------------------------------------------------+
  ROS_WARN("FIM");
  ros::shutdown();

 return 0;
}
