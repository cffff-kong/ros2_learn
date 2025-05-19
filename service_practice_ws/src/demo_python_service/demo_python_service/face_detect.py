
import face_recognition
import cv2
from ament_index_python.packages import get_package_share_directory #获取功能包share目录绝对路径

def main():
   path="/home/kongdechang/repo/ros2_learn/service_practice_ws/src/demo_python_service/resource/test.jpg"
   img=cv2.imread(path)
   face_locations=face_recognition.face_locations(img)
   print("face_locations:",face_locations)
   for top, right, bottom, left in face_locations:
       cv2.rectangle(img,(left,top),(right,bottom),(0,255,0),2)
   cv2.imshow("img",img)
   cv2.waitKey(0)

if __name__ == "__main__":
    main()