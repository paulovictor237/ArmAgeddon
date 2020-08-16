/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2013, SRI International
 *  All rights reserved.
 *  Copyright (c) 2017, Jonathan Cacace
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of SRI International nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Authors: Sachin Chitta
						Jonathan Cacace
*/
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/LinearMath/Quaternion.h>


int main(int argc, char **argv)
{
  // iniciacao padrao para nodes
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();
  /* This sleep is ONLY to allow Rviz to come up */
  sleep(2.0);

  // nome do grupo que sera movimentado
  static const std::string PLANNING_GROUP = "robot_arm";
  // linhas padrao para criar um grupo a ser movimentado
  moveit::planning_interface::MoveGroupInterface group(PLANNING_GROUP);
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  const robot_state::JointModelGroup* joint_model_group = group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  // aqui inicia o programa de fato
  ROS_INFO("INICIANDO PACOTES");
  // The package MoveItVisualTools
  namespace rvt = rviz_visual_tools;
  moveit_visual_tools::MoveItVisualTools visual_tools("base_link");
  visual_tools.deleteAllMarkers();
  // inicia o controle por botoes
  visual_tools.loadRemoteControl();
  // pacotes para a interface - text, cylinders, and spheres
  Eigen::Isometry3d text_pose = Eigen::Isometry3d::Identity();
  text_pose.translation().z() = 0.7;
  visual_tools.publishText(text_pose, "MoveGroupInterface Demo", rvt::WHITE, rvt::XLARGE);

  // (Optional) Create a publisher for visualizing plans in Rviz.
  ros::Publisher display_publisher = node_handle.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
  moveit_msgs::DisplayTrajectory display_trajectory;

  ROS_INFO("primeito movimento randomico");
  //seta o movimento
  // group.setRandomTarget();
  moveit::core::RobotStatePtr current_state = group.getCurrentState();
  std::vector<double> joint_group_positions;
  current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
  joint_group_positions[0] = 0.0;  // radians
  joint_group_positions[1] = 0.0;  // radians
  joint_group_positions[2] = 0.0;  // radians
  joint_group_positions[3] = 0.0;  // radians
  // joint_group_positions[4] = 0.0;  // radians
  // joint_group_positions[5] = 1.10;  // radians
  group.setJointValueTarget(joint_group_positions);
  //move o objeto
  group.move();
  // Batch publishing is used to reduce the number of messages being sent to RViz for large visualizations
  visual_tools.trigger();
  // prompt trava o programa esperando o proximo passo
  visual_tools.prompt("Press 'next' in the RvizVisualToolsGui window to continue");

  ROS_INFO("Reference frame: %s", group.getPlanningFrame().c_str());
  ROS_INFO("Reference frame: %s", group.getEndEffectorLink().c_str());

  // Planning to a Pose goal
  geometry_msgs::Pose target_pose1;
  tf2::Quaternion myQuaternion;
  myQuaternion.setRPY(3.14159, 0, 3.14159); // Create this quaternion from roll/pitch/yaw (in radians)
  myQuaternion.normalize();
  target_pose1.orientation = tf2::toMsg(myQuaternion);
  target_pose1.position.x = 0.6836502253486568;
  target_pose1.position.y = 0.6836502253486568;
  target_pose1.position.z = 0.5369882852527241;
  group.setPoseTarget(target_pose1);

  // planeja o movimento mas ainda nao executa
	moveit::planning_interface::MoveGroupInterface::Plan my_plan;
	moveit::planning_interface::MoveItErrorCode success = group.plan(my_plan);
  ROS_INFO("Visualizing plan 1 (pose goal) %s",success.val ? "":"FAILED");


  ROS_INFO_NAMED("tutorial", "Visualizing plan 1 as trajectory line");
  visual_tools.publishAxisLabeled(target_pose1, "pose1");
  visual_tools.publishText(text_pose, "Pose Goal", rvt::WHITE, rvt::XLARGE);
  visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
  visual_tools.trigger();
  group.execute(my_plan);
  visual_tools.prompt("iniciar movimento de juntas");
 

// aqui move o robo de fato.
	// group.move();
  // group.execute(my_plan);

  // mover braco atraves das juntas
  current_state = group.getCurrentState();
  //copia o estdado das juntas para a nova variavel
  current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
  // modifica o estado de uma das juntas
  joint_group_positions[0] = -1.0;  // radians
  group.setJointValueTarget(joint_group_positions);
  //print das juntas
  for (auto& valor : joint_group_positions)ROS_INFO("%f ",valor);

  success = (group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  ROS_INFO_NAMED("tutorial", "Visualizing plan 2 (joint space goal) %s", success ? "" : "FAILED");

  // Visualize the plan in RViz
  visual_tools.deleteAllMarkers();
  // visual_tools.publishAxisLabeled(target_pose1, "pose1");
  visual_tools.publishText(text_pose, "Joint Space Goal", rvt::WHITE, rvt::XLARGE);
  visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
  visual_tools.trigger();
  visual_tools.prompt("iniciar restricao de caminho");

  group.execute(my_plan);
  visual_tools.trigger();
  visual_tools.deleteAllMarkers();

  //===================================================
  visual_tools.prompt("fim");
  ros::shutdown();

 return 0;
}
