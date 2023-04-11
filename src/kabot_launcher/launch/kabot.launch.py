from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    kabot_launcher_dir = get_package_share_directory('kabot_launcher')

    aruco_camera_arg = DeclareLaunchArgument('aruco_camera', default_value='False',
                                    description='Launch usb camera plugin with aruco detection node')
    
    foxglove_setup_arg = DeclareLaunchArgument('foxglove_setup', default_value='False',
                                    description='Launch foxglove software configuration for Kabot')
    
    rviz_setup_arg = DeclareLaunchArgument('rviz_setup', default_value='False',
                                        description='Launch rviz2 software configuration for Kabot')

    aruco_camera = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [kabot_launcher_dir, '/launch/aruco_camera.launch.py']),
        condition=IfCondition(LaunchConfiguration('aruco_camera'))
    )

    foxglove_setup = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [kabot_launcher_dir, '/launch/foxglove.launch.py']),
        condition=IfCondition(LaunchConfiguration('foxglove_setup'))
    )

    kabot_core = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [kabot_launcher_dir, '/launch/kabot_core.launch.py']),
    )

    rviz_setup = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [kabot_launcher_dir, '/launch/rviz.launch.py']),
        condition=IfCondition(LaunchConfiguration('rviz_setup'))
    )

    return LaunchDescription([
        #arguments
        aruco_camera_arg,
        foxglove_setup_arg,
        rviz_setup_arg,

        #launch files
        aruco_camera,
        foxglove_setup,
        kabot_core,
        rviz_setup,
    ])