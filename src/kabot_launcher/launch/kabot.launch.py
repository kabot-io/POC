from launch import LaunchDescription
from launch_ros.actions import Node

from ament_index_python.packages import get_package_share_directory

import os

def generate_launch_description():

    kabot_launcher_dir = get_package_share_directory('kabot_launcher')

    kabot_agent = Node(
        package='micro_ros_agent',
        executable='micro_ros_agent',
        name='kabot_agent',
        arguments=["udp4", "-p", "8888", "-v6"]
    )

    usb_camera_node = Node(
        package='usb_cam',
        executable='usb_cam_node_exe',
        name='usb_camera_node',
        parameters=[os.path.join(kabot_launcher_dir, 'config','camera_params.yaml')]
    )

    camera_tranform_publisher = Node(
        package="tf2_ros",
        node_executable="static_transform_publisher",
        arguments=["0","0","0","0","0","0","world","camera"],
        output="screen"
    )

    aruco_detection_node = Node(
        package='ros2_aruco',
        executable='aruco_node',
        name='aruco_detection_node',
        emulate_tty=True,
        parameters=[{'image_topic':'/image_raw'},
                    {'camera_info_topic':'/camera_info'},
                    {'camera_frame':'camera'},
                    # {'marker_size':'.0260'}
                    ],
    )

    kabot_app = Node(
        package='kabot_app',
        executable='kabot_app',
    )

    rviz2 = Node(
        package='rviz2',
        executable='rviz2',
        arguments=['-d', [os.path.join(kabot_launcher_dir, 'config', 'rviz.rviz')]]
    )

    return LaunchDescription([
        kabot_agent,
        usb_camera_node,
        camera_tranform_publisher,
        aruco_detection_node,
        # kabot_app,
        rviz2,
    ])