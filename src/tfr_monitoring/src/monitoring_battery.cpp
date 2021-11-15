/****************************************************************************************
 * File:    monitoring_battery.cpp
 * Node:    monitoring_battery
 *
 * Purpose: This is a subscriber that will listen to the voltage output of the battery. 
 *	    When the battery is outputting 37 volts or less, it will print a warning 
 *	    message to terminal.
 *
 ****************************************************************************************/

#include "ros/ros.h"
#include <std_msgs/UInt16.h>


void batteryVoltageCallback(const std_msgs::UInt16& batteryVoltage) {
	//Roboteq controller sends voltage * 10 back i.e. if 150 is reported than it is 15 volts.
  float batteryVolt = batteryVoltage.data / 10;
  if (batteryVolt <= 36.5) {
    ROS_ERROR("BATTERY LOW! CHARGE NOW! (%f volts)\n", batteryVolt);
  }
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "monitoring_battery");
	ros::NodeHandle n;
	ros::Subscriber batteryVoltageSubscriber = n.subscribe("/device8/get_qry_volts/v_bat",
		5, batteryVoltageCallback);
	ros::spin();
	return 1;
}
