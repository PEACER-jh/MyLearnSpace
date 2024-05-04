#include <memory>
// 包依赖项
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using namespace rclcpp;

// 从request中添加两个整数，并为response提供总和
void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request>  request,
               std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
{
    response->sum = request->a + request->b;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "[Server] Incoming request: a = %ld /t b = %ld", request->a, request->b);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "[Server] Sending back response: %ld", (long int)response->sum);
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service_ = node->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", &add);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "[Server] Ready to add: \n");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}