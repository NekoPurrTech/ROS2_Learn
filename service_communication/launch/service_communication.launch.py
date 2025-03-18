# service_communication.launch.py
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import ExecuteProcess, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

def generate_launch_description():
    # 获取当前软件包路径
    package_dir = get_package_share_directory('service_communication')

    # 定义服务节点
    server_node = Node(
        package='service_communication',
        executable='add_two_ints_server',
        name='add_two_ints_server',
        output='screen'
    )

    # 定义客户端节点1
    client1_node = Node(
        package='service_communication',
        executable='add_two_ints_client',
        name='add_two_ints_client1',
        output='screen'
    )

    # 定义客户端节点2
    client2_node = Node(
        package='service_communication',
        executable='add_two_ints_client2',
        name='add_two_ints_client2',
        output='screen'
    )

    # 返回启动描述
    return LaunchDescription([
        server_node,
        client1_node,
        client2_node
    ])