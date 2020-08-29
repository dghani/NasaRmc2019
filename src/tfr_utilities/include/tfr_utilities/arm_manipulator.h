#ifndef ARM_MANIPULATOR_H
#define ARM_MANIPULATOR_H
#include <ros/ros.h>
#include <tfr_msgs/ArmMoveAction.h>
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/Int32.h>
#include <actionlib/server/simple_action_server.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <joints.h>
#include <urdf/model.h>
#include <actionlib/client/simple_action_client.h>
#include <sensor_msgs/JointState.h>
#include <servo_cylinder.h>

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

        // These ServoCylinder instances are public, so that users of ArmManipulator can call the methods of them to change each joint individually.
        // e.g. You can do something like:
        //
        // ArmManipulator arm_manipulator{n};
        // arm_manipulator.lower_arm.movePosition(2.5);
        //
        ServoCylinder lower_arm;
        ServoCylinder upper_arm;
        ServoCylinder scoop;
        ServoCylinder left_bin;
        ServoCylinder right_bin;

        bool isArmTargetPositionReached(); 

        bool isTurntablePositionReached();
        void moveTurntablePosition(double turntable);

    private:
        ros::Publisher turntable_publisher;
        ros::Subscriber turntable_target_position_subscriber;
        ros::Subscriber turntable_position_actual_value_subscriber;
        void updateTurntableTargetPosition(const std_msgs::Int32 &value);
        void updateTurntablePositionActualValue(const std_msgs::Int32 &value);
        int32_t turntable_target_position;
        int32_t turntable_position_actual_value;
 };

#endif
