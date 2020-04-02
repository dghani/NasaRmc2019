# CMake generated Testfile for 
# Source directory: /home/phillipov/NasaRmc2019/src/tfr_sensor
# Build directory: /home/phillipov/NasaRmc2019/src/tfr_sensor
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_tfr_sensor_gtest_tread_distance_test "/home/phillipov/NasaRmc2019/src/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/phillipov/NasaRmc2019/src/test_results/tfr_sensor/gtest-tread_distance_test.xml" "--return-code" "/home/phillipov/NasaRmc2019/devel/lib/tfr_sensor/tread_distance_test --gtest_output=xml:/home/phillipov/NasaRmc2019/src/test_results/tfr_sensor/gtest-tread_distance_test.xml")
add_test(_ctest_tfr_sensor_rostest_test_drivebase_odom.test "/home/phillipov/NasaRmc2019/src/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/melodic/share/catkin/cmake/test/run_tests.py" "/home/phillipov/NasaRmc2019/src/test_results/tfr_sensor/rostest-test_drivebase_odom.xml" "--return-code" "/opt/ros/melodic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/phillipov/NasaRmc2019/src/tfr_sensor --package=tfr_sensor --results-filename test_drivebase_odom.xml --results-base-dir \"/home/phillipov/NasaRmc2019/src/test_results\" /home/phillipov/NasaRmc2019/src/tfr_sensor/test/drivebase_odom.test ")
