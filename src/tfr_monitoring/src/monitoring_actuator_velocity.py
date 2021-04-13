#!/usr/bin/python

##########################################################################################
# File:    monitoring_actuator_velocity.py
# Node:    monitoring_actuator_velocity
#
# Purpose: This subscribes to the velocities of the actuators to determine when they
#          are done moving. This also publishes a bool for each actuator depending on
#          whether they are moving or not, which is dependent on the tolerances set in
#          the launch file.
#
##########################################################################################

import rospy
from std_msgs.msg import Float32


class monitor:
    turnTableMoving = True

    def __init__(self):
        turnTableSub = rospy.Subscriber('/device1/velocity_actual_value', Float32, turnTableCallback, queue_size=5)


def turnTableCallback(msg):
    turnTableVelocity = msg.data
    rospy.loginfo(turnTableVelocity)
    if turnTableVelocity < 5.0:
        mon.turnTableMoving = False
    else:
        mon.turnTableMoving = True


if __name__ == '__main__':
    while True:
        try:
            rospy.init_node('monitoring_actuator_velocity')
            mon = monitor()
        except rospy.ROSInterruptException:
            pass
