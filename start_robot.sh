#!/bin/bash
export ROS_MASTER_URI=http://192.168.0.181:11311
export ROS_HOSTNAME=192.168.0.181
echo "Attempting to bring down CAN interfaces"
./shutdownCAN.sh
echo "Attempting to bring up CAN interfaces"
./setupCAN.sh
. devel/setup.bash
roslaunch tfr_launch robot.launch


