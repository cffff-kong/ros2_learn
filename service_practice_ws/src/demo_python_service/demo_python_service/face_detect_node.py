import rclpy
from rclpy.node import Node
import face_recognition
import cv2
from cv_bridge import CvBridge
from chapt4_interface.srv import FaceDetector #导入自定义服务
class FaceDetect(Node):
    def __init__(self):
        super().__init__("face_detect")
        self.get_logger().info("Face detection node has been started")
        self.service=self.create_service(FaceDetector, "face_detect", self.face_detect_callback)
        self.bridge=CvBridge()
    def face_detect_callback(self, request, response):
        if request.img is None:
            path="/home/kongdechang/repo/ros2_learn/service_practice_ws/src/demo_python_service/resource/test.jpg"
            cv_img=cv2.imread(path)
        else:
            cv_img=self.bridge.imgmsg_to_cv2(request.img)
        face_locations=face_recognition.face_locations(cv_img)
        response.number=len(face_locations)
        for top, right, bottom, left in face_locations:
            response.top.append(top)
            response.right.append(right)
            response.bottom.append(bottom)
            response.left.append(left)
            self.get_logger().info("face location: %d, %d, %d, %d" % (top, right, bottom, left))
        return response 

def main(args=None):
    rclpy.init(args=args)
    node = FaceDetect()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

