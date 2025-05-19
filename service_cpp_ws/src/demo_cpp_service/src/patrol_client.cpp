#include <rclcpp/rclcpp.hpp>
#include "chapt4_interface/srv/patrol.hpp"
#include <ctime>
using namespace std::chrono_literals;
using Patrol = chapt4_interface::srv::Patrol;

class PatrolClient : public rclcpp::Node
{
private:
    rclcpp::Client<Patrol>::SharedPtr client_;
    rclcpp::TimerBase::SharedPtr timer_;

public:
    PatrolClient() : Node("PatrolClient")
    {
        client_ = this->create_client<Patrol>("patrol");
        timer_ = this->create_wall_timer(std::chrono::seconds(10), std::bind(&PatrolClient::timer_callback, this));
        srand(time(NULL));
    }

    void timer_callback()
    {
        while (!this->client_->wait_for_service(1s))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
        }
        auto request = std::make_shared<Patrol::Request>();
        request->target_x = rand() % 15;
        request->target_y = rand() % 15;
        RCLCPP_INFO(this->get_logger(), "send request: x=%f, y=%f", request->target_x, request->target_y);
        auto result = client_->async_send_request(request, [&](rclcpp::Client<Patrol>::SharedFuture result) -> void
                                                  { auto response=result.get();
                                                    if(response->result==Patrol::Response::SUCCESS) {
                                                        RCLCPP_INFO(this->get_logger(), "patrol success");
                                                    }
                                                    else{
                                                        RCLCPP_INFO(this->get_logger(), "patrol failed");
                                                    } });
    }
};
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PatrolClient>());
    rclcpp::shutdown();
    return 0;
}