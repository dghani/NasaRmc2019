# Install script for directory: /home/phillipov/NasaRmc2019/src/tfr_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/phillipov/NasaRmc2019/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/msg" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/msg/Echo.msg"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/msg/SystemStatus.msg"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/msg/ArduinoAReading.msg"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/msg/ArduinoBReading.msg"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/msg/PwmCommand.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/srv" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/srv/EmptySrv.srv"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/srv/QuerySrv.srv"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/srv/ArmStateSrv.srv"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/srv/BinStateSrv.srv"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/srv/DurationSrv.srv"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/srv/PoseSrv.srv"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/srv/WrappedImage.srv"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/srv/SetOdometry.srv"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/action" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/action/Teleop.action"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/action/Example.action"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/action/Navigation.action"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/action/Localization.action"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/action/Bin.action"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/action/Aruco.action"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/action/ArmMove.action"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/action/Empty.action"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/action/Digging.action"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/msg" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/TeleopAction.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/TeleopActionGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/TeleopActionResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/TeleopActionFeedback.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/TeleopGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/TeleopResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/TeleopFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/msg" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ExampleAction.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ExampleActionGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ExampleActionResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ExampleActionFeedback.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ExampleGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ExampleResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ExampleFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/msg" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/NavigationAction.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/NavigationActionGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/NavigationActionResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/NavigationActionFeedback.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/NavigationGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/NavigationResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/NavigationFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/msg" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/LocalizationAction.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/LocalizationActionGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/LocalizationActionResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/LocalizationActionFeedback.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/LocalizationGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/LocalizationResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/LocalizationFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/msg" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/BinAction.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/BinActionGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/BinActionResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/BinActionFeedback.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/BinGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/BinResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/BinFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/msg" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArucoAction.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArucoActionGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArucoActionResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArucoActionFeedback.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArucoGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArucoResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArucoFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/msg" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArmMoveAction.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArmMoveActionGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArmMoveActionResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArmMoveActionFeedback.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArmMoveGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArmMoveResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/ArmMoveFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/msg" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/EmptyAction.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/EmptyActionGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/EmptyActionResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/EmptyActionFeedback.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/EmptyGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/EmptyResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/EmptyFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/msg" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/DiggingAction.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/DiggingActionGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/DiggingActionResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/DiggingActionFeedback.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/DiggingGoal.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/DiggingResult.msg"
    "/home/phillipov/NasaRmc2019/devel/share/tfr_msgs/msg/DiggingFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/cmake" TYPE FILE FILES "/home/phillipov/NasaRmc2019/src/tfr_msgs/catkin_generated/installspace/tfr_msgs-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/phillipov/NasaRmc2019/devel/include/tfr_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/phillipov/NasaRmc2019/devel/share/roseus/ros/tfr_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/phillipov/NasaRmc2019/devel/share/common-lisp/ros/tfr_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/phillipov/NasaRmc2019/devel/share/gennodejs/ros/tfr_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python2" -m compileall "/home/phillipov/NasaRmc2019/devel/lib/python2.7/dist-packages/tfr_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python2.7/dist-packages" TYPE DIRECTORY FILES "/home/phillipov/NasaRmc2019/devel/lib/python2.7/dist-packages/tfr_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/phillipov/NasaRmc2019/src/tfr_msgs/catkin_generated/installspace/tfr_msgs.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/cmake" TYPE FILE FILES "/home/phillipov/NasaRmc2019/src/tfr_msgs/catkin_generated/installspace/tfr_msgs-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs/cmake" TYPE FILE FILES
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/catkin_generated/installspace/tfr_msgsConfig.cmake"
    "/home/phillipov/NasaRmc2019/src/tfr_msgs/catkin_generated/installspace/tfr_msgsConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tfr_msgs" TYPE FILE FILES "/home/phillipov/NasaRmc2019/src/tfr_msgs/package.xml")
endif()

