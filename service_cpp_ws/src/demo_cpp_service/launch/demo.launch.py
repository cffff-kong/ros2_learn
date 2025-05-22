import launch
import launch_ros

def generate_launch_description():

    action_node_turtlesim_node=launch_ros.actions.Node(
        package='turtlesim',
        executable='turtlesim_node',
        output='screen', # 输出到屏幕
    )
    action_node_turtle_control=launch_ros.actions.Node(
        package='demo_cpp_service',
        executable='turtle_control_node',
        output='screen', # 输出到屏幕
    )
    action_node_patrol_client=launch_ros.actions.Node(
        package='demo_cpp_service',
        executable='patrol_client_node',
        output='screen', # 输出到屏幕
    )
    return launch.LaunchDescription([
        # actions动作
      action_node_turtlesim_node,
      action_node_turtle_control,
    ])