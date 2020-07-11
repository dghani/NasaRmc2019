#include <arm_manipulator.h>

ArmManipulator::ArmManipulator(ros::NodeHandle &n, bool init_joints):
            turntable_publisher{n.advertise<sensor_msgs::JointState>("/device1/set_joint_state", 5)},
            lower_arm_publisher{n.advertise<sensor_msgs::JointState>("/device23/set_joint_state", 5)},
            upper_arm_publisher{n.advertise<sensor_msgs::JointState>("/device45/set_joint_state", 5)},
            scoop_publisher{n.advertise<sensor_msgs::JointState>("/device56/set_joint_state", 5)}
{
  ROS_INFO("Initializing Arm Manipulator");
}

void ArmManipulator::moveArm(const double& turntable, const double& lower_arm ,const double& upper_arm,  const double& scoop )
{
    ROS_INFO_STREAM("Arm manipulator moveArm() called by: " << 
    ros::this_node::getName() << ". Parameters: " 
<< turntable << ", " << lower_arm << ", " << upper_arm << ", " << scoop << std::endl);
    ROS_INFO_STREAM("ArmManipulator::moveArm() deprecated. Replace calls to moveArm()." << std::endl);

    // TODO: Replace the other references to moveArm() in the code base.
}

void ArmManipulator::moveTurntablePosition(double turntable)
{
    sensor_msgs::JointState turntable_joint_state;

    turntable_joint_state.header.stamp = ros::Time::now();
    turntable_joint_state.position.push_back(turntable);
    
    turntable_publisher.publish(turntable_joint_state);
}

void ArmManipulator::moveLowerArmPosition(double lower_arm)
{
    sensor_msgs::JointState lower_arm_joint_state;

    lower_arm_joint_state.header.stamp = ros::Time::now();
    lower_arm_joint_state.position.push_back(lower_arm);

    lower_arm_publisher.publish(lower_arm_joint_state);
}

void ArmManipulator::moveUpperArmPosition(double upper_arm)
{
    sensor_msgs::JointState upper_arm_joint_state;

    upper_arm_joint_state.header.stamp = ros::Time::now();
    upper_arm_joint_state.position.push_back(upper_arm);

    upper_arm_publisher.publish(upper_arm_joint_state);
}

void ArmManipulator::moveScoopPosition(double scoop)
{
    sensor_msgs::JointState scoop_joint_state;

    scoop_joint_state.header.stamp = ros::Time::now();
    scoop_joint_state.position.push_back(scoop);

    scoop_publisher.publish(scoop_joint_state);
}

/*
 * Moves the arm to the given position.
 *
 * Notes:
 *  - Careful what parameters are passed in, the arm could collide with the robot.
 *
 *  - The method is not blocking, so the caller needs to wait for the arm to move.
 *    See digging_action_server.cpp for example.
 */
void ArmManipulator::moveArmWithoutPlanningOrLimits(
            const double& turntable, const double& lower_arm, const double& upper_arm, const double& scoop)
{
    ROS_INFO_STREAM("moveArmWithoutPlanningOrLimits() called by: " << ros::this_node::getName() << ". Parameters: " << turntable << ", " << lower_arm << ", " << upper_arm << ", " << scoop << std::endl);

    moveTurntablePosition(turntable);
    moveLowerArmPosition(lower_arm);
    moveUpperArmPosition(upper_arm);
    moveScoopPosition(scoop);

    return;
}
