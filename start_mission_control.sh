#!/bin/bash

. devel/setup.bash
#This next line allows Mission Control to only connect to the robot when connected to the team router at the below IP. Remove it if you want to develop on a local computer.
 export ROS_MASTER_URI=http://192.168.0.148:11311
 export ROS_HOSTNAME=$(hostname -I | tr -d "[:space:]")

rosparam set joy_node/dev "/dev/input/js0"
rosparam set joy_node/deadzone "0.4"
rosrun joy joy_node &

roslaunch tfr_launch mission_control.launch
