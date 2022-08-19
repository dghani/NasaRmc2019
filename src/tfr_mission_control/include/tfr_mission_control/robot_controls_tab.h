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

#include <sensor_msgs/JointState.h>

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
			double turntablePos;//Represented in radians


			//Keyboard control limits

			/**
			* Each time a keyboard control button is pressed for an actuator,
			* it will move the actuator 0.5 inches 
			*/
			const double ACTUATOR_MANUAL_MOVE_VALUE = 0.5;


			const double BIN_MAX_POSITION = 4.0;
			const double BIN_MIN_POSITION = 1.0;

			const double UPPER_ARM_MAX_POSITION = 10.0;//NEEDS TESTING
			const double UPPER_ARM_MIN_POSITION = 1.0;//NEEDS TESTING

			const double LOWER_ARM_MAX_POSITION = 10.0;//NEEDS TESTING
			const double LOWER_ARM_MIN_POSITION = 1.0;//NEEDS TESTING

			const double SCOOP_MAX_POSITION = 5.0;//NEEDS TESTING
			const double SCOOP_MIN_POSITION = 1.0;//NEEDS TESTING
			

			//Subscriber callbacks
			void updateBinPosition(const std_msgs::Int16 binSensorCount);
			void updateUpperArmPosition(const std_msgs::Int16 upperArmSensorCount);
			void updateLowerArmPosition(const std_msgs::Int16 lowerArmSensorCount);
			void updateScoopPosition(const std_msgs::Int16 scoopSensorCount);
			void updateTurntablePosition(const sensor_msgs::JointState turntableJointState);



		protected slots://QT specific syntax
			void armStoringPos();
			void armMiningPos();
			void armDumpingExcessPos();
			void armDumpingBinPos();
			void armHoldGravel();

			void turntableStoringPos();
			void turntableMiningPos();
			void turntableDumpingExcessPos();
			void turntableDumpingBinPos();
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