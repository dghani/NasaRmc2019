#include <servo_cylinder.h>

// canNodeId: the CAN node ID for the actuator, defined in create_ros_topics_for_can_nodes.cpp.
ServoCylinder::ServoCylinder(ros::NodeHandle& n, int canNodeId)
{
	// Set up the topics to publish/subscribe to.
	std::string nodeIdString = std::to_string(canNodeId);
	
	// publishers
	std::string publisherTopic = "/device" + nodeIdString + "/set_joint_state";
	servo_cylinder_publisher = n.advertise<sensor_msgs::JointState>(publisherTopic, 5);
	
	std::string position_window_publisher_topic = "/device" + nodeIdString + "/position_window";
	position_window_publisher = n.advertise<sensor_msgs::JointState>(position_window_publisher_topic, 5);
	
	std::string position_window_time_publisher_topic = "/device" + nodeIdString + "/position_window_time";
	position_window_time_publisher = n.advertise<sensor_msgs::JointState>(position_window_time_publisher_topic, 5);
	
	// subscriber
	std::string statuswordTopic = "/device" + nodeIdString + "/statusword";
	servo_cylinder_statusword_subscriber = n.subscribe(statuswordTopic, 5, &ServoCylinder::updateStatusword, this);
	
	
	// ---- Actuator Configuration ----
	// Configure the actuator so that it will return true for isTargetPositionReached() when the actuator is within 1/8th inch of the target position for at least 1 millisecond.
	setPositionWindow(1024, 1); // 1024 counts = 0.125 inches.
	
}

// This only gets updated at the minimum of
// - the rate that tfr_can node publishes the servo cylinder statusword message
// - the rate of the node which holds this ServoCylinder instance.
// i.e. if your node is running at 10 Hz, then this method definitely won't get updated faster than 10 Hz.
void ServoCylinder::updateStatusword(const std_msgs::UInt16 &value)
{
	statusword = value.data;
}

bool ServoCylinder::isTargetPositionReached()
{
    const uint16_t BIT10 = (1 << 10); // 0b0000010000000000

    uint16_t target_position_reached_bit = (statusword & BIT10); // mask out just bit #10 of the statusword. This bit tells is 1 if the motor has reached the last target position. (The motor may still be moving, but it is near the target position.)

    if (target_position_reached_bit != 0)
    {
        return true;
    }
    else
    {
		return false;
    }
}

void ServoCylinder::movePosition(double position)
{
    sensor_msgs::JointState state;

    state.header.stamp = ros::Time::now();
    state.position.push_back(position);
    
    servo_cylinder_publisher.publish(state);
}

// Change the actuator's definition of having reached its target position.
// After the actuator is told what position to go to, isTargetPositionReached() will return true once the actuator's position has remained within encoder_counts of the target position for some number of milliseconds.
// e.g.
//  setPositionWindow(1000, 10);
//  ^ This would mean "The actuator has reached its position once it has stayed within 1000 encoder counts of the target position for 10 milliseconds."
// Note: On the Servo Cylinder actuators: 1024 encoder counts = 0.125 inches.
void ServoCylinder::setPositionWindow(uint32_t encoder_counts, uint16_t milliseconds)
{
	// position window is a U32
	// position window time is a U16
	std_msgs::UInt32 position_window;
	std_msgs::UInt16 position_window_time;
	
	position_window.data = encoder_counts;
	position_window_time.data = milliseconds;
	
	// Send the messages
	position_window_publisher.publish(position_window);
	position_window_time_publisher.publish(position_window_time);
}
