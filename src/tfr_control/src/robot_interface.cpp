
/** * controller.cpp *
 * This class is in charge of handling the physical hardware interface with
 * the robot itself, and is started by the controller_launcher node.
 */
#include "robot_interface.h"
#include <tfr_utilities/joints.h>

using hardware_interface::JointHandle;
using hardware_interface::JointStateHandle;

namespace tfr_control {
/*
 * Creates the robot interfaces spins up all the joints and registers them
 * with their relevant interfaces
 * */
RobotInterface::RobotInterface(ros::NodeHandle &n, bool fakes,
                               const double *lower_lim, const double *upper_lim)
    :

      brushless_left_tread_vel{
          n.subscribe("/device8/get_qry_abcntr/channel_1", 5,
                      &RobotInterface::setBrushlessLeftEncoder, this)},
      brushless_left_tread_vel_publisher{n.advertise<std_msgs::Int32>(
          "/device8/set_cmd_cango/cmd_cango_1", 1)},

      brushless_right_tread_vel{
          n.subscribe("/device8/get_qry_abcntr/channel_2", 5,
                      &RobotInterface::setBrushlessRightEncoder, this)},
      brushless_right_tread_vel_publisher{n.advertise<std_msgs::Int32>(
          "/device8/set_cmd_cango/cmd_cango_2", 1)},

      turntable_subscriber_encoder{
          n.subscribe("/device1/get_joint_state", 5,
                      &RobotInterface::readTurntableEncoder, this)},
      turntable_subscriber_torque{n.subscribe(
          "/device1/current_actual_values/current_actual_value_averaged", 1,
          &RobotInterface::readTurntableTorque, this)},
      turntable_publisher{n.advertise<std_msgs::Int32>(
          "/device4/set_cmd_cango/cmd_cango_1", 1)},

      lower_arm_subscriber_encoder{
          n.subscribe("/device23/get_joint_state", 5,
                      &RobotInterface::readLowerArmEncoder, this)},
      lower_arm_subscriber_torque{
          n.subscribe("/device23/get_torque_actual_value", 1,
                      &RobotInterface::readLowerArmTorque, this)},
      lower_arm_publisher{
          n.advertise<sensor_msgs::JointState>("/device23/set_joint_state", 1)},

      upper_arm_subscriber_encoder{
          n.subscribe("/device45/get_joint_state", 5,
                      &RobotInterface::readUpperArmEncoder, this)},
      upper_arm_subscriber_torque{
          n.subscribe("/device45/get_torque_actual_value", 1,
                      &RobotInterface::readUpperArmTorque, this)},
      upper_arm_publisher{
          n.advertise<sensor_msgs::JointState>("/device45/set_joint_state", 1)},

      scoop_subscriber_encoder{n.subscribe("/device56/get_joint_state", 5,
                                           &RobotInterface::readScoopEncoder,
                                           this)},
      scoop_subscriber_torque{n.subscribe("/device56/get_torque_actual_value",
                                          1, &RobotInterface::readScoopTorque,
                                          this)},
      scoop_publisher{
          n.advertise<sensor_msgs::JointState>("/device56/set_joint_state", 1)},

      // left_tread_publisher_pid_debug_setpoint{n.advertise<std_msgs::Float64>("/left_tread_velocity_controller/pid_debug/setpoint",
      // 1)}, Not sure if this does anything so disabling for debug purposes
      // left_tread_publisher_pid_debug_state{n.advertise<std_msgs::Float64>("/left_tread_velocity_controller/pid_debug/state",
      // 1)}, Not sure if this does anything so disabling for debug purposes
      // left_tread_publisher_pid_debug_command{n.advertise<std_msgs::Int32>("/left_tread_velocity_controller/pid_debug/command",
      // 1)}, Not sure if this does anything so disabling for debug purposes

