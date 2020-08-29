#include <arm_manipulator.h>

ArmManipulator::ArmManipulator(ros::NodeHandle &n, bool init_joints):
            turntable_publisher{n.advertise<sensor_msgs::JointState>("/device1/set_joint_state", 5)},
            turntable_target_position_subscriber{n.subscribe("/device1/target_position", 5, &ArmManipulator::updateTurntableTargetPosition, this)},
            turntable_position_actual_value_subscriber{n.subscribe("/device1/position_actual_value", 5, &ArmManipulator::updateTurntablePositionActualValue, this)},
            lower_arm(n, 23), 
            upper_arm(n, 45),
            scoop(n, 56),
            left_bin(n, 77),
            right_bin(n, 88)
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

bool ArmManipulator::isTurntablePositionReached()
{
    // Return true if the turntable is within 1 degree of its target position.
    // For the turntable there are 308224 ticks per revolution, so ~856 ticks == 1 degree.
    return std::abs(turntable_target_position - turntable_position_actual_value) <= 856;
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
            const double& turntable_pos, const double& lower_arm_pos, const double& upper_arm_pos, const double& scoop_pos)
{
    ROS_INFO_STREAM("moveArmWithoutPlanningOrLimits() called by: " << ros::this_node::getName() << ". Parameters: " << turntable_pos << ", " << lower_arm_pos << ", " << upper_arm_pos << ", " << scoop_pos << std::endl);

    moveTurntablePosition(turntable_pos);
    lower_arm.movePosition(lower_arm_pos);
    upper_arm.movePosition(upper_arm_pos);
    scoop.movePosition(scoop_pos);

    return;
}

// return true if all the arm actuators have reached the positions they were asked to move to.
// If you call this immediately after telling the arm to move somewhere, the actuators may not have started moving yet, and it
bool ArmManipulator::isArmTargetPositionReached() 
{
    // TODO: the TURNTABLE is not included!
    
    bool is_arm_stopped = 
        lower_arm.isTargetPositionReached() 
     && upper_arm.isTargetPositionReached() 
     && scoop.isTargetPositionReached()
     && isTurntablePositionReached(); 

    return is_arm_stopped;
}

void ArmManipulator::updateTurntableTargetPosition(const std_msgs::Int32 &value)
{
    turntable_target_position = value.data;
}

void ArmManipulator::updateTurntablePositionActualValue(const std_msgs::Int32 &value)
{
    turntable_position_actual_value = value.data;
}
