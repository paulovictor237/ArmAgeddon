#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float64.h>
#include <sensor_msgs/JointState.h>

#include <string>
#include <sstream>
#include <vector>

#define juntas_num 6

class joint{
public:
    joint(){
        last_position=0.0;
        first_iteration=true;
    }
    ~joint(){}
public:
    float last_position;
    bool first_iteration;
};


serial::Serial ser;

std::vector<joint> joints_select;

std::string serial_message;

// subscriber callback
void write_callback(const sensor_msgs::JointState::ConstPtr& msg){
    for(int i=0;i<juntas_num;i++){
        float rad_position = msg->position[i];
        float var_rad = 0.0;
        float var_steps = 0;
        std::ostringstream stm;
        // a primeira iteração serve para modificar o valor de last_position e evitar problemas com o 0.0
        if (joints_select[i].first_iteration) {
            joints_select[i].last_position = rad_position;
            joints_select[i].first_iteration = false;
        } else {
            // manda sinal ao motor se alterou a posição
            if (rad_position != joints_select[i].last_position) {
                // converte de rad para passos considerando 0.01 deg/step ou 0.0001745329 rad/step
                var_rad = rad_position - joints_select[i].last_position;
                var_steps = int(var_rad/0.0001745329);
                // cria a mensagem a ser mandada pro motor via serial
                stm.str("");
                stm << (i+1) << "DI" << var_steps << "\r";
                serial_message = stm.str();
                ROS_INFO_STREAM("Writing to serial port: " << serial_message);
                // envia a mensagem
                ser.write(serial_message);
                ros::Duration(0.01).sleep();
                stm.str("");
                stm << (i+1) << "FL\r";
                serial_message = stm.str();
                ROS_INFO_STREAM("Writing to serial port: " << serial_message);
                ROS_INFO_STREAM("----------------------------------");
                // envia a mensagem
                ser.write(serial_message);
                ros::Duration(0.01).sleep();
                joints_select[i].last_position = rad_position;
            }
        }
    }  
}


int main (int argc, char** argv){
    joints_select.resize(juntas_num);
    //inicia o programa
    ros::init(argc, argv, "joint_interface_node");
    ros::NodeHandle nh;

    // receives robotJointTrajectory from internal controller and sends to servo driver
    ros::Subscriber robot_joint_trajectory_sub = nh.subscribe("joint_states", 1, write_callback);

    // receives robotJointState from servo driver and publishes into a topic
    ros::Publisher joint_current_state_pub = nh.advertise<std_msgs::String>("joint_current_state", 1);

    // ------------------------------------------------------------------------------------------------------------------------
    // initialize serial port to servo driver

    
    try
    {
        ser.setPort("/dev/ttyUSB0");  // or ttyUSB0, remember to change this
        ser.setBaudrate(9600);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port: " << e.what());
        return -1;
    }

    if(ser.isOpen()){
        ROS_INFO_STREAM("Serial Port initialized");
    }else{
        return -1;
    }
    
	ros::Duration(1).sleep();
    // ------------------------------------------------------------------------------------------------------------------------
    // set initial servo/stepper configurations via serial
    //ser.write("MR13");  // microstep resolution: 36000 steps/rev -> 0.01 deg/step

	ser.write("HR\r");
	ros::Duration(0.1).sleep();
	ser.write("SK\r");
	ros::Duration(0.1).sleep();

	ser.write("MV\r");
	ros::Duration(0.01).sleep();
	ser.write("RLs\r");
	ros::Duration(0.01).sleep();
	ser.write("EG\r");
	ros::Duration(0.01).sleep();
	ser.write("IF\r");
	ros::Duration(0.01).sleep();
	ser.write("PR\r");
	ros::Duration(0.01).sleep();
	ser.write("PR5\r");
	ros::Duration(0.01).sleep();
	ser.write("PM\r");
	ros::Duration(0.01).sleep();
	ser.write("RV\r");
	ros::Duration(0.01).sleep();
	ser.write("SR-1\r");
	ros::Duration(0.01).sleep();
	ser.write("SV\r");
	ros::Duration(0.01).sleep();
	ser.write("SR100\r");
	ros::Duration(0.01).sleep();
	ser.write("SV\r");
	ros::Duration(0.01).sleep();
	
    
    ros::Rate loop_rate(10);  // freq in Hertz
    while(ros::ok()){

        // TODO Publisher

        // ser.write("IP");
        ros::spinOnce();
        // aqui podemos obter os valores do estado do motor para publicar num novo tópico
        // no momento estou publicando apenas o valor enviado ao driver pela serial
        std_msgs::String message;
        message.data = serial_message;
        joint_current_state_pub.publish(message);
      
        loop_rate.sleep();
    }
}

