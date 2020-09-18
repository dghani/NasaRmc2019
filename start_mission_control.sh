#!/bin/bash

. devel/setup.bash

rosparam set joy_node/dev "/dev/input/js0"
rosparam set joy_node/deadzone "0.4"
rosrun joy joy_node &

roslaunch tfr_launch mission_control.launch

