#include <iostream>
#include <ros/ros.h>

//class read_torque {

//public:
//	readTorqueValues(ros:NodeHandle &handler) : 
//		lowerArmSub{handler.subscribe("/device23/get_torque_actual_value",5,&read_torque::lowerArmCallback,this)}
//	{}
//
//
//
////class variables
//private:
//	ros::Subscriber lowerArmSub;
//
//
//
////callback functions
//	void lowerArmCallback() {
//		std::cout << "Lower arm callback"
//
//	}
//}

void lowerArmCallback() {
	std:cout << "Lower arm callback";
}



//Entry point
int main(int argc, char** argv) {
	ros::init(argc, argv, "read_torque");
	ros::NodeHandle nodeHandler;

	ros::Subscriber lowerArmSub = nodeHandler.subscribe("/device23/get_torque_actual_value",5, lowerArmCallback);

	//readTorqueValues(nodeHandler);

	ros::spin();
	

	std::cout << "Hello World";
	return 0;
}