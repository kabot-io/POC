#!/bin/bash

launch_creator(){
  colcon build
  source install/setup.bash
  ~/Qt/Tools/QtCreator/bin/qtcreator
}

launch_kabot(){
  colcon build
  source install/setup.bash
  echo ""
  echo "Default launch arguments"
  ros2 launch kabot_launcher kabot.launch.py --show-args
  echo ""
  echo ""
  ros2 launch kabot_launcher kabot.launch.py
}

launch_kabot_foxglove(){
  colcon build
  source install/setup.bash
  ros2 launch kabot_launcher kabot.launch.py foxglove_setup:='True'
}

launch_kabot_rviz(){
  colcon build
  source install/setup.bash
  ros2 launch kabot_launcher kabot.launch.py rviz_setup:='True'
}

rebuild(){
  rm -rf install log build
  colcon build
}

show_topics(){
	while true; do clear; ros2 topic list; sleep 5; done
}

show_services(){
  while true; do clear; ros2 service list; sleep 5; done
}

init_agent(){
  cd src
  git clone -b $ROS_DISTRO https://github.com/micro-ROS/micro_ros_setup.git src/micro_ros_setup
  sudo apt update && rosdep update
  rosdep install --from-paths src --ignore-src -y
  sudo apt-get install python3-pip
  colcon build
  source install/local_setup.bash
  ros2 run micro_ros_setup create_agent_ws.sh
  source install/local_setup.bash
  ros2 run micro_ros_setup build_agent.sh
}

run_agent(){
  source install/local_setup.bash
  ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
}

export LC_NUMERIC=en_US.UTF-8
source /opt/ros/foxy/setup.bash

