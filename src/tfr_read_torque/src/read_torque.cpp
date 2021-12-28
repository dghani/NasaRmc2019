#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>
#include <chrono>

class ReadTorque {

public:
    ReadTorque(ros::NodeHandle nodeHandler) {
        upperArmSub = nodeHandler.subscribe("/device45/get_torque_actual_value", 5, &ReadTorque::upperArmCallback, this);//upper arm

        scoopFullPub = nodeHandler.advertise<std_msgs::Bool>("isScoopFull", 50);

        startupTime = std::chrono::system_clock::now();
        startTimeInSeconds = std::chrono::duration<double>(startupTime.time_since_epoch());
        previousTime = startTimeInSeconds.count();
    }

private:
    ros::Subscriber upperArmSub;
    ros::Publisher scoopFullPub;

    std::chrono::system_clock::time_point startupTime{};
    std::chrono::duration<double> startTimeInSeconds{};
    long previousTime{};

    double previousAmps{};

    std_msgs::Bool isScoopFull{};


    void upperArmCallback(const std_msgs::Int16 torqueSensorCount) {
        std::cout << "Upper arm callback" << std::endl;

        double currentAmps = (torqueSensorCount.data / 1848.43);//Page 93 from the Ultra Motion Servo Cylinder manual, "Motor Current"


        auto time = std::chrono::system_clock::now();
        auto timeInSeconds = std::chrono::duration<double>(time.time_since_epoch());
        long currentTime = timeInSeconds.count();

        double torque_slope = (previousAmps - currentAmps) / (previousTime - currentTime);

        std::cout
            << "\nPreviousAmps: " << previousAmps
            << "\nCurrent Amps: " << currentAmps
            << "\nPrevious Time: " << previousTime
            << "\nCurrent Time: " << currentTime
            << "\nTorque Slope: " << torque_slope << std::endl;

        if (torque_slope < 0.3 && torque_slope > -0.3) {//within 0.3amps of zero amps (aka an unchanging torque)
            isScoopFull.data = true;
        }
        else {
            isScoopFull.data = false;
        }

        previousAmps = currentAmps;
        previousTime = currentTime;

        scoopFullPub.publish(isScoopFull);
    }


};





//Entry point
int main(int argc, char** argv) {
    ros::init(argc, argv, "read_torque");
    ros::NodeHandle nodeHandler;


    ReadTorque testClass(nodeHandler);



    ros::spin();

    return 0;
}