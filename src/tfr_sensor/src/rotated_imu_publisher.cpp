#include <ros/ros.h>
#include <std_msgs/String.h>

/**
 * Subscribes to the Realsense sensor data and rotates the IMU data to follow
 * ROS format (X forward, Y left, Z up)
 * 
 * 
 * subscribed topics:
 *  realsense_camera_imu
 * published topics:
 *  rotated_imu_data
 * 
 * X Forward
 * Y Left 
 * Z Up
 * 
 **/
class RotatedIMUPublisher {
public:

private:

};

void printMsg(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("Here's the received subscribe info: [%s]", msg->data.c_str());
    int* arr = rotateData(0, 1, 2);
    std::cout << arr[0] << std::endl;
}

int* rotateData(int oldX, int oldY, int oldZ) {
    int arr[3];
    arr[0] = oldX;
    arr[1] = oldZ;
    arr[2] = oldY;
    return arr;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "rotated_imu_publisher");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("camera/gyro/imu_info", 1000, printMsg);
    ros::Publisher rotatedPublisher = n.advertise<std_msgs::String>("rotated_imu_data", 1000);

    ros::Rate loop_rate(10);
    int count = 0;

    // while ROS is running, try to publish a new message
    // new message should just contain a basic count for now
    while (ros::ok()) {
        std_msgs::String msg;

        std::stringstream ss;
        ss << "Publishing : " << count;
        msg.data = ss.str();

        ROS_INFO("%s", msg.data.c_str());


        rotatedPublisher.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }
    return 0;
}   