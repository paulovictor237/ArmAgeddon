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

#include <ros/package.h>
#include <ros/console.h>
// BIBLIOTECAS C++
#include <iostream>
#include <fstream>
#include <iomanip>      // std::setprecision & std::setw
#include <algorithm>    // std::count
#include <math.h>       // M_PI
using namespace std;

void outputLine( double x,double y,double z,double rx,double ry,double rz )
{
  cout << std::fixed << std::setprecision(2);
  cout << "FileLine>> ";
  cout << "x: "  << x  << setw( 8 );
  cout << "y: "  << y  << setw( 8 );
  cout << "z: "  << z  << setw( 8 );
  cout << "rx: " << rx << setw( 8 ); 
  cout << "ry: " << ry << setw( 8 );
  cout << "rz: " << rz << endl;
  return;
}


void ExtractPoints(std::ifstream &inClientFile ,std::vector<geometry_msgs::Pose> &waypoints){
  geometry_msgs::Pose target_pose;
  tf2::Quaternion rpy2quaternion;

  double x,y,z,rx,ry,rz;
  string descartar;
  while (!inClientFile.eof()){
    inClientFile >> descartar >> x ;
    inClientFile >> descartar >> y ;
    inClientFile >> descartar >> z ;
    inClientFile >> descartar >> rx;
    inClientFile >> descartar >> ry;
    inClientFile >> descartar >> rz;
    outputLine(x,y,z,rx,ry,rz);

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
  // Obter o endereco relativo do pacote armageddon_robot
  string RelativePath=ros::package::getPath("armageddon_robot");
  cout << "Caminho Relativo: " << RelativePath << endl;
//+-------------------------------------------------------------------------------+
  // Informar o numero de linhas do arquivo 
  std::ifstream inFile(RelativePath + "/arquivos/positions.txt"); 
  if(!inFile) {
    cout << "Arquivo não foi encontrado.\n";
    return 0;
  }
  cout << "Numero de linhas do arquivo: " << std::count(std::istreambuf_iterator<char>(inFile),std::istreambuf_iterator<char>(), '\n')+1 << endl;
  inFile.close();
//+-------------------------------------------------------------------------------+
  // abre o arquivo 
  ifstream inClientFile(RelativePath + "/arquivos/positions.txt");
//+-------------------------------------------------------------------------------+
  // faz a leitura do cabecalho  
  double MaxVelocity;
  double MaxAcceleration;
  double PlanningTime ;
  double EndEffectorStep;
  double JumpThreshold;
  bool   AvoidCollisions;
  
  string descartar;
  inClientFile >> descartar;
  inClientFile >> descartar >> MaxVelocity;
  inClientFile >> descartar >> MaxAcceleration;
  inClientFile >> descartar >> PlanningTime;
  inClientFile >> descartar >> EndEffectorStep;
  inClientFile >> descartar >> JumpThreshold;
  inClientFile >> descartar >> AvoidCollisions;
  inClientFile >> descartar;
  
  cout << descartar << endl;
  cout << "MaxVelocity: " << MaxVelocity << endl;
  cout << "MaxAcceleration: " << MaxAcceleration << endl;
  cout << "PlanningTime: " << PlanningTime << endl;
  cout << "EndEffectorStep: " << EndEffectorStep << endl;
  cout << "JumpThreshold: " << JumpThreshold << endl;
  cout << "AvoidCollisions: " << AvoidCollisions << endl;
  cout << descartar << endl;
//+-------------------------------------------------------------------------------+
  // faz a leitura dos waypoints
  std::vector<geometry_msgs::Pose> waypoints;

  ExtractPoints(inClientFile,waypoints);
  
  inClientFile.close();

  // for (auto &valor : waypoints)cout << valor;
//+-------------------------------------------------------------------------------+
  ROS_WARN("FIM");
  return 0;
}