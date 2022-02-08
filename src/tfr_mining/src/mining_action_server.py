#! /usr/bin/env python

###############################################################################
# File:    mining_action_server.py
# Node:    mining_action_server
#
# Purpose: This is an action server that handles all of the digging subsystem.
#
# Description:
#
# When the digging action server receives a goal, it starts by positioning
# the arm straight in front of the rover with the arm in the air still.
#
# The position of the actuators will be monitored, so that during scooping
# once the 3 actuator positions are close to where they were sent, the next
# set of positions will be sent.
#
# During a scoop the max/min actuator positions will be saved to determine if
# the arm reached the sent positions. After a scoop the torque of the lower
# arm actuator will be checked to determine how full of material the scoop
# is. The position the arm reached and the fullness of the scoop will
# determine how much farther down the next scoop will be.
#
# The position of the arm will also be used to determine if we reached the
# depth of the icy regolith. Once the icy regolith is reached and scooped, it
# will be deposited in the rover's bin
#
# The time clock.
#
# Pre: There must be accurate measurements of the position of the
#      arm. Digging can start while the arm is turned off-center, but
#      ROS must be aware of this. In other words, as long as the
#      position of the arm is not miscalibrated, it's ok.
#
# Post: The arm will be back over the rover, ready to navigate back to the
#       dumping bin.
###############################################################################

import rospy
import actionlib
from std_msgs.msg import Int16
from std_msgs.msg import Int32
from tfr_msgs.msg import ArmMoveAction, DiggingAction


###############################################################################
#                             Initialize Class                                #
###############################################################################

class MiningActionServer:
    def __init__(self):
        rospy.Subscriber("/device1/get_velocity_actual_values/velocity_actual_value_averaged", Int32, self.turnTableVelocityCallback)
        rospy.Subscriber("/device23/get_torque_actual_value", Int16, self.lowerArmTorqueCallback)
        rospy.Subscriber("/device23/get_position_actual_value", Int32, self.lowerArmPositionCallback)
        rospy.Subscriber("/device45/get_position_actual_value", Int32, self.upperArmPositionCallback)
        rospy.Subscriber("/device56/get_position_actual_value", Int32, self.scoopPositionCallback)
        self.server = actionlib.SimpleActionServer('mining_action', DiggingAction, self.execute, False)


###############################################################################
#                              Server Function                                #
###############################################################################

    def execute(self, goal):
        self.server.set_succeeded()

###############################################################################
#                                 Callbacks                                   #
###############################################################################

    def turnTableVelocityCallback(self, data):
        rospy.loginfo(data)

    def lowerArmTorqueCallback(self, data):
        rospy.loginfo(data)

    def lowerArmPositionCallback(self, data):
        rospy.loginfo(data)

    def upperArmPositionCallback(self, data):
        rospy.loginfo(data)

    def scoopPositionCallback(self, data):
        rospy.loginfo(data)


###############################################################################
#                                   Main                                      #
###############################################################################

if __name__ == '__main__':
    rospy.init_node("mining_action_server")
    miner = MiningActionServer()
    #while not rospy.is_shutdown():
    rospy.spin()
