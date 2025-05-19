import rclpy
from rclpy.node import Node
from tf2_ros import TransformBroadcaster 
from geometry_msgs.msg import TransformStamped
from tf_transformations import quaternion_from_euler 
import math

class StaticTFBroadcaster(Node):
    def __init__(self):
        super().__init__('static_tf_broadcaster')
        self.static_broadcaster = TransformBroadcaster(self)
        self.publish_static_tf()

    # publish static tf: base_link -> camera_link
    def publish_static_tf(self):
        transform=TransformStamped()
        transform.header.frame_id = 'base_link'
        transform.header.stamp = self.get_clock().now().to_msg()
        