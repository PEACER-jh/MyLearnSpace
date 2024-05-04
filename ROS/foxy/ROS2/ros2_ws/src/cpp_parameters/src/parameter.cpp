#include <chrono>
#include <functional>
#include <string>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;
using namespace rclcpp;

class myParam : public rclcpp::Node
{
public:
    myParam() : Node("my_param")
    {
        this->declare_parameter("my_parameter", "world");
        // 以 1000 毫秒的周期初始化
        timer_ = this->create_wall_timer(1000ms, std::bind(&myParam::timer_callback, this));
    }

    void timer_callback()
    {
        std::string my_param = this->get_parameter("my_parameter").as_string();
        RCLCPP_INFO(this->get_logger(), "[Param] Hello %s", my_param.c_str());
        std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_parameter", "world")};
        this->set_parameters(all_new_parameters);
    }

private:
    rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<myParam>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}