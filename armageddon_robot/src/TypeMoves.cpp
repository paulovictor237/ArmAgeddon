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


int main(int argc, char **argv)
{
//+-------------------------------------------------------------------------------+
  ROS_WARN("Iniciando Node");
  // iniciacao padrao para nodes
  ros::init(argc, argv, "TypeMoves");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();
  /* This sleep is ONLY to allow Rviz to come up */
  // sleep(2.0);
//+-------------------------------------------------------------------------------+
  ROS_WARN("Iniciando PLANNING_GROUP");
  // nome do grupo que sera movimentado
  static const std::string PLANNING_GROUP = "robot_arm";
  // linhas padrao para criar um grupo a ser movimentado
  moveit::planning_interface::MoveGroupInterface group(PLANNING_GROUP);
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  const robot_state::JointModelGroup* joint_model_group = group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);
  // aqui inicia o programa de fato
//+-------------------------------------------------------------------------------+
  ROS_WARN("Iniciando Visual_Tools");
  // The package MoveItVisualTools
  namespace rvt = rviz_visual_tools;
  moveit_visual_tools::MoveItVisualTools visual_tools("base_link");
  visual_tools.deleteAllMarkers();
  // inicia o controle por botoes
  visual_tools.loadRemoteControl();
  // pacotes para a interface - text, cylinders, and spheres
  Eigen::Isometry3d text_pose = Eigen::Isometry3d::Identity();
  text_pose.translation().z() = 1.7;

  // Scales
  // XXXXSMALL = 1, XXXSMALL = 2, XXSMALL = 3, XSMALL = 4,
  // SMALL = 5, MEDIUM = 6, LARGE = 7, XLARGE = 8,
  // XXLARGE = 9, XXXLARGE = 10, XXXXLARGE = 11

  // Colors 
  // BLACK 	 BROWN 	 BLUE 	 CYAN 	 GREY 	 DARK_GREY 	 
  // GREEN 	 LIME_GREEN 	 MAGENTA 	 ORANGE 	 PURPLE 	 
  // RED 	 PINK 	 WHITE 	 YELLOW 	 
  // TRANSLUCENT 	 TRANSLUCENT_LIGHT 	 TRANSLUCENT_DARK 	 
  // RAND 	 CLEAR 	 DEFAULT 

  visual_tools.publishText(text_pose, "Iniciando Visual_Tools", rvt::WHITE, rvt::XLARGE);
  // (Optional) Create a publisher for visualizing plans in Rviz.
  ros::Publisher display_publisher = node_handle.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
  moveit_msgs::DisplayTrajectory display_trajectory;
  visual_tools.trigger();
//+-------------------------------------------------------------------------------+
  // ROS_WARN("Movimento Randomico");
  // group.setRandomTarget();
  // group.move();
//+-------------------------------------------------------------------------------+
  ROS_WARN("Movimento GoHome");
  visual_tools.deleteAllMarkers();
  visual_tools.publishText(text_pose, "Movimento GoHome", rvt::ORANGE, rvt::XXXLARGE);
  visual_tools.trigger();

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
  group.move();
  // Batch publishing is used to reduce the number of messages being sent to RViz for large visualizations
  visual_tools.trigger();
  // prompt trava o programa esperando o proximo passo
  visual_tools.prompt("Presione 'next' no Rviz");
//+-------------------------------------------------------------------------------+
  ROS_WARN("Planejar PoseGoal");
  visual_tools.deleteAllMarkers(); 
  visual_tools.publishText(text_pose, "Planejar PoseGoal", rvt::ORANGE, rvt::XXXLARGE);
  visual_tools.trigger();

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
  ROS_INFO("Visualizing plan 1 (pose goal) %s",success.val ? "SUCCESS":"FAILED");

  // mostra o movimento no visual_tools
  ROS_INFO_NAMED("tutorial", "Visualizing plan 1 as trajectory line");
  visual_tools.publishAxisLabeled(target_pose1, "pose1");
  visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
  visual_tools.trigger();
  group.execute(my_plan);
  visual_tools.prompt("Presione 'next' no Rviz");
 
  // aqui move o robo de fato.
	// group.move();
  // group.execute(my_plan);
