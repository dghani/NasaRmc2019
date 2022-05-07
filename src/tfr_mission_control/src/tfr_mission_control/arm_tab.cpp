#include "tfr_mission_control/arm_tab.h"

#include <pluginlib/class_list_macros.h>


namespace tfr_mission_control {

	ArmTab::ArmTab() {
	}

	ArmTab::~ArmTab() {

	}


	void ArmTab::setupSignalsAndSlots() {

		//Preset buttons
		QPushButton* button = findChild<QPushButton*>("starting_pos_button");
		connect(button, &QPushButton::clicked, this, &ArmTab::startingPosition);

		button = findChild<QPushButton*>("mining_pos_button");
		connect(button, &QPushButton::clicked, this, &ArmTab::miningPosition);

		button = findChild<QPushButton*>("dumping_pos_button");
		connect(button, &QPushButton::clicked, this, &ArmTab::dumpingPosition);

		button = findChild<QPushButton*>("face_fowards_button");
		connect(button, &QPushButton::clicked, this, &ArmTab::faceFowards);

		//Arm keyboard controls
		button = findChild<QPushButton*>("extend_upper_arm_button");
		connect(button, &QPushButton::clicked, this, &ArmTab::upperArmExtend);

		button = findChild<QPushButton*>("retract_upper_arm_button");
		connect(button, &QPushButton::clicked, this, &ArmTab::upperArmRetract);

		button = findChild<QPushButton*>("extend_lower_arm_button");
		connect(button, &QPushButton::clicked, this, &ArmTab::lowerArmExtend);

		button = findChild<QPushButton*>("retract_lower_arm_button");
		connect(button, &QPushButton::clicked, this, &ArmTab::lowerArmRetract);

		button = findChild<QPushButton*>("extend_scoop_button");
		connect(button, &QPushButton::clicked, this, &ArmTab::scoopExtend);

		button = findChild<QPushButton*>("retract_scoop_button");
		connect(button, &QPushButton::clicked, this, &ArmTab::scoopRetract);




	}

	void ArmTab::setButtonAvailability(bool availability) {
		QList<QPushButton*> allButtons = findChildren<QPushButton*>();

		for (QPushButton* button : allButtons) {
			button->setEnabled(availability);
		}
	}

	void ArmTab::startingPosition() {

	}

	void ArmTab::miningPosition() {

	}

	void ArmTab::dumpingPosition() {

	}

	void ArmTab::faceFowards() {

	}

	void ArmTab::upperArmExtend() {

	}

	void ArmTab::upperArmRetract() {

	}

	void ArmTab::lowerArmExtend() {

	}

	void ArmTab::lowerArmRetract() {

	}

	void ArmTab::scoopExtend() {

	}

	void ArmTab::scoopRetract() {

	}





}
