#include "tfr_mission_control/robot_controls_tab.h"

#include <pluginlib/class_list_macros.h>


namespace tfr_mission_control {


	/**
	* A default constructor, but this is never called as a QWidget from the tab
	* is casted into a RobotControlsTab, so the object already exists.
	*
	*/
	RobotControlsTab::RobotControlsTab()
	{
	
	}

	/**
	* This destructor is called in the MissionControl's destructor
	*/
	RobotControlsTab::~RobotControlsTab() {
		delete arm_manipulator;
		delete controlsTabSubHandler;
	}


	/**
	* Connects all of the buttons in the tab to their according slot.
	* 
	*/
	void RobotControlsTab::setupSignalsAndSlots() {
		//Preset Buttons
		//Arm
		QPushButton* button = findChild<QPushButton*>("arm_storing_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::armStoringPos);

		button = findChild<QPushButton*>("arm_mining_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::armMiningPos);

		button = findChild<QPushButton*>("arm_dumping_excess_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::armDumpingExcessPos);

		button = findChild<QPushButton*>("arm_dumping_bin_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::armDumpingBinPos);

		button = findChild<QPushButton*>("arm_hold_gravel");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::armHoldGravel);

		//Turntable
		button = findChild<QPushButton*>("turntable_storing_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::turntableStoringPos);

		button = findChild<QPushButton*>("turntable_mining_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::turntableMiningPos);

		button = findChild<QPushButton*>("turntable_dumping_excess_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::turntableDumpingExcessPos);

		button = findChild<QPushButton*>("turntable_dumping_bin_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::turntableDumpingBinPos);

		button = findChild<QPushButton*>("turntable_face_forwards_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::turntableFaceForwards);

		//Bin
		button = findChild<QPushButton*>("bin_dumping_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::binDumpingPos);

		button = findChild<QPushButton*>("bin_collection_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::binCollectionPos);

		//Drivetrain
		button = findChild<QPushButton*>("drivetrain_preset_forwards");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::drivetrainPresetForwards);

		button = findChild<QPushButton*>("drivetrain_preset_backwards");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::drivetrainPresetBackwards);

		button = findChild<QPushButton*>("drivetrain_preset_left");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::drivetrainPresetTurnLeft);

		button = findChild<QPushButton*>("drivetrain_preset_right");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::drivetrainPresetTurnRight);


		//Keyboard controls
		//Arm
		button = findChild<QPushButton*>("extend_upper_arm_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::extendUpperArm);

		button = findChild<QPushButton*>("retract_upper_arm_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::retractUpperArm);

		button = findChild<QPushButton*>("extend_lower_arm_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::extendLowerArm);

		button = findChild<QPushButton*>("retract_lower_arm_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::retractLowerArm);

		button = findChild<QPushButton*>("extend_scoop_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::extendScoop);

		button = findChild<QPushButton*>("retract_scoop_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::retractScoop);

		//Turntable
		button = findChild<QPushButton*>("rotate_left_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::turntableRotateLeft);

		button = findChild<QPushButton*>("rotate_right_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::turntableRotateRight);

		//Bin
		button = findChild<QPushButton*>("extend_bin_controls_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::binExtend);

		button = findChild<QPushButton*>("retract_bin_controls_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::binRetract);

		//Drivetrain
		button = findChild<QPushButton*>("move_forward_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::drivetrainMoveForwards);

		button = findChild<QPushButton*>("move_backward_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::drivetrainMoveBackwards);

		button = findChild<QPushButton*>("turn_left_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::drivetrainTurnLeft);

		button = findChild<QPushButton*>("turn_right_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::drivetrainTurnRight);

		button = findChild<QPushButton*>("left_tread_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::drivetrainMoveLeftTread);

		button = findChild<QPushButton*>("right_tread_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::drivetrainMoveRightTread);


	}

	/**
	* Sets up all the ROS related prereqs needed such as 
	* setting up subscribers, creating new instances of trickfire ROS
	* handlers and so on.
	* 
	* As a note for the subscribers, for some reason you cannot assign ros::Subscribers
	* within QWdiget/QT_OBJECT classes. I have no idea why this is the case, but as a work
	* around I made a new class, ControlsTabSubHandler that will store the subscribers for this QWidget.
	* 
	* 
	*/
	void RobotControlsTab::setupROS(ros::NodeHandle node) {
		controlsTabSubHandler = new ControlsTabSubHandler();

		//Actuators
                controlsTabSubHandler->binPositionSub = node.subscribe("/device77/position_actual_value", 5, &RobotControlsTab::updateBinPosition, this);
                controlsTabSubHandler->upperArmPositionSub = node.subscribe("/device45/position_actual_value", 5, &RobotControlsTab::updateUpperArmPosition, this);
                controlsTabSubHandler->lowerArmPositionSub = node.subscribe("/device23/position_actual_value", 5, &RobotControlsTab::updateLowerArmPosition, this);
                controlsTabSubHandler->scoopPositionSub = node.subscribe("/device56/position_actual_value", 5, &RobotControlsTab::updateScoopPosition, this);

		//Turntable
		//controlsTabSubHandler->turntablePosSub = node.subscribe("/device1/get_joint_state", 5, &RobotControlsTab::updateTurntablePosition, this);



		binPos = 0;
		upperArmPos = 0;
		lowerArmPos = 0;
		scoopPos = 0;


		arm_manipulator = new ArmManipulator(node);
	}

	/**
	* Set whether the buttons in the tab are able to be pressed or not
	* 
	* @param availability The target availability state. 
	*		true = buttons can be pressed, false = buttons cannot be pressed
	* 
	*/
	void RobotControlsTab::setButtonAvailability(bool availability) {
		QList<QPushButton*> allButtons = findChildren<QPushButton*>();

		for (QPushButton* button : allButtons) {
			button->setEnabled(availability);
		}
	}


	// --------------------PRESET BUTTONS--------------------


	void RobotControlsTab::armStoringPos() {
		arm_manipulator->moveLowerArmPosition(5.0);
		arm_manipulator->moveUpperArmPosition(3.0);
		arm_manipulator->moveScoopPosition(3.5);
	}

	/*
	* Moves the whole arm to the mining position.
	* This does not move the turntable, move the turntable by its preset buttons.
	* 
	* Make sure that this will not hit anything when pressing
	* 
	* I got these positions from 
	* https://github.com/TrickfireRobotics/NasaRmc2019/blob/master/src/tfr_mining/data/use_this_one.yaml
	* 
	* " #[turntable, lowerArm, upperArm, scoop]
	* [[-3.14, 5.0, 0.7, 3.5], # scoop facing forward
	* [-3.14, 4.3, 0.7, 0.3], # SCOOP 1 ZERO POSITION
	* [-3.14, 3.0, 1.1, 0.3], # move over mining spot 1  <- I used this one
	* [-3.14, 2.0, 1.1, 0.3], # stick into dirt 2
	* [-3.14, 2.1, 2.8, 2.0], # pull scoop through 3
	* [-3.14, 4.2, 3.0, 3.3], # Come back up 4
	* [-3.14, 5.0, 3.6, 3.5], # Prep for rotation to discard 5
	* [-2.4, 5.0, 3.6, 3.5], # Rotate to discard position 6"
	*/
	void RobotControlsTab::armMiningPos() {
		arm_manipulator->moveLowerArmPosition(3.0);
		arm_manipulator->moveUpperArmPosition(1.1);
		arm_manipulator->moveScoopPosition(0.3);
	}

	/*
	* Moves the whole arm to the dumping excess dirt position.
	* This does not move the turntable, move the turntable by its preset buttons.
	* 
	* Make sure that this will not hit anything when pressing
	* 
	* I got these positions from
	* https://github.com/TrickfireRobotics/NasaRmc2019/blob/master/src/tfr_mining/data/use_this_one.yaml
	* 
	* 
	* " #[turntable, lowerArm, upperArm, scoop]
	* [[-3.14, 5.0, 0.7, 3.5], # scoop facing forward
	* [-3.14, 4.3, 0.7, 0.3], # SCOOP 1 ZERO POSITION
	* [-3.14, 3.0, 1.1, 0.3], # move over mining spot 1  
	* [-3.14, 2.0, 1.1, 0.3], # stick into dirt 2
	* [-3.14, 2.1, 2.8, 2.0], # pull scoop through 3
	* [-3.14, 4.2, 3.0, 3.3], # Come back up 4
	* [-3.14, 5.0, 3.6, 3.5], # Prep for rotation to discard 5 <- I used this one
	* [-2.4, 5.0, 3.6, 3.5], # Rotate to discard position 6"
	*/
	void RobotControlsTab::armDumpingExcessPos() {
		arm_manipulator->moveLowerArmPosition(5.0);
		arm_manipulator->moveUpperArmPosition(3.6);
		arm_manipulator->moveScoopPosition(0.3);
	}




	/*
	* Moves the whole arm to the bin to dump the load into.
	* This does not move the turntable, move the turntable by its preset buttons.
	* 
	* Make sure that this will not hit anything when pressing
	* 
	* I got these positions from
	* https://github.com/TrickfireRobotics/NasaRmc2019/blob/master/src/tfr_mining/data/use_this_one.yaml
	* 
	* 
	* " #[turntable, lowerArm, upperArm, scoop]
	*  [0.0, 5.5, 0.3, 2.0], # Open scoop partly to dump BP1 11" <- I used this one
	*/
	void RobotControlsTab::armDumpingBinPos() {
		arm_manipulator->moveLowerArmPosition(5.5);
		arm_manipulator->moveUpperArmPosition(0.3);
		arm_manipulator->moveScoopPosition(2.0);
	}



	/*
	* Moves the whole arm to face forwards
	* This does not move the turntable, move the turntable by its preset buttons.
	*
	* Make sure that this will not hit anything when pressing
	* 
	* 
	* I got these positions from
	* https://github.com/TrickfireRobotics/NasaRmc2019/blob/master/src/tfr_mining/data/use_this_one.yaml
	* 
	* " #[turntable, lowerArm, upperArm, scoop]
	* [[-3.14, 5.0, 0.7, 3.5], # scoop facing forward <- I used this one
	* [-3.14, 4.3, 0.7, 0.3], # SCOOP 1 ZERO POSITION
	* [-3.14, 3.0, 1.1, 0.3], # move over mining spot 1  
	* [-3.14, 2.0, 1.1, 0.3], # stick into dirt 2
	* [-3.14, 2.1, 2.8, 2.0], # pull scoop through 3
	* [-3.14, 4.2, 3.0, 3.3], # Come back up 4
	* [-3.14, 5.0, 3.6, 3.5], # Prep for rotation to discard 5 
	* [-2.4, 5.0, 3.6, 3.5], # Rotate to discard position 6"
	*/
	void RobotControlsTab::armHoldGravel() {
		arm_manipulator->moveLowerArmPosition(5.0);
		arm_manipulator->moveUpperArmPosition(0.7);
		arm_manipulator->moveScoopPosition(3.5);
	}


	/*
	* This moves the turntable to the storing position.
	* The storing position is when the scoop is facing the bin.
	* 
	* Make sure that the arm will not hit anything when pressing the button
	* 
	* I got these positions from
	* https://github.com/TrickfireRobotics/NasaRmc2019/blob/master/src/tfr_mining/data/use_this_one.yaml
	* 
	* "#For Turntable:
	* # 0 is facing towards the bin
	* # -2.4 is dumping excess spot
	* # -3.14 is mining spot"
	*/
	void RobotControlsTab::turntableStoringPos() {
		arm_manipulator->moveTurntablePosition(0.0);
	}

	/*
	* This moves the turntable to the mining position.
	*
	* Make sure that the arm will not hit anything when pressing the button
	* 
	* I got these positions from
	* https://github.com/TrickfireRobotics/NasaRmc2019/blob/master/src/tfr_mining/data/use_this_one.yaml
	* 
	* "#For Turntable:
	* # 0 is facing towards the bin
	* # -2.4 is dumping excess spot
	* # -3.14 is mining spot"
	*/
	void RobotControlsTab::turntableMiningPos() {
		arm_manipulator->moveTurntablePosition(-3.14);
	}

	/*
	* This moves the turntable to the dumping excess position.
	*
	* Make sure that the arm will not hit anything when pressing the button
	* 
	* I got these positions from
	* https://github.com/TrickfireRobotics/NasaRmc2019/blob/master/src/tfr_mining/data/use_this_one.yaml
	* 
	* "#For Turntable:
	* # 0 is facing towards the bin
	* # -2.4 is dumping excess spot
	* # -3.14 is mining spot"
	*/
	void RobotControlsTab::turntableDumpingExcessPos() {
		arm_manipulator->moveTurntablePosition(-2.4);
	}

	/*
	* This moves the turntable to the bin dumping position.
	*
	* Make sure that the arm will not hit anything when pressing the button
	*
	* I got these positions from
	* https://github.com/TrickfireRobotics/NasaRmc2019/blob/master/src/tfr_mining/data/use_this_one.yaml
	*
	* "#For Turntable:
	* # 0 is facing towards the bin
	* # -2.4 is dumping excess spot
	* # -3.14 is mining spot"
	*/
	void RobotControlsTab::turntableDumpingBinPos() {
		arm_manipulator->moveTurntablePosition(0);
	}



	/*
	* This moves the turntable to face fowards.
	* Forwards is when the scoop is facing away from the bin
	*
	* Make sure that the arm will not hit anything when pressing the button
	* 
	* 
	* I got these positions from
	* https://github.com/TrickfireRobotics/NasaRmc2019/blob/master/src/tfr_mining/data/use_this_one.yaml
	* 
	* 
	* "#For Turntable:
	* # 0 is facing towards the bin
	* # -2.4 is dumping excess spot
	* # -3.14 is mining spot"
	*/
	void RobotControlsTab::turntableFaceForwards() {
		arm_manipulator->moveTurntablePosition(-3.14);
	}

	/**
	* Extends the bin actuators by four inches, thus extending the
	* dumping bin.
	* 
	* The units are in inches
	* 
	*/
	void RobotControlsTab::binDumpingPos() {
		arm_manipulator->moveLeftBinPosition(4); // Extend left bin actuator
		arm_manipulator->moveRightBinPosition(4);// Extend right bin actuator
	}


	/**
	* Retracts the bin actuators back to the collection position
	* 
	* The units are in inches
	* 
	*/
	void RobotControlsTab::binCollectionPos() {
		arm_manipulator->moveLeftBinPosition(1.0); // Retract left bin actuator
		arm_manipulator->moveRightBinPosition(1.0);// Retract right bin actuator
	}

	//There are talks about redoing the drivtrain ros system, 
	//so implementation will not be here just yet
	void RobotControlsTab::drivetrainPresetForwards() {

	}

	void RobotControlsTab::drivetrainPresetBackwards() {

	}

	void RobotControlsTab::drivetrainPresetTurnLeft() {

	}

	void RobotControlsTab::drivetrainPresetTurnRight() {

	}


	// --------------------KEYBOARD CONTROLS--------------------



	void RobotControlsTab::extendUpperArm() {
		double newTarget = ACTUATOR_MANUAL_MOVE_VALUE + upperArmPos;


		arm_manipulator->moveUpperArmPosition(newTarget);
		

		//if (newTarget <= UPPER_ARM_MAX_POSITION) {

		//}
	}

	void RobotControlsTab::retractUpperArm() {
		double newTarget = upperArmPos - ACTUATOR_MANUAL_MOVE_VALUE;

		arm_manipulator->moveUpperArmPosition(newTarget);

		//if (newTarget >= UPPER_ARM_MIN_POSITION) {

		//}
	}

	void RobotControlsTab::extendLowerArm() {
		double newTarget = lowerArmPos + ACTUATOR_MANUAL_MOVE_VALUE;

		arm_manipulator->moveLowerArmPosition(newTarget);

		//if (newTarget <= LOWER_ARM_MAX_POSITION) {

		//}
	}

	void RobotControlsTab::retractLowerArm() {
		double newTarget = lowerArmPos - ACTUATOR_MANUAL_MOVE_VALUE;

		arm_manipulator->moveLowerArmPosition(newTarget);

		//if (newTarget >= LOWER_ARM_MIN_POSITION) {

		//}
	}


	void RobotControlsTab::extendScoop() {
		double newTarget = scoopPos + ACTUATOR_MANUAL_MOVE_VALUE;

		arm_manipulator->moveScoopPosition(newTarget);

		//if (newTarget <= SCOOP_MAX_POSITION) {

		//}
	}

	void RobotControlsTab::retractScoop() {
		double newTarget = scoopPos - ACTUATOR_MANUAL_MOVE_VALUE;

		arm_manipulator->moveScoopPosition(newTarget);

		//if (newTarget >= SCOOP_MIN_POSITION) {

		//}
	}


	void RobotControlsTab::turntableRotateLeft() {

	}

	void RobotControlsTab::turntableRotateRight() {

	}


	void RobotControlsTab::binExtend() {
        ROS_ERROR("%d",binPos);
		double newTarget = ACTUATOR_MANUAL_MOVE_VALUE + binPos;

		//make sure that we do not over extend anything
		if (newTarget <= BIN_MAX_POSITION) {
			arm_manipulator->moveLeftBinPosition(newTarget);
			arm_manipulator->moveRightBinPosition(newTarget);
		}
	}

	void RobotControlsTab::binRetract() {
		double newTarget = binPos - ACTUATOR_MANUAL_MOVE_VALUE;

		//make sure that we do not over extend anything
		if (newTarget >= BIN_MIN_POSITION) {
			arm_manipulator->moveLeftBinPosition(newTarget); 
			arm_manipulator->moveRightBinPosition(newTarget);
		}
	}


	void RobotControlsTab::drivetrainMoveForwards() {

	}

	void RobotControlsTab::drivetrainMoveBackwards() {

	}

	void RobotControlsTab::drivetrainTurnLeft() {

	}

	void RobotControlsTab::drivetrainTurnRight() {

	}

	void RobotControlsTab::drivetrainMoveLeftTread() {

	}

	void RobotControlsTab::drivetrainMoveRightTread() {

	}



	//------------------Callbacks-----------------

	/**
	* This will update the current position of the bin position in inches.
	* 
	* Luckily, the CAN topic /device77/position_actual_value will give us
	* the inches directly
	* 
	* But the topic gives us an int, not a double, which might be concerning if not tested
	* 
	* @param binSensorCounts Gives us the current position of the bin actuator
	* 
	*/
	void RobotControlsTab::updateBinPosition(const std_msgs::Int16 binSensorCount) {
		binPos = binSensorCount.data;
	}


	void RobotControlsTab::updateUpperArmPosition(const std_msgs::Int16 upperArmSensorCount) {
		upperArmPos = upperArmSensorCount.data;
	}

	void RobotControlsTab::updateLowerArmPosition(const std_msgs::Int16 lowerArmSensorCount) {
		lowerArmPos = lowerArmSensorCount.data;
	}


	void RobotControlsTab::updateScoopPosition(const std_msgs::Int16 scoopSensorCount) {
		scoopPos = scoopSensorCount.data;
	}


	void RobotControlsTab::updateTurntablePosition(const sensor_msgs::JointState turntableJointState) {
		turntablePos = turntableJointState.position[0];
	}






}
