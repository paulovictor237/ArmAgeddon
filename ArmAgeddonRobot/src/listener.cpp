//+-------------------------------------------------------------------------------+
//             ╔══════════════════════════════════════════════════╗
//             ║  Copyright (C) 2020 Paulo Victor Duarte          ║
//             ╚══════════════════════════════════════════════════╝
//+-------------------------------------------------------------------------------+
#include <ros/package.h>
#include <iostream>
#include <fstream>
#include <iomanip>      // std::setprecision & std::setw
#include <algorithm>    // std::count
#include <math.h>       // M_PI
using namespace std;

void outputLine( double x,double y,double z,double rx,double ry,double rz )
{
   cout.precision(17);
   cout << std::fixed << std::setprecision(2);
   std::cout.precision(2);
   std::cout.setf(std::ios::fixed);
   cout << setprecision(3) << fixed;
   cout << "x: "  << x << setw( 8 ) 
        << "y: "  << y << setw( 8 )
        << "z: "  << z << setw( 8 )
        << "rx: " << rx << setw( 8 ) 
        << "ry: " << ry << setw( 8 )
        << "rz: " << rz  
        << endl;
} // end function outputLine

// ROS_INFO("%s\n", s.data.c_str());

int main()
{
    string RelativePath=ros::package::getPath("ArmAgeddonRobot");
    cout << RelativePath << endl;

    ifstream inClientFile(RelativePath + "/arquivos/test.txt");

    std::ifstream inFile(RelativePath + "/arquivos/test.txt"); 
    cout << "Numero de linhas: " << std::count(std::istreambuf_iterator<char>(inFile),std::istreambuf_iterator<char>(), '\n')+1 << endl;
    inFile.close();


    if(!inClientFile) {
      cout << "Cannot open input file.\n";
      return 1;
    }

    double x,y,z,rx,ry,rz;

    while ( inClientFile >> x >> y >> z >> rx >> ry >> rz ){
      outputLine(x,y,z,rx,ry,rz);
    }
    inClientFile.close();

    return 0;
}