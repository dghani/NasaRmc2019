#ifndef ARM_MANIPULATOR_H
#define ARM_MANIPULATOR_H
#include <ros/ros.h>
#include <tfr_msgs/ArmMoveAction.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/UInt16.h>
#include <actionlib/server/simple_action_server.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <joints.h>
#include <urdf/model.h>
#include <actionlib/client/simple_action_client.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float64.h>

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
        void moveRightBinPosition(double rightBin);
        void moveLeftBinPosition(double leftBin);

        bool isArmTargetPositionReached(); // TODO

        bool turntable_target_position_reached = false;

        // Daniel/Matthew
        void scoopCallback(const std_msgs::Int32& scoop_position);
        void scoopIncremental();
        void scoopDecremental();

    private:
        ros::Publisher turntable_publisher;
        ros::Publisher lower_arm_publisher;
        ros::Publisher upper_arm_publisher;
        ros::Publisher scoop_publisher;
        ros::Publisher left_bin_publisher;
        ros::Publisher right_bin_publisher;
        ros::Subscriber turntable_statusword_subscriber;
        void updateTurntableTargetPosition(const std_msgs::UInt16 &value);

        // Daniel/Matthew
        ros::Subscriber scoop_subscriber;
        float scoopToleranceLimit;
        std_msgs::Bool scoopMoving;
        double double_scoop_position;
 };

#endif
