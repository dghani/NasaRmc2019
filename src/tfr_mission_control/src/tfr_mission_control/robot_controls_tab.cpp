#include "tfr_mission_control/robot_controls_tab.h"

#include <pluginlib/class_list_macros.h>


namespace tfr_mission_control {



	RobotControlsTab::RobotControlsTab()
	{
	
	}

	RobotControlsTab::~RobotControlsTab() {

	}

	void RobotControlsTab::setupSignalsAndSlots() {
		//Preset Buttons
		//Arm
		QPushButton* button = findChild<QPushButton*>("arm_storing_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::armStoringPos);

		button = findChild<QPushButton*>("arm_mining_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::armMiningPos);

		button = findChild<QPushButton*>("arm_dumping_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::armDumpingPos);

		button = findChild<QPushButton*>("arm_face_forwards_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::armFaceForwards);

		//Turntable
		button = findChild<QPushButton*>("turntable_storing_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::turntableStoringPos);

		button = findChild<QPushButton*>("turntable_mining_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::turntableMiningPos);

		button = findChild<QPushButton*>("turntable_dumping_pos_button");
		connect(button, &QPushButton::clicked, this, &RobotControlsTab::turntableDumpingPos);

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

	void RobotControlsTab::setupROS(ros::NodeHandle& node) {
		arm_manipulator = new ArmManipulator(node);
	}

	void RobotControlsTab::setButtonAvailability(bool availability) {
		QList<QPushButton*> allButtons = findChildren<QPushButton*>();

		for (QPushButton* button : allButtons) {
			button->setEnabled(availability);
		}
	}


	void RobotControlsTab::armStoringPos() {

	}

	void RobotControlsTab::armMiningPos() {

	}

	void RobotControlsTab::armDumpingPos() {

	}

	void RobotControlsTab::armFaceForwards() {

	}


	void RobotControlsTab::turntableStoringPos() {

	}

	void RobotControlsTab::turntableMiningPos() {

	}

	void RobotControlsTab::turntableDumpingPos() {

	}

	void RobotControlsTab::turntableFaceForwards() {

	}


	void RobotControlsTab::binDumpingPos() {
		arm_manipulator->moveLeftBinPosition(5.0); // Extend left bin actuator
		arm_manipulator->moveRightBinPosition(5.0);// Extend right bin actuator
	}

	void RobotControlsTab::binCollectionPos() {
		arm_manipulator->moveLeftBinPosition(1.0); // Extend left bin actuator
		arm_manipulator->moveRightBinPosition(1.0);// Extend right bin actuator
	}


	void RobotControlsTab::drivetrainPresetForwards() {

	}

	void RobotControlsTab::drivetrainPresetBackwards() {

	}

	void RobotControlsTab::drivetrainPresetTurnLeft() {

	}

	void RobotControlsTab::drivetrainPresetTurnRight() {

	}



	void RobotControlsTab::extendUpperArm() {

	}

	void RobotControlsTab::retractUpperArm() {

	}

	void RobotControlsTab::extendLowerArm() {

	}

	void RobotControlsTab::retractLowerArm() {

	}


	void RobotControlsTab::extendScoop() {

	}

	void RobotControlsTab::retractScoop() {

	}


	void RobotControlsTab::turntableRotateLeft() {

	}

	void RobotControlsTab::turntableRotateRight() {

	}


	void RobotControlsTab::binExtend() {

	}

	void RobotControlsTab::binRetract() {

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




}