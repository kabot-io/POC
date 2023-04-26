from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    kabot_launcher_dir = get_package_share_directory('kabot_launcher')
    
    foxglove_setup_arg = DeclareLaunchArgument('foxglove', default_value='False',
                                    description='Launch foxglove software configuration for Kabot')
    
    rviz_setup_arg = DeclareLaunchArgument('rviz', default_value='True',
                                        description='Launch rviz2 software configuration for Kabot')
    
    simulation_arg = DeclareLaunchArgument('sim', default_value='True',
                                    description='Launch gazebo simulation')
 
    aruco_camera = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [os.path.join(kabot_launcher_dir, 'launch', 'aruco_camera.launch.py')])
    )

    foxglove_setup = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [os.path.join(kabot_launcher_dir, 'launch', 'foxglove.launch.py')]),
        condition=IfCondition(LaunchConfiguration('foxglove'))
    )

    rviz_setup = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [os.path.join(kabot_launcher_dir, 'launch', 'rviz.launch.py')]),
        condition=IfCondition(LaunchConfiguration('rviz'))
    )

    simulation = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [os.path.join(kabot_launcher_dir, 'launch', 'gazebo.launch.py')]),
        condition=IfCondition(LaunchConfiguration('sim'))
    )

    robot = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [os.path.join(kabot_launcher_dir, 'launch', 'robot.launch.py')]),
    )

    return LaunchDescription([
        #arguments
        foxglove_setup_arg,
        simulation_arg,
        rviz_setup_arg,

        #launch files
        aruco_camera,
        foxglove_setup,
        simulation,
        robot,
        rviz_setup,
    ])