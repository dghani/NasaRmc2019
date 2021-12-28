#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>
#include <chrono>

double previousAmps{0};
double previousTime = std::chrono::system_clock::now();
bool isScoopFull = false;


void lowerArmCallback(const std_msgs::Int16 torqueSensorCount) {
	std::cout << "Upper arm callback" << std::endl;

	double currentAmps = (torqueSensorCount.data / 1848.43);//Page 93 from the Ultra Motion Servo Cylinder manual, "Motor Current"
	double currentTime = std::chrono::system_clock::now();

	double torque_slope = (previousAmps - currentAmps) / (previousTime - currentTime);

	if (torque_slope < 0.3 && torque_slope > -0.3) {//within 0.3amps of zero amps (aka an unchanging torque)
		isScoopFull = true;
	}
	else {
		isScoopFull = false;
	}

	previousAmps = currentAmps;
	previousTime = currentTime;


}



//Entry point
int main(int argc, char** argv) {
	ros::init(argc, argv, "read_torque");
	ros::NodeHandle nodeHandler;

	ros::Subscriber lowerArmSub = nodeHandler.subscribe("/device45/get_torque_actual_value",5, lowerArmCallback);//upper arm
	ros::Publisher scoopFullPub = nodeHandler.advertise<std_msgs::Bool>("isScoopFull",50);



	ros::spin();
	

	std::cout << "Hello World";
	return 0;
}