#include <gtest/gtest.h>
#include <ros/ros.h>
#include <ros/callback_queue.h>
#include "std_msgs/Int32.h"
#include "std_msgs/Float64.h"
#include <nav_msgs/Odometry.h>
#include <tf2_ros/transform_listener.h>
#include <boost/function.hpp>
#include <cmath>


TEST(TreadDistanceNode, Basic)
{

    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);
    

    double wheel_span, wheelRadius, ticksPerRevolution, drivebaseOdomRate, drivebaseOdomPeriod;
    ros::param::param<double>("/tread_distance_publisher/wheelRadius", wheelRadius, -1);
    ros::param::param<double>("/tread_distance_publisher/ticksPerRevolution", ticksPerRevolution, -1);
    ros::param::param<double>("/drivebase_odom_publisher/wheel_span", wheel_span, -1);
    ros::param::param<double>("/drivebase_odom_publisher/rate", drivebaseOdomRate, -1);
    
    drivebaseOdomPeriod = 1/drivebaseOdomRate;
    
    ros::CallbackQueue leftTreadCBQueue;
    ros::NodeHandle leftTreadNH;
    leftTreadNH.setCallbackQueue(&leftTreadCBQueue);
    ros::Publisher leftTreadCountPublisher = leftTreadNH.advertise<std_msgs::Int32>("/left_tread_count", 15);
    double leftTreadDistance;
    boost::function<void(const std_msgs::Float64&)> leftTreadCallback = [&leftTreadDistance](const std_msgs::Float64& msg) {
        leftTreadDistance = msg.data;
    };
    auto leftTreadCountSub = leftTreadNH.subscribe<std_msgs::Float64>("/left_tread_distance", 10, leftTreadCallback);

    ros::CallbackQueue rightTreadCBQueue;
    ros::NodeHandle rightTreadNH;
    rightTreadNH.setCallbackQueue(&rightTreadCBQueue);
    ros::Publisher rightTreadCountPublisher = rightTreadNH.advertise<std_msgs::Int32>("/right_tread_count", 15);
    
    ros::CallbackQueue drivebaseOdomCBQueue;
    ros::NodeHandle drivebaseOdomNH;
    drivebaseOdomNH.setCallbackQueue(&drivebaseOdomCBQueue); 
    geometry_msgs::PoseWithCovariance drivebasePose;
    geometry_msgs::TwistWithCovariance drivbaseTwist;
    boost::function<void(const nav_msgs::Odometry&)> drivebaseOdomCallback = [&drivebasePose, &drivbaseTwist](const nav_msgs::Odometry& msg) {
        drivebasePose = msg.pose;
        drivbaseTwist = msg.twist;
    };

    auto odometrySub = drivebaseOdomNH.subscribe<nav_msgs::Odometry>("/drivebase_odom", 10, drivebaseOdomCallback);
    
    //wait for nodes to subscribe
    while(ros::ok() && (
        leftTreadCountPublisher.getNumSubscribers() < 1 || 
        rightTreadCountPublisher.getNumSubscribers() < 1)){}
    ROS_DEBUG("Subscribers Connected");

    std_msgs::Int32 treadCountMsg;
    
    auto waitAndProcessOneMessageCallbackQueue = [](ros::CallbackQueue & cb){    
        for (auto result=cb.callOne(); ros::ok() && result != ros::CallbackQueue::CallOneResult::Called; result=cb.callOne()){
            ROS_DEBUG("Queue Empty? %d", cb.empty());
            ROS_DEBUG("Queue Result %d", result);
            ros::Duration(0.1).sleep();
        }
    };
    
    //give first counts so drivebase_odom has distances to setup with
    treadCountMsg.data=0;
    leftTreadCountPublisher.publish(treadCountMsg);
    rightTreadCountPublisher.publish(treadCountMsg);
    ros::Duration(2*drivebaseOdomPeriod).sleep();

    waitAndProcessOneMessageCallbackQueue(leftTreadCBQueue);
    EXPECT_DOUBLE_EQ(leftTreadDistance, 0);

    //check drivebase is saying we aren't moving
    drivebaseOdomCBQueue.callAvailable();
    waitAndProcessOneMessageCallbackQueue(drivebaseOdomCBQueue);
    EXPECT_DOUBLE_EQ(drivebasePose.pose.position.x, 0);
    EXPECT_DOUBLE_EQ(drivebasePose.pose.position.y, 0);

    //forward a 1/2 revolution
    treadCountMsg.data=(ticksPerRevolution/2);
    leftTreadCountPublisher.publish(treadCountMsg);
    rightTreadCountPublisher.publish(treadCountMsg);
    ros::Duration(2*drivebaseOdomPeriod+.01).sleep();

    waitAndProcessOneMessageCallbackQueue(leftTreadCBQueue);
    EXPECT_DOUBLE_EQ(leftTreadDistance, M_PI*wheelRadius);

    drivebaseOdomCBQueue.callAvailable();
    waitAndProcessOneMessageCallbackQueue(drivebaseOdomCBQueue);
    EXPECT_DOUBLE_EQ(drivebasePose.pose.position.x, M_PI*wheelRadius);
    EXPECT_DOUBLE_EQ(drivebasePose.pose.position.y, 0);
    
    //forward 1 + 1/2 revolutions
    treadCountMsg.data=(ticksPerRevolution*2);
    leftTreadCountPublisher.publish(treadCountMsg);
    rightTreadCountPublisher.publish(treadCountMsg);
    ros::Duration(2*drivebaseOdomPeriod+.01).sleep();
    
    waitAndProcessOneMessageCallbackQueue(leftTreadCBQueue);
    EXPECT_DOUBLE_EQ(leftTreadDistance, 3*M_PI*wheelRadius);

    drivebaseOdomCBQueue.callAvailable();
    waitAndProcessOneMessageCallbackQueue(drivebaseOdomCBQueue);
    EXPECT_DOUBLE_EQ(drivebasePose.pose.position.x, 4*M_PI*wheelRadius);
    EXPECT_DOUBLE_EQ(drivebasePose.pose.position.y, 0);

    // back a revolution
    treadCountMsg.data=(ticksPerRevolution);
    leftTreadCountPublisher.publish(treadCountMsg);
    rightTreadCountPublisher.publish(treadCountMsg);
    ros::Duration(2*drivebaseOdomPeriod+.01).sleep();
    
    waitAndProcessOneMessageCallbackQueue(leftTreadCBQueue);
    EXPECT_DOUBLE_EQ(leftTreadDistance, -2*M_PI*wheelRadius);
    
    drivebaseOdomCBQueue.callAvailable();
    waitAndProcessOneMessageCallbackQueue(drivebaseOdomCBQueue);
    EXPECT_DOUBLE_EQ(drivebasePose.pose.position.x, 2*M_PI*wheelRadius);
    EXPECT_DOUBLE_EQ(drivebasePose.pose.position.y, 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "drivebase_integration_test");
    return RUN_ALL_TESTS();
}