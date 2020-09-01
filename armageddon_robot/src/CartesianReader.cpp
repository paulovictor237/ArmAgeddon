//+-------------------------------------------------------------------------------+
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//+-------------------------------------------------------------------------------+
// BIBLIOTECAS ROS
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/LinearMath/Quaternion.h>

// BIBLIOTECAS C++
#include <iostream>
#include <fstream>
#include <iomanip>      // std::setprecision & std::setw
#include <algorithm>    // std::count
#include <math.h>       // M_PI
// #include <angles/angles.h> //angles::from_degrees(rx);
using namespace std;

void ExtractPoints(std::ifstream &PositionsFile ,std::vector<geometry_msgs::Pose> &waypoints){
  geometry_msgs::Pose target_pose;
  tf2::Quaternion rpy2quaternion;

  double x,y,z,rx,ry,rz;
  string descartar;
  while (!PositionsFile.eof()){
    PositionsFile >> descartar >> x ;
    PositionsFile >> descartar >> y ;
    PositionsFile >> descartar >> z ;
    PositionsFile >> descartar >> rx;
    PositionsFile >> descartar >> ry;
    PositionsFile >> descartar >> rz;
    PositionsFile >> descartar;
    // outputLine(x,y,z,rx,ry,rz);

    // CONVERTER GRAUS EM RADIANOS
    // (Degrees to Radians)
    rx = rx*(M_PI/180.0);
    ry = ry*(M_PI/180.0);
    rz = rz*(M_PI/180.0);
    // Outra forma de converter graus em radianos
    // static double angles::from_degrees	(	double 	degrees	)	
    // rx = angles::from_degrees(rx);
    // ry = angles::from_degrees(ry);
    // rz = angles::from_degrees(rz);

    rpy2quaternion.setRPY(rx,ry,rz);
    rpy2quaternion.normalize();
    target_pose.orientation = tf2::toMsg(rpy2quaternion);
    target_pose.position.x = x;
    target_pose.position.y = y;
    target_pose.position.z = z;
    waypoints.push_back(target_pose);
  }
  return;
}


int main(int argc, char **argv)
{
//+-------------------------------------------------------------------------------+
  ROS_WARN("Iniciando Node");
  // iniciacao padrao para nodes
  ros::init(argc, argv, "CartesianReader");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();
  /* This sleep is ONLY to allow Rviz to come up */
  // sleep(2.0);
//+-------------------------------------------------------------------------------+
  // Obter o endereco relativo do pacote armageddon_robot
  string RelativePath=ros::package::getPath("armageddon_robot");
  cout << "Caminho Relativo: " << RelativePath << endl;
//+-------------------------------------------------------------------------------+
  // Informar o numero de linhas do arquivo 
  std::ifstream inFile(RelativePath + "/arquivos/positions.md"); 
  if(!inFile) {
    cout << "Arquivo não foi encontrado.\n";
    ros::shutdown();
    return 0;
  }

  int contador=0;
  char leitura;

  while (!inFile.eof()){
    leitura = inFile.get();
    if(leitura==','){
      ROS_FATAL("Padrao numerico errado");
      ROS_FATAL("Nao use ',' para separar casas decimais !!");
      inFile.close();
      ros::Duration(0.5).sleep();  // Sleep por meio segundo
      ros::shutdown();
      return 0;
    }
    if(leitura=='\n') contador++;
  }
  cout << "Numero de linhas do arquivo: " << contador+1 << endl;

  inFile.close();
//+-------------------------------------------------------------------------------+
  // abre o arquivo 
  ifstream PositionsFile(RelativePath + "/arquivos/positions.md");
//+-------------------------------------------------------------------------------+
  // faz a leitura do cabecalho  
  double MaxVelocity;
  double MaxAcceleration;
  double PlanningTime ;
  double EndEffectorStep;
  double JumpThreshold;
  bool   AvoidCollisions;
  
  string descartar;
  char line[256];
  for (int i = 0; i < 3; i++)PositionsFile.getline(line,256);
  PositionsFile >> descartar >> MaxVelocity;
  PositionsFile >> descartar >> MaxAcceleration;
  PositionsFile >> descartar >> PlanningTime;
  PositionsFile >> descartar >> EndEffectorStep;
  PositionsFile >> descartar >> JumpThreshold;
  PositionsFile >> descartar >> AvoidCollisions;
  for (int i = 0; i < 5; i++)PositionsFile.getline(line,256);
  
  cout << "MaxVelocity: " << MaxVelocity << endl;
  cout << "MaxAcceleration: " << MaxAcceleration << endl;
  cout << "PlanningTime: " << PlanningTime << endl;
  cout << "EndEffectorStep: " << EndEffectorStep << endl;
  cout << "JumpThreshold: " << JumpThreshold << endl;
  cout << "AvoidCollisions: " << AvoidCollisions << endl;
  // cout << descartar << endl;
//+-------------------------------------------------------------------------------+
  // faz a leitura dos waypoints
  std::vector<geometry_msgs::Pose> waypoints;

  ExtractPoints(PositionsFile,waypoints);
  
  PositionsFile.close();

  // for (auto &valor : waypoints)cout << valor;
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
  ROS_WARN("Iniciar Plano Cartesiano");
  visual_tools.deleteAllMarkers();
  visual_tools.publishText(text_pose, "Iniciar Plano Cartesiano", rvt::ORANGE, rvt::XXXLARGE);
  visual_tools.trigger();

  waypoints.insert(waypoints.begin(),group.getCurrentPose().pose);
  // ===================== configuracoes =====================
  // Velocidade e Aceleração máxima
  // Para realizar caminhos cartesianos é recomendado usar 5% (0.05)
  // O valor padrão é 10% (0.10)
  // Defina seu valor padrão no arquivo joint_limits.yaml 
  group.setMaxVelocityScalingFactor(MaxVelocity); 
  group.setMaxAccelerationScalingFactor(MaxAcceleration);
  // O planejamento com restrições pode ser lento porque cada amostra deve
  // chamar um solucionador de cinemática inversa. 
  // O valor padrão é 5 segundos 
  // É comum aumentar esse tempo quando se está calculando uma trajetória de multiplos pontos
  // Para garantir que o planejador tenha tempo suficiente para ter sucesso aumente para 10s
  group.setPlanningTime(PlanningTime);
  // eef_step tamanho de passo máximo em metros entre o efetor final e os pontos da trajetória
  const double eef_step = EndEffectorStep;
  // Jump_threshold  - desativa-lo pode evitar pulos no calculo da cinematica inversa
  const double jump_threshold = JumpThreshold;
  // avoid_collisions - colisões são evitadas se for definido como true.
  // Entretanto, se as colisões não podem ser evitadas, a função falha. 
  bool avoid_collisions=AvoidCollisions;
  // =========================================================
  moveit_msgs::RobotTrajectory trajectory;
  // Cartesian path funciona como consecutivos pontos da funcao setPoseReferenceFrame()
  // Retorne um valor entre 0.0 e 1.0 indicando a fração do caminho alcançado
  // Retorne -1,0 em caso de erro. 
  double fraction = group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory,avoid_collisions);
  ROS_INFO("fracao do caminho alcancado: (%.2f%%)", fraction * 100.0);

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
