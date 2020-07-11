#ifndef ARM_MANIPULATOR_H
#define ARM_MANIPULATOR_H
#include <ros/ros.h>
#include <tfr_msgs/ArmMoveAction.h>
#include <std_msgs/Float64MultiArray.h>
#include <actionlib/server/simple_action_server.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <joints.h>
#include <urdf/model.h>
#include <actionlib/client/simple_action_client.h>
#include <sensor_msgs/JointState.h>

/**
 * Provides a simple method for moving the arm.
 * This is a regular ole' class, just instantiate it and call moveArm.
 * */
class ArmManipulator
{
    public:
        ArmManipulator(ros::NodeHandle &n, bool init_joints=true);
        ~ArmManipulator(){};
        ArmManipulator(const ArmManipulator&) = delete;
        ArmManipulator& operator=(const ArmManipulator&) = delete;
        ArmManipulator(ArmManipulator&&)=delete;
        ArmManipulator& operator=(ArmManipulator&&)=delete;

        void moveArm( const double& turntable, const double& lower_arm, const double& upper_arm, const double& scoop);

        void moveArmWithoutPlanningOrLimits(
            const double& turntable, const double& lower_arm, const double& upper_arm, const double& scoop);

        void moveTurntablePosition(double turntable);
        void moveLowerArmPosition(double lower_arm);
        void moveUpperArmPosition(double upper_arm);
        void moveScoopPosition(double scoop);

    private:
        ros::Publisher turntable_publisher;
        ros::Publisher lower_arm_publisher;
        ros::Publisher upper_arm_publisher;
        ros::Publisher scoop_publisher;
 };

#endif
