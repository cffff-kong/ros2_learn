#include <rclcpp/rclcpp.hpp>
#include "geometry_msgs/msg/twist.hpp"
#include <turtlesim/msg/pose.hpp>
#include "chapt4_interface/srv/patrol.hpp"  
using Patrol=chapt4_interface::srv::Patrol;

class TurtleControl : public rclcpp::Node
{
private:
rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_; //需要写消息类型
rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
rclcpp::Service<Patrol>::SharedPtr service_;
rclcpp::TimerBase::SharedPtr timer_;
double target_x_=11.0;
double target_y_=1.0;
double kp_=1.0;
double max_speed_=2.0;
public:
    TurtleControl() : Node("turtle_control")
    {
        RCLCPP_INFO(this->get_logger(), "Turtle Control Start");
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10); // 第一个值是话题名，话题的消息类型在<>
        subscription_ = this->create_subscription<turtlesim::msg::Pose>("/turtle1/pose", 10,
                                                                        std::bind(&TurtleControl::timer_callback, this, std::placeholders::_1));
        service_ = this->create_service<Patrol>("patrol", [&](const Patrol::Request::SharedPtr request, Patrol::Response::SharedPtr response) -> void
                                                {
            if (request->target_x > 0 && request->target_y > 0 && request->target_x< 11 && request->target_y < 11)
                {
                    this->target_x_ = request->target_x;
                    this->target_y_ = request->target_y;
                    response->result = Patrol::Response::SUCCESS;
                }
                else
                {
                    response->result = Patrol::Response::FAILURE;
                } });
    }
void timer_callback(const turtlesim::msg::Pose::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "Received message: x=%f, y=%f, theta=%f", msg->x, msg->y, msg->theta);
    // 1. 获取当前的位置
    auto current_x=msg->x;
    auto current_y=msg->y;
    RCLCPP_INFO(this->get_logger(), "Current position: x=%f, y=%f", current_x, current_y);

    //2. 计算当前的位置和目标位置之间的距离
    double distance=sqrt(pow(current_x-target_x_,2)+pow(current_y-target_y_,2));
    double angle=atan2(target_y_-current_y,target_x_-current_x)-msg->theta;

    // 3. 控制
    auto message = geometry_msgs::msg::Twist();
    if (distance > 0.1)
    {
        if (std::fabs(angle) > 0.2)
        {
            message.angular.z = fabs(angle);
        }
        else
        {
            message.linear.x = kp_*distance;
        }
    }
    //4. 限制速度
    if (message.linear.x>max_speed_)
    {
        message.linear.x=max_speed_;
    }
    publisher_->publish(message);
}
};

int main(int argc, char **argv)
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<TurtleControl>());
    rclcpp::shutdown();
    return 0;
}