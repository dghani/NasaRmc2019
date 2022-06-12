#include <cstddef>
#include <mutex>

#include <tfr_utilities/arm_manipulator.h>
#include <ros/ros.h>


#include <std_msgs/Int16.h>


#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QScrollBar>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QKeyEvent>


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



#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QScrollBar>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QKeyEvent>

#include "tfr_mission_control/controls_tab_sub_handler.h"


/**
* To prevent MissonControl from becoming too large, the controls tab is represented by 
* this class. This will handle any button logic, UI visualizations, business logic, etc
* for this tab. 
* 
* Note: ros::Subscribers are stored in ControlTabSubhandler. The reason is explain in ControlTabSubhandler.h
* 
* We extend QWidget as we cast a real QWidget from the tab element of the ui so that we can add our
* additional functionality. 
* 
* 
*/
namespace tfr_mission_control {

	class RobotControlsTab : public QWidget {
		Q_OBJECT

		public:
			RobotControlsTab();
			~RobotControlsTab();
			void setupSignalsAndSlots();
			void setupROS(ros::NodeHandle node);
			void setButtonAvailability(bool availability);

			

		private:
			ArmManipulator* arm_manipulator;
			ControlsTabSubHandler* controlsTabSubHandler;

			//Current positions of the robot
			double binPos;
			double upperArmPos;
			double lowerArmPos;
			double scoopPos;
			

			//Subscriber callbacks
			void updateBinPosition(const std_msgs::Int16 binSensorCount);
			void updateUpperArmPosition(const std_msgs::Int16 upperArmSensorCount);
			void updateLowerArmPosition(const std_msgs::Int16 lowerArmSensorCount);
			void updateScoopPosition(const std_msgs::Int16 scoopSensorCount);



		protected slots://QT specific syntax
			void armStoringPos();
			void armMiningPos();
			void armDumpingPos();
			void armFaceForwards();

			void turntableStoringPos();
			void turntableMiningPos();
			void turntableDumpingPos();
			void turntableFaceForwards();

			void binDumpingPos();
			void binCollectionPos();

			void drivetrainPresetForwards();
			void drivetrainPresetBackwards();
			void drivetrainPresetTurnLeft();
			void drivetrainPresetTurnRight();


			void extendUpperArm();
			void retractUpperArm();

			void extendLowerArm();
			void retractLowerArm();

			void extendScoop();
			void retractScoop();

			void turntableRotateLeft();
			void turntableRotateRight();

			void binExtend();
			void binRetract();

			void drivetrainMoveForwards();
			void drivetrainMoveBackwards();
			void drivetrainTurnLeft();
			void drivetrainTurnRight();
			void drivetrainMoveLeftTread();
			void drivetrainMoveRightTread();


	};





}