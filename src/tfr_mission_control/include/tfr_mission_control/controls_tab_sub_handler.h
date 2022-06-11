#pragma once

#include <rqt_gui_cpp/plugin.h>
#include <tfr_mission_control/ui_mission_control.h>
#include "tfr_mission_control/joy_constants.h"

#include <ros/ros.h>
#include <ros/console.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <std_srvs/SetBool.h>
#include <std_srvs/Empty.h>
#include <sensor_msgs/Joy.h>

#include <tfr_msgs/SystemStatus.h>
#include <tfr_msgs/DurationSrv.h>
#include <tfr_msgs/EmptyAction.h>
#include <tfr_msgs/TeleopAction.h>
#include <tfr_msgs/ArmMoveAction.h>
#include <tfr_msgs/ArmStateSrv.h>

#include <tfr_utilities/teleop_code.h>
#include <tfr_utilities/status_code.h>

#include <cstddef>
#include <mutex>

#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QScrollBar>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QKeyEvent>

/**
* This class is a work around of the fact that you cannot
* store ros::Subscribers in a class that a QWidget/Q_OBJECT.
* If you do, it will segfault and when assigning a subscriber.
* I do not know why this is the case, but this work around works.
* 
* This class is initialized within the RobotControlsTab::setupROS and then
* assigns subscriber in here through a pointer.
* 
* The sole purpose is to store subscribers
* 
* 
*/
namespace tfr_mission_control {

    class ControlsTabSubHandler{
        


        public:

            ControlsTabSubHandler();
            ~ControlsTabSubHandler();

            ros::Subscriber binPositionSub;

    };
}
