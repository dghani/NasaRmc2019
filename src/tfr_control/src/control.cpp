/**
 * controller_launcher.cpp
 * 
 * This is the controller layer for the ros control package.
 * It has the controller manager, which has the ability to register valid
 * controllers and manage their state. 
 * This layer maintains the state of the controller manager, and performs the
 * control loop for the control package.
 *
 * PARAMETERS:
 *  ~rate: in hz how fast we want to run the control loop (double, default:10)
 * SERVICES:
 *  /toggle_control - uses the empty service, needs to be explicitly turned on to work
 *  /toggle_motors - uses the empty service, needs to be explicitly turned on to work
 *  /bin_state - gives the position of the bin
 *  /arm_state - gives the 4d position of the arm
 *  /zero_turntable - zeros the position of the turntable
 */
#include <ros/ros.h>
#include <std_srvs/SetBool.h>
#include <std_srvs/Empty.h>
#include <tfr_msgs/QuerySrv.h>
#include <tfr_msgs/BinStateSrv.h>
#include <tfr_msgs/ArmStateSrv.h>
#include <urdf/model.h>
#include <sstream>
#include <controller_manager/controller_manager.h>
#include <tfr_utilities/joints.h>
#include "robot_interface.h"
#include "bin_control_server.h"
#include <sensor_msgs/Imu.h>
#include <geometry_msgs/Vector3.h>



namespace control_test
{
    // ADAM'S TEST CODE
    // Whether we're running on hardware or using fake values
    bool use_fake_values = false;
    // If we're faking the inputs, we need to know the model constraints on
    // the arm: load them here.
    // If not, just use zeroes, the limits don't matter. TEST code
    double lower_limits[tfr_utilities::Joint::JOINT_COUNT] = {};
    double upper_limits[tfr_utilities::Joint::JOINT_COUNT] = {};
}

using namespace control_test;

//test code
void initializeTestCode(ros::NodeHandle& n)
{
    // Get the model description 
    std::string desc;
    n.param<std::string>("robot_description", desc, "");

    if (desc.length() == 0) 
    {
        ROS_WARN("robot_description is empty and controller_launcher is using fake values, quitting.");
    }

    urdf::Model model;
    if (!model.initString(desc)) 
    {
        ROS_WARN("Couldn't load robot_description.");
    }

    ROS_INFO("Model loaded successfully, loading joint limits.");
    lower_limits[static_cast<int>(tfr_utilities::Joint::BIN)] 
        = model.getJoint("bin_joint")->limits->lower;
    upper_limits[static_cast<int>(tfr_utilities::Joint::BIN)] 
        = model.getJoint("bin_joint")->limits->upper;
    lower_limits[static_cast<int>(tfr_utilities::Joint::LOWER_ARM)] 
        = model.getJoint("lower_arm_joint")->limits->lower;
    upper_limits[static_cast<int>(tfr_utilities::Joint::LOWER_ARM)] 
        = model.getJoint("lower_arm_joint")->limits->upper;
    lower_limits[static_cast<int>(tfr_utilities::Joint::UPPER_ARM)] 
        = model.getJoint("upper_arm_joint")->limits->lower;
    upper_limits[static_cast<int>(tfr_utilities::Joint::UPPER_ARM)] 
        = model.getJoint("upper_arm_joint")->limits->upper;
    lower_limits[static_cast<int>(tfr_utilities::Joint::SCOOP)] 
        = model.getJoint("scoop_joint")->limits->lower;
    upper_limits[static_cast<int>(tfr_utilities::Joint::SCOOP)] 
        = model.getJoint("scoop_joint")->limits->upper;
}
//END TEST CODE


class Control
{
    public:
        Control(ros::NodeHandle &n, double& rate):
            robot_interface{n, use_fake_values, lower_limits, upper_limits},
            controller_interface{&robot_interface},
            eStopControl{n.advertiseService("toggle_control", &Control::toggleControl,this)},
            eStopMotors{n.advertiseService("toggle_motors", &Control::toggleControl,this)},
            binService{n.advertiseService("bin_state", &Control::getBinState,this)},
            armService{n.advertiseService("arm_state", &Control::getArmState,this)},
            zeroService{n.advertiseService("zero_turntable", &Control::zeroTurntable,this)},
            cycle{1/rate},
            enabled{false},
			quat_x_sub{n.subscribe("/device120/quaternion_x", 5, &Control::updatePrivateLocalVariable1,this)},
			quat_y_sub{n.subscribe("/device120/quaternion_y", 5, &Control::updatePrivateLocalVariable2,this)},
			quat_z_sub{n.subscribe("/device120/quaternion_z", 5, &Control::updatePrivateLocalVariable3,this)},
			quat_w_sub{n.subscribe("/device120/quaternion_w", 5, &Control::updatePrivateLocalVariable4,this)},
			lin_vel_x_sub{n.subscribe("linear_acceleration_x", 5, &Control::accumulateX,this)},
			lin_vel_y_sub{n.subscribe("linear_acceleration_y", 5, &Control::accumulateY,this)},
			lin_vel_z_sub{n.subscribe("linear_acceleration_z", 5, &Control::accumulateZ,this)}
		{}
        
