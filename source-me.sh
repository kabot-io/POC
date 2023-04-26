#!/bin/bash

kill_gazebo(){
  pkill -f gzserver
  pkill -f gzclient
}

launch_creator(){
  colcon build
  source install/setup.bash
  ~/Qt/Tools/QtCreator/bin/qtcreator
}

launch_kabot(){
  kill_gazebo
  colcon build --symlink-install
  source install/setup.bash
  echo ""
  echo ""
  ros2 launch kabot_launcher kabot.launch.py --show-args
  echo ""
  echo ""
  ros2 launch kabot_launcher kabot.launch.py
}

launch_kabot_foxglove(){
  kill_gazebo
  colcon build --symlink-install
  source install/setup.bash
  ros2 launch kabot_launcher kabot.launch.py foxglove_setup:='True'
}

launch_kabot_rviz(){
  kill_gazebo
  colcon build --symlink-install
  source install/setup.bash
  ros2 launch kabot_launcher kabot.launch.py rviz_setup:='True'
}

rebuild(){
  rm -rf install log build
  colcon build --symlink-install
}

show_topics(){
	while true; do clear; ros2 topic list; sleep 5; done
}

show_services(){
  while true; do clear; ros2 service list; sleep 5; done
}

export LC_NUMERIC=en_US.UTF-8
source /opt/ros/foxy/setup.bash
