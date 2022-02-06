/****************************************************************************************
 * File:    digging_action_server.cpp
 * Node:    digging_server
 *
 * Purpose: This is an action server that handles all of the digging subsystem.
 *
 ***************************************************************************************/

#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include "digging_queue.h"
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include <tfr_msgs/ArmMoveAction.h>  // Note: "Action" is appended
#include <tfr_msgs/DiggingAction.h>  // Note: "Action" is appended
#include <tfr_utilities/arm_manipulator.h>
#include <tfr_utilities/teleop_code.h>


typedef actionlib::SimpleActionServer<tfr_msgs::DiggingAction> Server;
typedef actionlib::SimpleActionClient<tfr_msgs::ArmMoveAction> Client;


/*****************************************************************************
                               Initialize Class
 *****************************************************************************/

class DiggingActionServer {
public:
    DiggingActionServer(ros::NodeHandle &nh, ros::NodeHandle &p_nh) :
        priv_nh{p_nh},
        drivebase_publisher{nh.advertise<geometry_msgs::Twist>("cmd_vel", 5)},
        turnTableSub{nh.subscribe("arm_status/turnTable", 5, &DiggingActionServer::turnTableVelocityCallback, this)},
        lowerArmSub{nh.subscribe("/device23/get_position_actual_value", 5, &DiggingActionServer::lowerArmPositionCallback, this)},
        upperArmSub{nh.subscribe("/device45/get_position_actual_value", 5, &DiggingActionServer::upperArmPositionCallback, this)},
        scoopSub{nh.subscribe("/device56/get_position_actual_value", 5, &DiggingActionServer::scoopPositionCallback, this)},
        server{nh, "dig", boost::bind(&DiggingActionServer::execute, this, _1), false},
        arm_manipulator{nh}

    {
        server.start();
    }

private:

	/*
	 * Description:
   *
   * When the digging action server receives a goal, it starts by positioning
   * the arm straight in front of the rover with the arm in the air still.
   *
   * The position of the actuators will be monitored, so that during scooping
   * once the 3 actuator positions are close to where they were sent, the next
   * set of positions will be sent.
   *
   * During a scoop the max/min actuator positions will be saved to determine if
   * the arm reached the sent positions. After a scoop the current of the lower
   * arm actuator will be checked to determine how full of material the scoop
   * is. The position the arm reached and the fullness of the scoop will
   * determine how much farther down the next scoop will be.
   *
   * The position of the arm will also be used to determine if we reached the
   * depth of the icy regolith. Once the icy regolith is reached and scooped, it
   * will be deposited in the rover's bin
   *
   * The time clock.
	 *
	 * Pre: There must be accurate measurements of the position of the
   *      arm. Digging can start while the arm is turned off-center, but
   *      ROS must be aware of this. In other words, as long as the
   *      position of the arm is not miscalibrated, it's ok.
	 *
	 * Post: The arm will be in the position
	 *
	 */

/*****************************************************************************
                              Class Variables
*****************************************************************************/

    ros::NodeHandle &priv_nh;

    Server server;

    ros::Publisher drivebase_publisher;

    ArmManipulator arm_manipulator;

    ros::Subscriber turnTableSub;
    ros::Subscriber lowerArmSub;
    ros::Subscriber upperArmSub;
    ros::Subscriber scoopSub;

    bool turnTableMoving;
    bool lowerArmNear;
    bool upperArmNear;
    bool scoopNear;


/*****************************************************************************
                            Server Function
*****************************************************************************/

    void execute(const tfr_msgs::DiggingGoalConstPtr& goal) {

    }


/*****************************************************************************
                            Callback Functions
*****************************************************************************/

    void turnTableVelocityCallback(const std_msgs::Bool &turnTableStatus) {
      this->turnTableMoving = turnTableStatus.data;
    }

    void lowerArmPositionCallback(const std_msgs::Int32& lowerArmPosition) {

    }

    void upperArmPositionCallback(const std_msgs::Int32& upperArmPosition) {

    }

    void scoopPositionCallback(const std_msgs::Int32& scoopPosition) {
      
    }

};


/*****************************************************************************
                                   Main
 *****************************************************************************/

int main(int argc, char** argv)
{
    ros::init(argc, argv, "digging_server");

    ros::NodeHandle n;
    ros::NodeHandle p_n("~");

    DiggingActionServer digger(n, p_n);

    ros::spin();
    return 0;
}