        /*
         * performs one iteration of the control loop
         * */
        void execute()
        {
            //update from hardware
            robot_interface.read();
            //update controllers
            controller_interface.update(ros::Time::now(), cycle);
            //if (!enabled)
            //    robot_interface.clearCommands();
            //update hardware from controllers
            robot_interface.write();
			
            cycle.sleep();
        }

    private:
        //the hardware layer
        tfr_control::RobotInterface robot_interface;

        //the controller layer
        controller_manager::ControllerManager controller_interface;

        //emergency stop
        ros::ServiceServer eStopControl;
        ros::ServiceServer eStopMotors;

        //state services
        ros::ServiceServer binService;
        ros::ServiceServer armService;

        //reset service
        ros::ServiceServer zeroService;

        //how fast to spin
        ros::Duration cycle;

		double quat_x = 0;
		double quat_y = 0;
		double quat_z = 0;
		double quat_w = 0;
		
		double lin_acc_x = 0;
		double lin_acc_y = 0;
		double lin_acc_z = 0;
		
		double lin_vel_x = 0;
		double lin_vel_y = 0;
		double lin_vel_z = 0;
		
		ros::Subscriber quat_x_sub;
		ros::Subscriber quat_y_sub;
		ros::Subscriber quat_z_sub;
		ros::Subscriber quat_w_sub;
		
		ros::Subscriber lin_vel_x_sub;
		ros::Subscriber lin_vel_y_sub;
		ros::Subscriber lin_vel_z_sub;
		
		void updatePrivateLocalVariable1(const std_msgs::Float64 &value)
		{
			quat_x = value.data;
		}
		
		void updatePrivateLocalVariable2(const std_msgs::Float64 &value)
		{
			quat_y = value.data;
		}
		
		void updatePrivateLocalVariable3(const std_msgs::Float64 &value)
		{
			quat_z = value.data;
		}
		
		void updatePrivateLocalVariable4(const std_msgs::Float64 &value)
		{
			quat_w = value.data;
		}
		
		
		void accumulateX(const std_msgs::Float64 &value)
		{
			lin_acc_x = value.data;
			lin_vel_x += value.data;
		}
		
		void accumulateY(const std_msgs::Float64 &value)
		{
			lin_acc_y = value.data;
			lin_vel_y += value.data;
		}
		
		void accumulateZ(const std_msgs::Float64 &value)
		{
			lin_acc_z = value.data;
			lin_vel_z += value.data;
		}
		
		
        //if our motors are enabled
        bool enabled;

        /*
         * Toggles the emergency stop on and off
         * */
        bool toggleControl(std_srvs::SetBool::Request& request,
                std_srvs::SetBool::Response& response)
        {
            enabled = request.data;
            robot_interface.setEnabled(request.data);
            return true;
        }

        /*
         * Toggles the emergency stop on and off
         * */
        bool toggleMotors(std_srvs::SetBool::Request& request,
                std_srvs::SetBool::Response& response)
        {
            enabled = request.data;
            robot_interface.setEnabled(request.data);
            return true;
        }


        /*
         * Gets the state of the bin
         * */
        bool getBinState(tfr_msgs::BinStateSrv::Request& request,
                tfr_msgs::BinStateSrv::Response& response)
        {
            response.state = static_cast<double>(robot_interface.getBinState());
            return true;
        }

        /*
         * Gets the state of the arm
         * */
        bool getArmState(tfr_msgs::ArmStateSrv::Request& request,
                tfr_msgs::ArmStateSrv::Response& response)
        {
            std::vector<double> states{};
            robot_interface.getArmState(states);
            response.states = states;
            return true;
        }

        /*
         * Toggles the emergency stop on and off
         * */
        bool zeroTurntable(std_srvs::Empty::Request& request,
                std_srvs::Empty::Response& response)
        {
            robot_interface.zeroTurntable();
            return true;
        }


};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "control");
    ros::NodeHandle n;

    double rate;
    ros::param::param<double>("~rate", rate, 10.0);

    //test code
    if (use_fake_values)
        initializeTestCode(n);

    // Start a spinner for ros node in the background, seperate from this thread
    // that manages the control loop
    ros::AsyncSpinner spinner(1);
    spinner.start();

    Control control{n, rate};

    while (ros::ok())
    {
        ros::spinOnce();
        control.execute();
    }
    return 0;
}
