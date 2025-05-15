#include <rclcpp/rclcpp.hpp>
#include <status_interfaces/msg/system_status.hpp>

class SysStatusSubscriber : public rclcpp::Node
{
public:
    SysStatusSubscriber() : Node("sys_status_subscriber")
    {
        subscription_ = this->create_subscription<status_interfaces::msg::SystemStatus>(
            "system_status", 10, std::bind(&SysStatusSubscriber::topic_callback, this, std::placeholders::_1));
    }

    void topic_callback(const status_interfaces::msg::SystemStatus::SharedPtr msg)
    {
        auto host_name= msg->host_name;
        auto cpu_percent= msg->cpu_percent;
        auto memory_percent= msg->memory_percent;
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", host_name.c_str());
        RCLCPP_INFO(this->get_logger(), "CPU Usage: '%f'", cpu_percent);
        RCLCPP_INFO(this->get_logger(), "Memory Usage: '%f'", memory_percent);
        RCLCPP_INFO(this->get_logger(), "-------------------------------------");

    }

private:
    rclcpp::Subscription<status_interfaces::msg::SystemStatus>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SysStatusSubscriber>());
    rclcpp::shutdown();
    return 0;
}