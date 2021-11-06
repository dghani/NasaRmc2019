#!/bin/bash
rm -rf installRealSenseSDK
git clone https://github.com/jetsonhacks/installRealSenseSDK.git
cd installRealSenseSDK
sudo apt-get update
sudo apt-get install libssl-dev libusb-1.0-0-dev pkg-config -y
sudo apt-get install build-essential cmake cmake-curses-gui -y
sudo apt-get install libgtk-3-dev libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev -y
sudo apt-get install qtcreator -y
sudo apt-get install -y python3 python3-dev
yes | ./buildLibrealsense.sh [ -v | 2.48.0 ]
