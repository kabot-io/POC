from launch import LaunchDescription
from launch_ros.actions import Node

from ament_index_python.packages import get_package_share_directory

import os   
import xacro

def generate_launch_description():
    kabot_launcher_dir = get_package_share_directory('kabot_launcher')

    uros_agent = Node(
        package='micro_ros_agent',
        executable='micro_ros_agent',
        name='kabot_agent',
        arguments=["udp4", "-p", "8888", "-v6"]
    )

    xacro_file = os.path.join(kabot_launcher_dir, 'description', 'urdf', 'kabot.urdf.xacro')
    robot_description_config = xacro.process_file(xacro_file)

    params = {'robot_description': robot_description_config.toxml(), 'use_sim_time': True}
    node_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[params]
    )

    return LaunchDescription([
        uros_agent,
        node_robot_state_publisher
    ])