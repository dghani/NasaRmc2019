/****************************************************************************************
 * File:    digging_action_server.cpp
 * Node:    digging_server
 *
 * Purpose: This is an action server that handles all of the digging subsystem.
 *
 *          This file includes <tfr_msgs/DiggingAction.h>, which is one of seven headers
 *          built by catkin from `tfr_msgs/action/Digging.action`:
 *              devel/include/tfr_msgs/DiggingAction.h
 *              devel/include/tfr_msgs/DiggingActionFeedback.h
 *              devel/include/tfr_msgs/DiggingActionGoal.h
 *              devel/include/tfr_msgs/DiggingActionResult.h
 *              devel/include/tfr_msgs/DiggingFeedback.h
 *              devel/include/tfr_msgs/DiggingGoal.h
 *              devel/include/tfr_msgs/DiggingResult.h
 *
 ***************************************************************************************/

#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <tfr_msgs/DiggingAction.h>  // Note: "Action" is appended
#include <tfr_msgs/ArmMoveAction.h>  // Note: "Action" is appended
#include <tfr_utilities/arm_manipulator.h>
#include <geometry_msgs/Twist.h>
#include <tfr_utilities/teleop_code.h>
#include <actionlib/client/simple_action_client.h>
#include "digging_queue.h"
#include <std_msgs/Bool.h>

typedef actionlib::SimpleActionServer<tfr_msgs::DiggingAction> Server;
typedef actionlib::SimpleActionClient<tfr_msgs::ArmMoveAction> Client;

class DiggingActionServer {
public:
    DiggingActionServer(ros::NodeHandle &nh, ros::NodeHandle &p_nh) :
        priv_nh{p_nh}, queue{priv_nh},
        drivebase_publisher{nh.advertise<geometry_msgs::Twist>("cmd_vel", 5)},
        turnTableSubscriber{nh.subscribe("arm_status/turnTable", 5, &DiggingActionServer::turnTableVelocityCallback, this)},
        lowerArmSubscriber{nh.subscribe("arm_status/lowerArm", 5, &DiggingActionServer::lowerArmVelocityCallback, this)},
        upperArmSubscriber{nh.subscribe("arm_status/upperArm", 5, &DiggingActionServer::upperArmVelocityCallback, this)},
        scoopSubscriber{nh.subscribe("arm_status/scoop", 5, &DiggingActionServer::scoopVelocityCallback, this)},
        server{nh, "dig", boost::bind(&DiggingActionServer::execute, this, _1), false},
        arm_manipulator{nh}

    {
        server.start();
    }

private:

	/*
	 * Description:
     *
     * When the digging action server receives a goal, it executes one
     * iteration of the digging queue.
     *
	 * Currently the digging action server receives the number of seconds
     * it is allowed to spend on digging in the goal message. This is not
     * currently used, but in the future (TODO) it can be used to control the
     * time spent digging autonomously.
	 *
	 * Pre: There must be accurate measurements of the position of the
     * arm. Digging can start while the arm is turned off-center, but
     * ROS must be aware of this. In other words, as long as the
     * position of the arm is not miscalibrated, it's ok.
	 *
	 * Post: The arm will be in the position specified at the end of the
     * digging queue, OR in an intermediate state if pre-empted (i.e. the
     * goal is cancelled, another goal is sent, or ROS is shutting down).
	 *
	 * Notes: ROS actionlib seemed to have a bug, and it would take
     * as much as 10 seconds to cancel a digging goal.
	 *
	 */

    ros::NodeHandle &priv_nh;

    Server server;

    ros::Publisher drivebase_publisher;

    ArmManipulator arm_manipulator;

    ros::Subscriber turnTableSubscriber;
    ros::Subscriber lowerArmSubscriber;
    ros::Subscriber upperArmSubscriber;
    ros::Subscriber scoopSubscriber;

    bool turnTableMoving;
    bool lowerArmMoving;
    bool upperArmMoving;
    bool scoopMoving;

    double turnTablePosition;


    void execute(const tfr_msgs::DiggingGoalConstPtr& goal)
    {

    }



    void turnTableVelocityCallback(const std_msgs::Bool &turnTableStatus) {
      this->turnTableMoving = turnTableStatus.data;
    }

    void lowerArmVelocityCallback(const std_msgs::Bool &lowerArmStatus) {
      this->lowerArmMoving = lowerArmStatus.data;
    }

    void upperArmVelocityCallback(const std_msgs::Bool &upperArmStatus) {
      this->upperArmMoving = upperArmStatus.data;
    }

    void scoopVelocityCallback(const std_msgs::Bool &scoopStatus) {
      this->scoopMoving = scoopStatus.data;
    }

};



int main(int argc, char** argv)
{
    ros::init(argc, argv, "digging_server");
    ros::NodeHandle n;
    ros::NodeHandle p_n("~");

    DiggingActionServer digger(n, p_n);
    ros::spin();
    return 0;
}
