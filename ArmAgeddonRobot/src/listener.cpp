#include <ros/package.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// ROS_INFO("%s\n", s.data.c_str());

int main()
{
    int sum = 0;
    int x;

    string string_teste=ros::package::getPath("ArmAgeddonRobot");
    cout << string_teste << endl;

    ifstream inFile;

    inFile.open(string_teste + "/src/test.txt");

    if (!inFile)
    {
        cout << "Unable to open file\n";
        exit(1); // terminate with error
    }

    while (inFile >> x)
    {
        sum = sum + x;
    }

    inFile.close();
    cout << "Sum = " << sum << endl;
    return 0;
}