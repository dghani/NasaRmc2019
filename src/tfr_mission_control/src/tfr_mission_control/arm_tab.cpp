#include "tfr_mission_control/arm_tab.h"

#include <pluginlib/class_list_macros.h>


namespace tfr_mission_control {

	ArmTab::ArmTab() {
		//widget = tab;

		//QPushButton* button = findChild<QPushButton*>("test_button");

		//QObject::connect(button, &QPushButton::clicked, [&] {(ArmTab::setupSignalsAndSlotss);});

		//button->setEnabled(false);
		//widget->connect(button, &QPushButton::clicked, this, &ArmTab::setupSignalsAndSlotss);
	}

	ArmTab::~ArmTab() {

	}

	void ArmTab::pressButton() {
		QLabel* label = findChild<QLabel*>("label");

		label->setText("asdasasdsa");
	}

	void ArmTab::setupSignalsAndSlotss() {
		QPushButton* button = findChild<QPushButton*>("test_button");
		//button->setEnabled(false);

		//QLabel* label = findChild<QLabel*>("label");

		//label->setText("asdasasdsa");

		connect(button, &QPushButton::clicked, this, &ArmTab::pressButton);
	}

}
