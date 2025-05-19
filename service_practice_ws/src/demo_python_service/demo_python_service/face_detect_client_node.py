#客户端
import rclpy
from rclpy.node import Node
import face_recognition
import cv2
from cv_bridge import CvBridge
from chapt4_interface.srv import FaceDetector #导入自定义服务
import time
class FaceDetectClient(Node):
    def __init__(self):
        super().__init__("face_detect_client")
        self.client=self.create_client(FaceDetector, "face_detect")
        self.path="/home/kongdechang/repo/ros2_learn/service_practice_ws/src/demo_python_service/resource/test2.jpg"
        self.cv_img=cv2.imread(self.path)
        self.bridge=CvBridge()



    def send_request(self):
        # 1.判断服务端是不是在线
        while self.client.wait_for_service(timeout_sec=1.0) is False:
            self.get_logger().info("service is not available, waiting again...")
        # 2.创建请求对象Request
        request= FaceDetector.Request()
        img_msg=self.bridge.cv2_to_imgmsg(self.cv_img)
        # 3.发送请求并等待处理完成
        future=self.client.call_async(request)   #发送请求，异步获取结果
        #rclpy.spin_until_future_complete(self, future) #等待服务端返回响应
        future.add_done_callback(self.result_callback) #添加回调函数
    def result_callback(self, future):
        response=future.result()
        self.get_logger().info("人脸数量: %d" % response.number)
        self.show_result(response)

    def show_result(self, response):
        for i in range(response.number):
            top=response.top[i]
            right=response.right[i]
            bottom=response.bottom[i]
            left=response.left[i]
            cv2.rectangle(self.cv_img, (left, top), (right, bottom), (0, 255, 0), 2) 
        cv2.imshow("img",self.cv_img)
        cv2.waitKey(0)

def main(args=None):
    rclpy.init(args=args)
    node=FaceDetectClient()
    node.send_request()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
        