#include "tfr_mission_control/controls_tab_sub_handler.h"

#include <pluginlib/class_list_macros.h>

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

	/**
	* Default constructor. No need to do anything as
	* the class just stores subscribers
	* 
	* 
	*/
	ControlsTabSubHandler::ControlsTabSubHandler(){

	}

	/**
	* Destructor, does nothing 
	* 
	*/
	ControlsTabSubHandler::~ControlsTabSubHandler() {

	}

}