#include <chrono>
#include <cstdlib>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;
using namespace rclcpp;

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    if(argc != 3)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "[Client] ERROR: please give two ints");
        return -1;
    }

    // 创建节点，然后为该节点创建客户端
    std::shared_ptr<Node> node = rclcpp::Node::make_shared("add_two_ints_client");
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_ = node->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");

    // 创建请求
    auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
    request->a = atoll(argv[1]);
    request->b = atoll(argv[2]);

    // 为客户端提供 1 秒钟的时间来搜索网络中的服务节点
    while(!client_->wait_for_service(1s))
    {
        if(!rclcpp::ok())
        {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "[Client] Interrupted while waiting for the service. Exiting.");
            return -2;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "[Client] Service not available, waiting again...");
    }

    // 客户端发送其请求
    auto result = client_->async_send_request(request);
    if(rclcpp::spin_until_future_complete(node,result) == rclcpp::FutureReturnCode::SUCCESS)
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "[Client] sum = %ld", result.get()->sum);
    else
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "[Client] Fail to call the server!");

    rclcpp::shutdown();
    return 0;
}