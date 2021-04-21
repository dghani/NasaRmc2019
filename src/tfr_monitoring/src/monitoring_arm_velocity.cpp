/*
* File:    monitoring_arm_velocity.cpp
* Node:    monitoring_arm_velocity
*
* Purpose: This subscribes to the velocities of the actuators to determine when they
*          are done moving. This also publishes a bool for each actuator depending on
*          whether they are moving or not, which is dependent on the tolerances set in
*          the launch file.
*
*/

#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>



/*****************************************************************************
                               Initialize Class
 *****************************************************************************/

class monitorArmVelocity {
public:
  monitorArmVelocity(ros::NodeHandle &nh, const float turnTableTolerance, const float lowerArmTolerance, const float upperArmTolerance, const float scoopTolerance) :
      turnTableSub{nh.subscribe("/device1/velocity_actual_value", 5, &monitorArmVelocity::turnTableCallback, this)},
      lowerArmSub{nh.subscribe("/device23/velocity_actual_value", 5, &monitorArmVelocity::lowerArmCallback, this)},
      upperArmSub{nh.subscribe("/device45/velocity_actual_value", 5, &monitorArmVelocity::upperArmCallback, this)},
      scoopSub{nh.subscribe("/device56/velocity_actual_value", 5, &monitorArmVelocity::scoopCallback, this)},
      turnTablePub{nh.advertise<std_msgs::Bool>("arm_status/turnTable", 10)},
      lowerArmPub{nh.advertise<std_msgs::Bool>("arm_status/lowerArm", 10)},
      upperArmPub{nh.advertise<std_msgs::Bool>("arm_status/upperArm", 10)},
      scoopPub{nh.advertise<std_msgs::Bool>("arm_status/scoop", 10)},
      turnTableTolerance{turnTableTolerance},
      lowerArmTolerance{lowerArmTolerance},
      upperArmTolerance{upperArmTolerance},
      scoopTolerance{scoopTolerance}
      {}



private:
  /*****************************************************************************
                                 Class Variables
   *****************************************************************************/

  // subscribers
  ros::Subscriber turnTableSub, lowerArmSub, upperArmSub, scoopSub;

  // publishers
  ros::Publisher turnTablePub, lowerArmPub, upperArmPub, scoopPub;

  // status
  // false/0 indicates actuators or turn table are not moving
  std_msgs::Bool turnTableMoving, lowerArmMoving, upperArmMoving, scoopMoving;

  // tolerances
  float turnTableTolerance, lowerArmTolerance, upperArmTolerance, scoopTolerance;



  /*****************************************************************************
                              Callback Functions
   *****************************************************************************/
  //called when the subsribers recieve a message from the publishers

  void turnTableCallback(const std_msgs::Float32& turnTableVelocity) {
    if (turnTableVelocity.data < this->turnTableTolerance && turnTableVelocity.data > -this->turnTableTolerance) {
      this->turnTableMoving.data = false;
    }
    else {
      this->turnTableMoving.data = true;
    }
    turnTablePub.publish(turnTableMoving);
  }

  void lowerArmCallback(const std_msgs::Float32& lowerArmVelocity) {
    if (lowerArmVelocity.data < this->lowerArmTolerance && lowerArmVelocity.data > -this->lowerArmTolerance) {
      this->lowerArmMoving.data = false;
    }
    else {
      this->lowerArmMoving.data = true;
    }
    lowerArmPub.publish(lowerArmMoving);
  }

  void upperArmCallback(const std_msgs::Float32& upperArmVelocity) {
    if (upperArmVelocity.data < this->upperArmTolerance && upperArmVelocity.data > -this->upperArmTolerance) {
      this->upperArmMoving.data = false;
    }
    else {
      this->upperArmMoving.data = true;
    }
    upperArmPub.publish(upperArmMoving);
  }

  void scoopCallback(const std_msgs::Float32& scoopVelocity) {
    if (scoopVelocity.data < this->scoopTolerance && scoopVelocity.data > -this->scoopTolerance) {
      this->scoopMoving.data = false;
    }
    else {
      this->scoopMoving.data = true;
    }
    scoopPub.publish(scoopMoving);
  }
};



/*****************************************************************************
                                   Main
 *****************************************************************************/

int main(int argc, char** argv) {
    ros::init(argc, argv, "monitoring_arm_velocity");
    ros::NodeHandle n;

    float turnTableTolerance, lowerArmTolerance, upperArmTolerance, scoopTolerance;
    // gotten from launch file
    ros::param::param<float>("~turnTableTolerance", turnTableTolerance, 0);
    ros::param::param<float>("~lowerArmTolerance", lowerArmTolerance, 0);
    ros::param::param<float>("~upperArmTolerance", upperArmTolerance, 0);
    ros::param::param<float>("~scoopTolerance", scoopTolerance, 0);

    monitorArmVelocity monitor(n, turnTableTolerance, lowerArmTolerance, upperArmTolerance, scoopTolerance);

    ros::Rate loop_rate(10);
    ros::spin();
    return 0;
}
