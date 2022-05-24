#!/bin/bash
rm -rf installRealSenseSDK
git clone https://github.com/IntelRealSense/realsense-ros.git
cd installRealSenseSDK/
git checkout `git tag | sort -V | grep -P "^2.\d+\.\d+" | tail -1`
cd ..
sudo apt-get update
sudo apt-get install libssl-dev libusb-1.0-0-dev pkg-config -y
sudo apt-get install build-essential cmake cmake-curses-gui -y
sudo apt-get install libgtk-3-dev libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev -y
sudo apt-get install qtcreator -y
sudo apt-get install -y python3 python3-dev
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
source ~/.bashrc
