#!/usr/bin/python

##########################################################################################
# File:    monitoring_actuator_velocity.py
# Node:    monitoring_actuator_velocity
#
# Purpose: This subscribes to the velocities of the actuators to determine when they
#          are done moving. This also publishes a bool for each actuator depending on
#          whether they are moving or not dependent on the tolerances set in the launch
#          file.
#
##########################################################################################

import rospy
from std_msgs.msg import Float32

def turnTableCallback(turnTableVelocity):
    if turnTableVelocity < turnTableTolerance and turnTableVelocity > -turnTableTolerance:
        turnTableMoving = False
    else:
        turnTableMoving = True

if __name__ == '__main__':
    while True:
        try:
            rospy.init_node("monitoring_actuator_velocity")
            turnTableSub = rospy.Subscriber("/device1/velocity_actual_value", Float32, turnTableCallback, queue_size=5)
            if turnTableMoving == False:
                ros.loginfo("yeet")
        except rospy.ROSInterruptException:
            pass
