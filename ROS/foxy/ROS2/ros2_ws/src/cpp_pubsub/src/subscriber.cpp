#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;
using namespace std;
using namespace rclcpp;

class mySubscriber : public Node
{
public:
    mySubscriber() : Node("my_subscriber")
    {
        //发布者和订阅者使用的主题名称和消息类型必须匹配,才能允许他们进行通信
        subscriber_ = this->create_subscription<std_msgs::msg::String>
            ("my_topic", 10, std::bind(&mySubscriber::topic_callback, this, _1));
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
    void topic_callback(const std_msgs::msg::String::SharedPtr message) const
    {
        RCLCPP_INFO(this->get_logger(), "[Subscriber] %s", message->data.c_str());
    }

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<mySubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}