# 发布
import rclpy
from rclpy.node import Node
import requests
from example_interfaces.msg import String
from queue import Queue

class TopicPublisher(Node):
    def __init__(self):
        super().__init__('novel_pub')
        self.get_logger().info('NodeTopic has been created')
        self.novel_queue=Queue() #创建队列
        self.novel_publisher_=self.create_publisher(String, 'novel', 10) #创建发布者
        self.create_timer(1, self.timer_callback)
    def timer_callback(self):
        if self.novel_queue.qsize()>0:
            line=self.novel_queue.get()
            msg=String()
            msg.data=line
            self.novel_publisher_.publish(msg)
            self.get_logger().info(f"发布消息：{msg.data}")

    def download(self,url):
        response=requests.get(url)
        response.encoding = 'utf-8'
        text=response.text         
        self.get_logger().info(f"开始下载 {url},{len(text)}")
        for line in text.split():
            self.novel_queue.put(line)
def main(args=None):
    rclpy.init(args=args)
    node = TopicPublisher()
    node.download('http://0.0.0.0:8000/novel1.txt')
   

    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()