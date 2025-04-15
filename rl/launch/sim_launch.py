from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    pkg_share = FindPackageShare('rl_maze_sim')

    return LaunchDescription([
        # Launch RViz with a simple config
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            arguments=['-d', PathJoinSubstitution([pkg_share, 'rviz', 'maze.rviz'])],
            output='screen',
        ),
        # Launch the simulation node
        Node(
            package='rl_maze_sim',
            executable='maze_sim_node.py',
            name='maze_sim_node',
            output='screen',
        ),
    ])