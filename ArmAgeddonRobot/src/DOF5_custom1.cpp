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

#include <moveit/move_group_interface/move_group_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

sensor_msgs::JointState asd;


int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle;  
  ros::AsyncSpinner spinner(1);
  spinner.start();


  /* This sleep is ONLY to allow Rviz to come up */
  sleep(2.0);
  
  // BEGIN_TUTORIAL
  // 
  // Setup
  // ^^^^^
  // 
  // The :move_group_interface:`MoveGroup` class can be easily 
  // setup using just the name
  // of the group you would like to control and plan for.
  moveit::planning_interface::MoveGroupInterface group("robot_arm");

  // We will use the :planning_scene_interface:`PlanningSceneInterface`
  // class to deal directly with the world.
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;  

  // (Optional) Create a publisher for visualizing plans in Rviz.
  ros::Publisher display_publisher = node_handle.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
  moveit_msgs::DisplayTrajectory display_trajectory;

  // Getting Basic Information
  // ^^^^^^^^^^^^^^^^^^^^^^^^^
  //	
  // We can print the name of the reference frame for this robot.
  ROS_INFO("Reference frame: %s", group.getPlanningFrame().c_str());
  
  // We can also print the name of the end-effector link for this group.
  ROS_INFO("Reference frame: %s", group.getEndEffectorLink().c_str());

  // Planning to a Pose goal
  // ^^^^^^^^^^^^^^^^^^^^^^^
  // We can plan a motion for this group to a desired pose for the 
  // end-effector.
  geometry_msgs::Pose target_pose1;
  target_pose1.orientation.x= -0.37485986948;
  target_pose1.orientation.y= -0.121226333082;
  target_pose1.orientation.z= -0.489020526409;
  target_pose1.orientation.w= 0.778230786324;

  target_pose1.position.x= 0.0528235733509;
  target_pose1.position.y= 0.184045732021;
  target_pose1.position.z= 0.292120486498;
  group.setPoseTarget(target_pose1);

  // Now, we call the planner to compute the plan
  // and visualize it.
  // Note that we are just planning, not asking move_group 
  // to actually move the robot.
	moveit::planning_interface::MoveGroupInterface::Plan my_plan;
	moveit::planning_interface::MoveItErrorCode success = group.plan(my_plan); 
  ROS_INFO("Visualizing plan 1 (pose goal) %s",success.val ? "":"FAILED");    

  // Sleep to give Rviz time to visualize the plan. 
	// group.move();
  group.execute(my_plan);	
	// END_TUTORIAL

  // linhas padrao para criar um grupo a ser movimentado
  moveit::planning_interface::MoveGroupInterface gripper("robot_gripper");

  std::vector<std::string> nomes;
  nomes = gripper.getJointNames();
  for (auto &valor : nomes) ROS_INFO("JointNames: %s ", valor.c_str());
  nomes = gripper.getLinkNames();
  for (auto &valor : nomes) ROS_INFO("Links: %s ", valor.c_str());

  const robot_state::JointModelGroup *joint_model_group = gripper.getCurrentState()->getJointModelGroup("robot_gripper");
  moveit::core::RobotStatePtr current_state = gripper.getCurrentState();
  std::vector<double> joint_group_positions;
  current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
  // joint_group_positions[0] = 0.0; // aberto
  gripper.setJointValueTarget(joint_group_positions);
  gripper.move();
  
  sleep(2.0);
  // joint_group_positions[0] = 0.8; // aberto
  gripper.setJointValueTarget(joint_group_positions);
  // gripper.setJointValueTarget("finger_joint1",0.03);
  // gripper.setMaxAccelerationScalingFactor(0);
  // gripper.setMaxVelocityScalingFactor(0);
  // gripper.setPlanningTime(1);
  gripper.move();

  sleep(2.0);
  // joint_group_positions[0] = 0.0; // aberto
  gripper.setJointValueTarget(joint_group_positions);
  gripper.move();

  sleep(2.0);
  // joint_group_positions[0] = 0.8; // aberto
  gripper.setJointValueTarget(joint_group_positions);
  gripper.move();

  ros::shutdown();  

 return 0;
}
