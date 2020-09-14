#!/bin/bash
opencv_ver="3.4.6"
sudo echo "Begin Install Script"
# start downloading some lovely dependencies
(sudo apt-get update; sudo apt-get install build-essential cmake cmake-gui cmake-qt-gui unzip pkg-config git libgtk2.0-dev libavcodec-dev libavformat-dev libswscale-dev python2.7-dev python3-dev python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev) &

# blow up any exisiting dir
rm -rf ./opencv
mkdir opencv; cd opencv

# clone repos from github and set their respective branches to the same version
(git clone https://github.com/opencv/opencv.git; cd opencv; git checkout $opencv_ver;) &
(git clone https://github.com/opencv/opencv_contrib.git; cd opencv_contrib; git checkout $opencv_ver;) &
wait
echo "Prereqs downloaded. Building."

# configure cmake to generate the makefile that tells how to build opencv
cd opencv; mkdir build; cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE -DBUILD_EXAMPLES=OFF -DBUILD_DOCS=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/usr/local -DENABLE_CXX11=ON -DCUDA_ARCH_BIN="7.2" -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules -DWITH_CUDA=ON -DWITH_V4L=ON -DWITH_LIBV4L=ON -DWITH_GSTREAMER=ON -DENABLE_FAST_MATH=ON -DCUDA_FAST_MATH=ON -DBUILD_LIST=core,highgui,improc,videoio,aruco,cudev ..

# build the glorious opencv bins
make -j$(nproc)

# put the bins someplace people/programs normally look for them
sudo make install
