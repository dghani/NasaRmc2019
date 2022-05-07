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

#include "tfr_mission_control/arm_tab.h"

namespace tfr_mission_control {

    /* Main entry point for the qt application, contains all of state, business
     * logic, and only has one screen. Uses the associated .ui file for layout
     * and design.
     * */
    class MissionControl : public rqt_gui_cpp::Plugin{

        Q_OBJECT

        public:

            /* ======================================================================== */
            /* Constructor/Destructor                                                   */
            /* ======================================================================== */

            MissionControl();
            ~MissionControl();

            /* ======================================================================== */
            /* Initialize/Shutdown                                                      */
            /* ======================================================================== */

            void initPlugin(qt_gui_cpp::PluginContext& context) override;

            void shutdownPlugin() override;

        private:            
            enum RobotMode {
                teleoperated,
                autonomous
            };

            enum InputType {
                keyboard,
                controller
            };


            /* ======================================================================== */
            /* Variables                                                                */
            /* ======================================================================== */

            //the user interface
            Ui::MissionControlWidget ui;
            //Out application context
            QWidget* widget;
            //the mission timer
            QTimer* countdownClock;

            //Represents if the robot is going to run one of the RobotModes
            std::atomic<bool> robotEnabled;

            //Represents the current running mode of the robot
            std::atomic<RobotMode> robotMode;

            std::atomic<InputType> inputType;

            ArmTab* armTab;



            /*Robot Specific*/
            void enableRobot();
            void disableRobot();
            void setRobotMode(MissionControl::RobotMode mode);
            void setInputType(MissionControl::InputType mode);

            /*ROS Specific*/
            void startTimeService();

            /*GUI Specific*/
            void renderClock();
            void setupButtons();





    };
}
