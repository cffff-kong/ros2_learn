#include <rclcpp/rclcpp.hpp>

class HelloWorld : public rclcpp::Node
{
public:
    HelloWorld() : Node("node_cpp")
    {
        while (rclcpp::ok())
        {
            RCLCPP_INFO(this->get_logger(), "Hello World!");
            sleep(1);
        }
    }
};
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<HelloWorld>());
    rclcpp::shutdown();
    return 0;
}