# 订阅
import espeakng
import rclpy
import rclpy.logging
from rclpy.node import Node
from example_interfaces.msg import String
from queue import Queue 
import threading
import time
class TopicSubscriber(Node):
    def __init__(self):
        super().__init__('novel_sub')
        self.get_logger().info('NodeTopic has been created')
        self.novels_queue=Queue()
        self.novels_subscriber=self.create_subscription(String, 'novel', self.novel_callback, 10)
        self.speech_method=threading.Thread(target=self.speak_method)
        self.speech_method.start()
    def novel_callback(self, msg): #其实是String msg，作为参数接收发布者的数据
        self.novels_queue.put(msg.data)

    def speak_method(self):
        speaker=espeakng.Speaker()
        speaker.voice='zh'
        while rclpy.ok():
            if self.novels_queue.qsize()>0:
                text=self.novels_queue.get()
                self.get_logger().info(f"接收消息：{text}")
                #self.get_logger().info(f"接收消息：{text}")
                #speaker.say(text)
                #speaker.wait() #等待语音播放完成
            else:
                #让当前线程休眠
                time.sleep(1)
def main(args=None):
    rclpy.init(args=args)
    node = TopicSubscriber()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()