#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"        //使用ROS2系统中最常见的部分
#include "std_msgs/msg/string.hpp"  //使用ROS2系统中的消息类型

using namespace std::chrono_literals;
using namespace std;
using namespace rclcpp;

// 通过继承来创建节点类
class myPublisher : public rclcpp::Node
{
public:
    //发布者使用消息类型、主题名称和所需的队列大小进行初始化
    myPublisher() : Node("my_publisher"), count_(0)
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("my_topic", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&myPublisher::timer_callback, this));
    }

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_; //发布者
    rclcpp::TimerBase::SharedPtr timer_;    //计时器

    size_t count_ = 0;
    //设置消息数据并实际发布消息
    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = "Hello ROS2 foxy!" + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "[Publisher] %s", message.data.c_str());
        publisher_->publish(message);
    }

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<myPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