      use_fake_values{fakes}, lower_limits{lower_lim}, upper_limits{upper_lim},
      drivebase_v0{std::make_pair(0, 0)},
      last_update{ros::Time::now()}, enabled{true} {

  // Note: the string parameters in these constructors must match the
  // joint names from the URDF, and yaml controller description.

  // Connect and register each joint with appropriate interfaces at our
  // layer
  registerJointEffortInterface("left_tread_joint",
                               tfr_utilities::Joint::LEFT_TREAD);
  registerJointEffortInterface("right_tread_joint",
                               tfr_utilities::Joint::RIGHT_TREAD);
  registerJointEffortInterface("bin_joint", tfr_utilities::Joint::BIN);
  registerJointPositionInterface("turntable_joint",
                                 tfr_utilities::Joint::TURNTABLE);
  registerJointPositionInterface("lower_arm_joint",
                                 tfr_utilities::Joint::LOWER_ARM);
  registerJointPositionInterface("upper_arm_joint",
                                 tfr_utilities::Joint::UPPER_ARM);
  registerJointPositionInterface("scoop_joint", tfr_utilities::Joint::SCOOP);
  // register the interfaces with the controller layer
  registerInterface(&joint_state_interface);
  registerInterface(&joint_effort_interface);
  registerInterface(&joint_position_interface);

  for (int joint = 0; joint < tfr_utilities::Joint::JOINT_COUNT; joint++) {
    velocity_values[joint] = 0;
    effort_values[joint] = 0;
  }
}

/*
 * Reads from our hardware and populates from shared memory.
 *
 * Information that is not explicity needed by our controllers
 * is written to some safe sensible default (usually 0).
 *
 * */
void RobotInterface::read() {
  // LEFT_TREAD
  position_values[static_cast<int>(tfr_utilities::Joint::LEFT_TREAD)] = 0;
  velocity_values[static_cast<int>(tfr_utilities::Joint::LEFT_TREAD)] =
      readBrushlessLeftVel();
  effort_values[static_cast<int>(tfr_utilities::Joint::LEFT_TREAD)] = 0;

  // RIGHT_TREAD
  position_values[static_cast<int>(tfr_utilities::Joint::RIGHT_TREAD)] = 0;
  velocity_values[static_cast<int>(tfr_utilities::Joint::RIGHT_TREAD)] =
      readBrushlessRightVel();
  effort_values[static_cast<int>(tfr_utilities::Joint::RIGHT_TREAD)] = 0;

  if (!use_fake_values) {
    // TURNTABLE
    double turntable_position_double = linear_interp<double>(
        static_cast<double>(turntable_encoder),
        static_cast<double>(turntable_encoder_min), turntable_joint_min,
        static_cast<double>(turntable_encoder_max), turntable_joint_max);

    position_values[static_cast<int>(tfr_utilities::Joint::TURNTABLE)] =
        turntable_position_double;
    velocity_values[static_cast<int>(tfr_utilities::Joint::TURNTABLE)] = 0;
    effort_values[static_cast<int>(tfr_utilities::Joint::TURNTABLE)] = 0;

    // LOWER_ARM
    double lower_arm_position_double = linear_interp<double>(
        static_cast<double>(lower_arm_encoder),
        static_cast<double>(arm_lower_encoder_min), arm_lower_joint_min,
        static_cast<double>(arm_lower_encoder_max), arm_lower_joint_max);

    double upper_arm_position_double = linear_interp<double>(
        static_cast<double>(upper_arm_encoder),
        static_cast<double>(arm_upper_encoder_min), arm_upper_joint_max,
        static_cast<double>(arm_upper_encoder_max), arm_upper_joint_min);

    double scoop_position_double = linear_interp<double>(
        static_cast<double>(scoop_encoder),
        static_cast<double>(arm_end_encoder_min), arm_end_joint_max,
        static_cast<double>(arm_end_encoder_max), arm_end_joint_min);

    position_values[static_cast<int>(tfr_utilities::Joint::LOWER_ARM)] =
        lower_arm_position_double;
    velocity_values[static_cast<int>(tfr_utilities::Joint::LOWER_ARM)] = 0;
    effort_values[static_cast<int>(tfr_utilities::Joint::LOWER_ARM)] = 0;

    // UPPER_ARM
    position_values[static_cast<int>(tfr_utilities::Joint::UPPER_ARM)] =
        upper_arm_position_double;
    velocity_values[static_cast<int>(tfr_utilities::Joint::UPPER_ARM)] = 0;
    effort_values[static_cast<int>(tfr_utilities::Joint::UPPER_ARM)] = 0;

    // SCOOP
    position_values[static_cast<int>(tfr_utilities::Joint::SCOOP)] =
        scoop_position_double;
    velocity_values[static_cast<int>(tfr_utilities::Joint::SCOOP)] = 0;
    effort_values[static_cast<int>(tfr_utilities::Joint::SCOOP)] = 0;
  }

  // BIN
  position_values[static_cast<int>(tfr_utilities::Joint::BIN)] = 0;
  velocity_values[static_cast<int>(tfr_utilities::Joint::BIN)] = 0;
  effort_values[static_cast<int>(tfr_utilities::Joint::BIN)] = 0;
}

/*
 * Writes command values from our controllers to our motors and actuators.
 *
 * Takes in command values from the controllers and these values are scaled
 * and written to the right place.
 *
 */
void RobotInterface::write() {

  double signal;
  if (use_fake_values) // test code for working with rviz simulator
  {
    adjustFakeJoint(tfr_utilities::Joint::TURNTABLE);
    adjustFakeJoint(tfr_utilities::Joint::LOWER_ARM);
    adjustFakeJoint(tfr_utilities::Joint::UPPER_ARM);
    adjustFakeJoint(tfr_utilities::Joint::SCOOP);
  }

  // LEFT_TREAD
  double left_tread_command =
      command_values[static_cast<int32_t>(tfr_utilities::Joint::LEFT_TREAD)];
  std_msgs::Int32 left_tread_msg;
  left_tread_msg.data =
      1 * clamp(static_cast<int32_t>(left_tread_command), -1000,
                1000); // changed -1 to 1 for debugging hall direction
  // left_tread_msg.data += 1; // for debugging only
  brushless_left_tread_vel_publisher.publish(left_tread_msg);

  // RIGHT_TREAD
  double right_tread_command =
      command_values[static_cast<int32_t>(tfr_utilities::Joint::RIGHT_TREAD)];
  std_msgs::Int32 right_tread_msg;
  right_tread_msg.data =
      1 * clamp(static_cast<int32_t>(right_tread_command), -1000,
                1000); // changed -1 to 1 for debugging hall direction
  // right_tread_msg.data += 1; // for debugging only
  brushless_right_tread_vel_publisher.publish(right_tread_msg);

  // UPKEEP
  last_update = ros::Time::now();
  drivebase_v0.first =
      velocity_values[static_cast<int>(tfr_utilities::Joint::LEFT_TREAD)];
  drivebase_v0.second =
      velocity_values[static_cast<int>(tfr_utilities::Joint::RIGHT_TREAD)];
}

template <typename T>
T RobotInterface::linear_interp(T x, T x1, T y1, T x2, T y2) {
  // line defined by two points: (x1, y1) and (x2, y2)
  T y = ((y2 - y1) / (x2 - x1)) * (x - x1) + y1;
  return y;
}

template <typename T>
T RobotInterface::clamp(const T input, const T bound_1, const T bound_2) {
  T lower_bound;
  T upper_bound;

  if (bound_1 < bound_2) {
    lower_bound = bound_1;
    upper_bound = bound_2;
  } else {
    upper_bound = bound_1;
    lower_bound = bound_2;
  }

  return std::max(std::min(input, upper_bound), lower_bound);
}

// TODO: Horrible duplication of code should be removed.
// has hardcoded min joint position in header file
const int32_t RobotInterface::get_arm_lower_min_int() {
  double arm_lower_joint_min_mapped = linear_interp<double>(
      arm_lower_joint_min * -10, arm_lower_joint_min,
      std::numeric_limits<int32_t>::min(), arm_lower_joint_max,
      std::numeric_limits<int32_t>::max());
  int32_t arm_lower_joint_min_mapped_int =
      static_cast<int32_t>(arm_lower_joint_min_mapped);

  return arm_lower_joint_min_mapped_int;
}

// has hardcoded max joint position in header file
const int32_t RobotInterface::get_arm_lower_max_int() {
  double arm_lower_joint_max_mapped = linear_interp<double>(
      arm_lower_joint_max * 10, arm_lower_joint_min,
      std::numeric_limits<int32_t>::min(), arm_lower_joint_max,
      std::numeric_limits<int32_t>::max());
  int32_t arm_lower_joint_max_mapped_int =
      static_cast<int32_t>(arm_lower_joint_max_mapped);

  return arm_lower_joint_max_mapped_int;
}

void RobotInterface::setEnabled(bool val) { enabled = val; }

void RobotInterface::adjustFakeJoint(const tfr_utilities::Joint &j) {
  int i = static_cast<int>(j);
  position_values[i] = command_values[i];
  // If this joint has limits, clamp the range down
  if (std::abs(lower_limits[i]) >= 1E-3 || std::abs(upper_limits[i]) >= 1E-3) {
    position_values[i] = std::max(std::min(position_values[i], upper_limits[i]),
                                  lower_limits[i]);
  }
}

/*
 * Tells the treads to stop moving, and the arm to hold position.
 *
 * The treads use velocity control, so they are set to 0 so that they their
 * speed drops to 0.
 *
 * The arm and bin use position control, so we stop them from moving by
 * commanding them to move to the position they are currently at.
 * */
void RobotInterface::clearCommands() {
  // LEFT_TREAD
  // command_values[static_cast<int>(tfr_utilities::Joint::LEFT_TREAD)] = 0;
  // Does this stop the bug?

  // RIGHT_TREAD
  //  command_values[static_cast<int>(tfr_utilities::Joint::RIGHT_TREAD)] = 0;

  // TURNTABLE
  command_values[static_cast<int>(tfr_utilities::Joint::TURNTABLE)] =
      position_values[static_cast<int>(tfr_utilities::Joint::TURNTABLE)];

  // LOWER_ARM
  command_values[static_cast<int>(tfr_utilities::Joint::LOWER_ARM)] =
      position_values[static_cast<int>(tfr_utilities::Joint::LOWER_ARM)];

  // UPPER_ARM
  command_values[static_cast<int>(tfr_utilities::Joint::UPPER_ARM)] =
      position_values[static_cast<int>(tfr_utilities::Joint::UPPER_ARM)];

  // SCOOP
  command_values[static_cast<int>(tfr_utilities::Joint::SCOOP)] =
      position_values[static_cast<int>(tfr_utilities::Joint::SCOOP)];

  // BIN
  command_values[static_cast<int>(tfr_utilities::Joint::BIN)] =
      position_values[static_cast<int>(tfr_utilities::Joint::BIN)];
}

/*
 * Retrieves the state of the bin
 * */
double RobotInterface::getBinState() {
  return position_values[static_cast<int>(tfr_utilities::Joint::BIN)];
}

/*
 * Retrieved the state of the arm
 * */
void RobotInterface::getArmState(std::vector<double> &position) {
  position.push_back(
      position_values[static_cast<int>(tfr_utilities::Joint::TURNTABLE)]);
  position.push_back(
      position_values[static_cast<int>(tfr_utilities::Joint::LOWER_ARM)]);
  position.push_back(
      position_values[static_cast<int>(tfr_utilities::Joint::UPPER_ARM)]);
  position.push_back(
      position_values[static_cast<int>(tfr_utilities::Joint::SCOOP)]);
}

void RobotInterface::readTurntableEncoder(const sensor_msgs::JointState &msg) {
  turntable_mutex.lock();

  turntable_encoder = msg.position[0];

  turntable_mutex.unlock();
}

void RobotInterface::readTurntableTorque(const std_msgs::Int16 &msg) {
  turntable_torque = msg.data;
}

void RobotInterface::readLowerArmEncoder(const sensor_msgs::JointState &msg) {
  lower_arm_mutex.lock();

  lower_arm_encoder = msg.position[0];

  lower_arm_mutex.unlock();
}

// TODO: Add mutex to protect all of these arm readings from reading while
// writing.
void RobotInterface::readLowerArmTorque(const std_msgs::Int16 &msg) {
  lower_arm_torque = msg.data;
}

void RobotInterface::readUpperArmEncoder(const sensor_msgs::JointState &msg) {
  upper_arm_mutex.lock();

  upper_arm_encoder = msg.position[0];

  upper_arm_mutex.unlock();
}

void RobotInterface::readUpperArmTorque(const std_msgs::Int16 &msg) {
  upper_arm_torque = msg.data;
}

void RobotInterface::readScoopEncoder(const sensor_msgs::JointState &msg) {
  scoop_mutex.lock();

  scoop_encoder = msg.position[0];

  scoop_mutex.unlock();
}

void RobotInterface::readScoopTorque(const std_msgs::Int16 &msg) {
  scoop_torque = msg.data;
}

/*
 * Register this joint with each neccessary hardware interface
 * */
void RobotInterface::registerJointEffortInterface(std::string name,
                                                  tfr_utilities::Joint joint) {
  auto idx = static_cast<int>(joint);
  // give the joint a state
  JointStateHandle state_handle(name, &position_values[idx],
                                &velocity_values[idx], &effort_values[idx]);
  joint_state_interface.registerHandle(state_handle);

  // allow the joint to be commanded
  JointHandle handle(state_handle, &command_values[idx]);
  joint_effort_interface.registerHandle(handle);
}

void RobotInterface::setBrushlessLeftEncoder(const std_msgs::Int32 &msg) {
  left_tread_absolute_encoder_current = msg.data;
  left_tread_time_current = ros::Time::now();
}

void RobotInterface::setBrushlessRightEncoder(const std_msgs::Int32 &msg) {
  right_tread_absolute_encoder_current = msg.data;
  right_tread_time_current = ros::Time::now();
}

/*
 * Register this joint with each neccessary hardware interface
 * */
void RobotInterface::registerJointPositionInterface(
    std::string name, tfr_utilities::Joint joint) {
  auto idx = static_cast<int>(joint);
  // give the joint a state
  JointStateHandle state_handle(name, &position_values[idx],
                                &velocity_values[idx], &effort_values[idx]);
  joint_state_interface.registerHandle(state_handle);

  // allow the joint to be commanded
  JointHandle handle(state_handle, &command_values[idx]);
  joint_position_interface.registerHandle(handle);
}

// get the ratio of the encoder count to the max encoder count for a revolution
double RobotInterface::brushlessEncoderCountToRadians(int32_t encoder_count) {
  return (2 * pi) * brushlessEncoderCountToRevolutions(encoder_count);
}

double
RobotInterface::brushlessEncoderCountToRevolutions(int32_t encoder_count) {
  return (static_cast<double>(encoder_count) /
          static_cast<double>(brushless_encoder_count_per_revolution));
}

// returns the linear speed of the robot (how fast it is moving forwards) in
// meters / second.
double RobotInterface::encoderDeltaToLinearSpeed(int32_t encoder_delta,
                                                 ros::Duration time_delta) {
  const double wheel_radius_meters = 0.15;
  const double wheel_circumference = 2 * 3.1415927 * wheel_radius_meters;

  const double revolutions = brushlessEncoderCountToRevolutions(encoder_delta);

  const double linear_speed_meters_per_sec =
      (wheel_circumference * revolutions) / time_delta.toSec();

  return linear_speed_meters_per_sec;
}

void RobotInterface::accumulateBrushlessRightVel(const std_msgs::Int32 &msg) {
  brushless_right_tread_mutex.lock();

  accumulated_brushless_right_tread_vel = msg.data;
  accumulated_brushless_right_tread_vel_num_updates++;
  accumulated_brushless_right_tread_vel_end_time =
      ros::Time::now(); // keep this call inside the mutex. The
                        // readBrushlessRightVel() call will also update it.

  brushless_right_tread_mutex.unlock();
}

void RobotInterface::accumulateBrushlessLeftVel(const std_msgs::Int32 &msg) {
  brushless_left_tread_mutex.lock();

  accumulated_brushless_left_tread_vel = msg.data;
  accumulated_brushless_left_tread_vel_num_updates++;
  accumulated_brushless_left_tread_vel_end_time = ros::Time::now();

  brushless_left_tread_mutex.unlock();
}

double RobotInterface::readBrushlessRightVel() {
  brushless_right_tread_mutex.lock();

  int32_t encoder_delta = right_tread_absolute_encoder_current -
                          right_tread_absolute_encoder_previous;

  ros::Duration time_delta =
      right_tread_time_current - right_tread_time_previous;

  right_tread_absolute_encoder_previous = right_tread_absolute_encoder_current;
  right_tread_time_previous = right_tread_time_current;

  brushless_right_tread_mutex.unlock();

  const double linear_speed_meters_per_sec =
      encoderDeltaToLinearSpeed(encoder_delta, time_delta);

  return linear_speed_meters_per_sec;
}

double RobotInterface::readBrushlessLeftVel() {
  brushless_left_tread_mutex.lock();

  int32_t encoder_delta = left_tread_absolute_encoder_current -
                          left_tread_absolute_encoder_previous;

  ros::Duration time_delta = left_tread_time_current - left_tread_time_previous;

  left_tread_absolute_encoder_previous = left_tread_absolute_encoder_current;
  left_tread_time_previous = left_tread_time_current;

  brushless_left_tread_mutex.unlock();

  const double linear_speed_meters_per_sec =
      encoderDeltaToLinearSpeed(encoder_delta, time_delta);

  return linear_speed_meters_per_sec;
}

void RobotInterface::zeroTurntable() {
  // TODO
}

} // namespace tfr_control
