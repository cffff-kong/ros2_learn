#include <rclcpp/rclcpp.hpp>
#include "geometry_msgs/msg/twist.hpp"
#include <iostream>
class TurtleCircle : public rclcpp::Node
{
private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_; //需要写消息类型
    rclcpp::TimerBase::SharedPtr timer_;
public:
    TurtleCircle() : Node("turtle_circle")
    {
        RCLCPP_INFO(this->get_logger(),"Turtle Circle Start");
        publisher_=this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10); //第一个值是话题名，话题的消息类型在<>
        timer_=this->create_wall_timer(std::chrono::milliseconds(1000),std::bind(&TurtleCircle::timer_callback,this));
    }
    void timer_callback()
    {
        auto message=geometry_msgs::msg::Twist();
        message.linear.x=2.0;
        message.angular.z=1.0;
        publisher_->publish(message);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<TurtleCircle>());
    rclcpp::shutdown();
    return 0;
}