from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    kabot_agent = Node(
        package='micro_ros_agent',
        executable='micro_ros_agent',
        name='kabot_agent',
        arguments=["udp4", "-p", "8888", "-v6"]
    )

    kabot_app = Node(
        package='kabot_app',
        executable='kabot_app',
    )

    return LaunchDescription([
        kabot_agent,
        kabot_app
    ])