#include <gtest/gtest.h>
#include <ros/ros.h>
#include <ros/callback_queue.h>
#include "std_msgs/Int32.h"
#include "std_msgs/Float64.h"
#include <boost/function.hpp>
#include <cmath>


TEST(TreadDistanceNode, Basic)
{
    ros::CallbackQueue leftTreadCBQueue;
    ros::NodeHandle distanceNH;
    distanceNH.setCallbackQueue(&leftTreadCBQueue);
    ros::Publisher leftTreadCountPublisher = distanceNH.advertise<std_msgs::Int32>("/left_tread_count", 15);
    
    double val;
    boost::function<void(const std_msgs::Float64&)> leftTreadCallback = [&val](const std_msgs::Float64& msg) {
        val = msg.data;
    };
    auto leftTreadCountSub = distanceNH.subscribe<std_msgs::Float64>("/left_tread_distance", 10, leftTreadCallback);
    
    //wait for node to subscribe
    while(ros::ok() && leftTreadCountPublisher.getNumSubscribers() < 1){}
    ROS_DEBUG("Subscriber Connected");

    std_msgs::Int32 int32Msg;
    int32Msg.data=5;
    leftTreadCountPublisher.publish(int32Msg);

    auto waitAndProcessOneMessage = [&leftTreadCBQueue]{    
        for (auto result=leftTreadCBQueue.callOne(); ros::ok() && result != ros::CallbackQueue::CallOneResult::Called; result=leftTreadCBQueue.callOne()){
            ROS_DEBUG("Queue Empty? %d", leftTreadCBQueue.empty());
            ROS_DEBUG("Queue Result %d", result);
            ros::Duration(0.1).sleep();
        }
    };

    waitAndProcessOneMessage();
    EXPECT_EQ(val, M_PI);
   
    int32Msg.data=-5;
    leftTreadCountPublisher.publish(int32Msg);
    waitAndProcessOneMessage();
    EXPECT_EQ(val, -2*M_PI);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "drivebase_integration_test");
    return RUN_ALL_TESTS();
}