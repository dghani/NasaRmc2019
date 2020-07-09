/****************************************************************************************
 * File:    arm_action_server.cpp
 * Node:    arm_action_server
 * 
 * Purpose: This ActionServer is what handles the movement of the arm to given points.
 *          It's tasked with interfacing with the move_group node to execute these
 *          actions.
 * 
 *          This file includes <tfr_msgs/ArmMove.h>, which is one of seven headers
 *          built by catkin from `tfr_msgs/action/ArmMove.action`:
 *              devel/include/tfr_msgs/ArmMoveAction.h
 *              devel/include/tfr_msgs/ArmMoveActionFeedback.h
 *              devel/include/tfr_msgs/ArmMoveActionGoal.h
 *              devel/include/tfr_msgs/ArmMoveActionResult.h
 *              devel/include/tfr_msgs/ArmMoveFeedback.h
 *              devel/include/tfr_msgs/ArmMoveGoal.h
 *              devel/include/tfr_msgs/ArmMoveResult.h
 * 
 ***************************************************************************************/
#include <ros/ros.h>
#include <control_msgs/FollowJointTrajectoryActionResult.h>
#include <actionlib/server/simple_action_server.h>
#include <tfr_msgs/ArmMoveAction.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <mutex>

