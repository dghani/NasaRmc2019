#include <iostream>
#include <ros/ros.h>

class read_torque {

public:
	readTorqueValues(ross:NodeHandle &handler) : 
		lowerArmSub{handler.subscribe("/device23/get_torque_actual_value")}
	{}

//class variables
private:
	ros::Subscriber lowerArmSub;




//callback functions
	void lowerArmCallback() {
		std::cout << "Lower arm callback"

	}
};



//Entry point
int main(int argc, char** argv) {
	ros::init(argc, argv, "read_torque");
	ros::NodeHandle nodeHandler;

	readTorqueValues(nodeHandler);

	ros::Rate loop_rate(10);
	ros::spin();


	std::cout << "Hello World";
	return 0;
}