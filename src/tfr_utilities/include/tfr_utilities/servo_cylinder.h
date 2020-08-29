#ifndef SERVO_CYLINDER_H
#define SERVO_CYLINDER_H

#include <ros/ros.h>
#include <sensor_msgs/JointState.h> // position publisher
#include <std_msgs/UInt16.h> // statusword subscriber, position_window_time
#include <std_msgs/UInt32.h> // position_window

class ServoCylinder
{
public:
	
	ServoCylinder(ros::NodeHandle&, int);
	
	void movePosition(double position);
	bool isTargetPositionReached();

private:

	void setPositionWindow(uint32_t encoder_counts, uint16_t milliseconds);
	void updateStatusword(const std_msgs::UInt16 &value);
	
	uint16_t statusword; // The "statusword" is part of CANopen's 402 profile. It tells you about the status of the motor. It's called a "word" because it's 16 bits.
	
	ros::Publisher  servo_cylinder_publisher;
	ros::Publisher  position_window_publisher;
	ros::Publisher  position_window_time_publisher;
	ros::Subscriber servo_cylinder_statusword_subscriber;
	
};

#endif
