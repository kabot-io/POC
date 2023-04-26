from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.conditions import UnlessCondition
from launch.substitutions import LaunchConfiguration

from ament_index_python.packages import get_package_share_directory

import os   
import xacro
import random
import string

def generate_launch_description():
    kabot_launcher_dir = get_package_share_directory('kabot_launcher')

    simulation_param = LaunchConfiguration('sim')
    simulation_arg = DeclareLaunchArgument('sim', default_value='False',
                                description='Launch gazebo simulation')

    uros_agent = Node(
        package='micro_ros_agent',
        executable='micro_ros_agent',
        name='kabot_agent',
        arguments=["udp4", "-p", "8888", "-v6"],
        condition=UnlessCondition(LaunchConfiguration('sim'))
    )

    kabot_xacro_file_path = os.path.join(kabot_launcher_dir, 'description', 'urdf', 'kabot.urdf.xacro')
    robot_description_config = xacro.process_file(kabot_xacro_file_path)
    kabot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_description_config.toxml(),
                     'use_sim_time': simulation_param}]
    )

    robot_name = 'kabot_'.join(random.choices(string.ascii_lowercase, k=3))
    spawn_kabot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-topic', 'robot_description',
                   '-entity', robot_name],
        output='screen',
        condition=IfCondition(LaunchConfiguration('sim'))
    )

    return LaunchDescription([
        simulation_arg,
        uros_agent,
        kabot_state_publisher,
        spawn_kabot
    ])