from launch import LaunchDescription
from launch_ros.actions import Node

tf2_broadcast = Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            arguments=['0', '0', '1', '0', '0', '0', \
                       'launch_world', 'launch_staticturtle']
        )

def generate_launch_description():
    return LaunchDescription([
        tf2_broadcast,
    ])