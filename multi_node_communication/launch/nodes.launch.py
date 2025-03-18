import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    
    package_dir = get_package_share_directory('multi_node_communication')

    # Set Node Info
    node1 = Node(
        package='multi_node_communication',
        executable='node1',
        name='node1',
        output='screen'
    )

    node2 = Node(
        package='multi_node_communication',
        executable='node2',
        name='node2',
        output='screen'
    )

    node3 = Node(
        package='multi_node_communication',
        executable='node3',
        name='node3',
        output='screen'
    )

    # 创建LaunchDescription对象
    ld = LaunchDescription([
        node1,
        node2,
        node3
    ])

    return ld
