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
  //  cout.precision(17);
  //  std::cout.precision(2);
  //  std::cout.setf(std::ios::fixed);
  //  cout << setprecision(3) << fixed;
  cout << std::fixed << std::setprecision(2);
  cout << "outputLine :"
       << "x: "  << x << setw( 8 ) 
       << "y: "  << y << setw( 8 )
       << "z: "  << z << setw( 8 )
       << "rx: " << rx << setw( 8 ) 
       << "ry: " << ry << setw( 8 )
       << "rz: " << rz  
       << endl;
} // end function outputLine

int main()
{
//+-------------------------------------------------------------------------------+
  // Obter o endereco relativo do pacote ArmAgeddonRobot
  string RelativePath=ros::package::getPath("ArmAgeddonRobot");
  cout << RelativePath << endl;
//+-------------------------------------------------------------------------------+
  // Informar o numero de linhas do arquivo 
  std::ifstream inFile(RelativePath + "/arquivos/test2.txt"); 
  if(!inFile) {
    cout << "Cannot open input file.\n";
    return 1;
  }
  cout << "Numero de linhas: " << std::count(std::istreambuf_iterator<char>(inFile),std::istreambuf_iterator<char>(), '\n')+1 << endl;
  inFile.close();
//+-------------------------------------------------------------------------------+
  // ler o arquivo 
  ifstream inClientFile(RelativePath + "/arquivos/test2.txt");
  double x,y,z,rx,ry,rz;
  string descartar;
  while (!inClientFile.eof()){
    inClientFile >> descartar;
    inClientFile >> x ;
    inClientFile >> descartar;
    inClientFile >> y ;
    inClientFile >> descartar;
    inClientFile >> z ;
    inClientFile >> descartar;
    inClientFile >> rx;
    inClientFile >> descartar;
    inClientFile >> ry;
    inClientFile >> descartar;
    inClientFile >> rz;
    outputLine(x,y,z,rx,ry,rz);
  }
  inClientFile.close();
  
  geometry_msgs::Pose target_pose;
  std::vector<geometry_msgs::Pose> waypoints;
  tf2::Quaternion rpy2quaternion;


  rpy2quaternion.setRPY(3.14159, 0, 3.14159);
  rpy2quaternion.normalize();
  target_pose.orientation = tf2::toMsg(rpy2quaternion);
  target_pose.position.x = 0.6836502253486568;
  target_pose.position.y = 0.6836502253486568;
  target_pose.position.z = 0.5369882852527241;
  
  waypoints.push_back(target_pose);
  for (auto &valor : waypoints)cout << valor;


  return 0;
}