#include "tfr_mission_control/arm_tab.h"

#include <pluginlib/class_list_macros.h>


namespace tfr_mission_control {

	ArmTab::ArmTab() {
	}

	ArmTab::~ArmTab() {

	}

	void ArmTab::pressButton() {
		QLabel* label = findChild<QLabel*>("label");

		label->setText("asdasasdsa");
	}

	void ArmTab::setupSignalsAndSlots() {
		QPushButton* button = findChild<QPushButton*>("test_button");
		connect(button, &QPushButton::clicked, this, &ArmTab::pressButton);
	}

	void ArmTab::setButtonAvailability(bool availability) {
		QList<QPushButton*> allButtons = findChildren<QPushButton*>();

		for (QPushButton* button : allButtons) {
			button->setEnabled(availability);
		}
	}





}