//+-------------------------------------------------------------------------------+
  ROS_WARN("Planejar Movimento Por Junta");
  visual_tools.deleteAllMarkers();
  visual_tools.publishText(text_pose, "Planejar Movimento Por Junta", rvt::ORANGE, rvt::XXXLARGE);
  visual_tools.trigger();
  // mover braco atraves das juntas
  current_state = group.getCurrentState();
  //copia o estdado das juntas para a nova variavel
  current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
  // modifica o estado de uma das juntas
  joint_group_positions[0] = -1.0;  // radians
  group.setJointValueTarget(joint_group_positions);

  success = (group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  ROS_INFO_NAMED("tutorial", "Visualizing plan 2 (joint space goal) %s", success ? "SUCCESS" : "FAILED");

  // Visualize the plan in RViz
  // visual_tools.publishAxisLabeled(target_pose1, "pose1");
  visual_tools.publishTrajectoryLine(my_plan.trajectory_, joint_model_group);
  visual_tools.trigger();
  visual_tools.prompt("Presione 'next' no Rviz");
//+-------------------------------------------------------------------------------+
  ROS_WARN("Executa Movimento Por Junta");
  visual_tools.publishText(text_pose, "Executa Movimento Por Junta", rvt::ORANGE, rvt::XXXLARGE);
  visual_tools.trigger();
  group.execute(my_plan);
  visual_tools.prompt("Presione 'next' no Rviz");
//+-------------------------------------------------------------------------------+
  ROS_WARN("Iniciar Plano Cartesiano");
  visual_tools.deleteAllMarkers();
  visual_tools.publishText(text_pose, "Iniciar Plano Cartesiano", rvt::ORANGE, rvt::XXXLARGE);
  visual_tools.trigger();
  target_pose1=group.getCurrentPose().pose;
  std::vector<geometry_msgs::Pose> waypoints;
  
  waypoints.push_back(target_pose1);
  target_pose1.position.z -= 0.2;
  waypoints.push_back(target_pose1);  // down
  target_pose1.position.y -= 0.2;
  waypoints.push_back(target_pose1);  // right
  target_pose1.position.z += 0.2;
  target_pose1.position.y += 0.2;
  target_pose1.position.x -= 0.2;
  waypoints.push_back(target_pose1);  // up and left
  target_pose1.position.z -= 0.2;
  target_pose1.position.y -= 0.2;
  target_pose1.position.x -= 0.2;
  waypoints.push_back(target_pose1);  // up and left
  target_pose1.position.z += 0.2;
  target_pose1.position.y += 0.2;
  target_pose1.position.x -= 0.2;
  waypoints.push_back(target_pose1);  // up and left
  target_pose1.position.z += 0.2;
  target_pose1.position.y -= 0.2;
  target_pose1.position.x += 0.2;
  waypoints.push_back(target_pose1);  // up and left
  target_pose1.position.z -= 0.2;
  target_pose1.position.y -= 0.2;
  waypoints.push_back(target_pose1);  // up and left
  target_pose1.position.y -= 0.2;
  target_pose1.position.x -= 0.2;
  target_pose1.position.z += 0.2;
  waypoints.push_back(target_pose1);  // up and left

  moveit_msgs::RobotTrajectory trajectory;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;
  double fraction = group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
  ROS_INFO_NAMED("tutorial", "Visualizing plan 4 (Cartesian path) (%.2f%% acheived)", fraction * 100.0);

  // Visualize the plan in RViz
  visual_tools.publishPath(waypoints, rvt::LIME_GREEN, rvt::SMALL);
  for (std::size_t i = 0; i < waypoints.size(); ++i)
  visual_tools.publishAxisLabeled(waypoints[i], "Point: " + std::to_string(i), rvt::SMALL);
  visual_tools.trigger();
  visual_tools.prompt("Presione 'next' no Rviz");
//+-------------------------------------------------------------------------------+
  ROS_WARN("Executa Plano Cartesiano");
  // visual_tools.deleteAllMarkers();
  visual_tools.publishText(text_pose, "Executa Plano Cartesiano", rvt::ORANGE, rvt::XXXLARGE);
  visual_tools.trigger();
  group.execute(trajectory);
//+-------------------------------------------------------------------------------+
  ROS_WARN("FIM");
  ros::shutdown();

 return 0;
}
