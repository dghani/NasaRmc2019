/****************************************************************************************
 * File:    monitoring_battery.cpp
 * Node:    monitoring_battery
 * 
 * Purpose: This is a subscriber that will listen to the current output while the arm is moving 
 *			to make sure that it does not exceed the capacity of the controllers
 *			To help tell the digging action server to change the digging queue becausethe current one
 *			is using to much power
 *
 *	TO_DO: not finished yet, might not use for this years compition 
 ****************************************************************************************/

#include "ros/ros.h"
#include <std_msgs/UInt16.h>



void batteryVoltageCallback(const std_msgs::UInt16& batteryVoltage) {
	//Roboteq controller sends voltage * 10 back i.e. if 150 is reported than it is 15 volts
        int batteryVolt = batteryVoltage.data / 10;
        //if battery voltage is below 30 than it needs to be charged
        if (batteryVolt < 37) {
        	ROS_ERROR("BATTERY LOW! CHARGE NOW! (%d volts)\n", batteryVolt);
        }
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "monitoring_battery");
	ros::NodeHandle n;
    
	ros::Subscriber batteryVoltageSubscriber = n.subscribe("/device8/get_qry_volts/v_bat", 
		5, batteryVoltageCallback, this);
	
	ros::spin();
	return 1;
		
}
