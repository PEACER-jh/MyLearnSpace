#include "ros/ros.h"
#include "std_msgs/String.h"

// 回调函数,当有新消息到达chatter话题时它就会被调用
void ChatterCallback(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("[Subscriber] %s",msg->data.c_str());
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle n;

    // 通过主节点订阅chatter话题
    // 每当有新消息到达时,ROS将调用chatterCallback()函数
    // 第二个参数是队列大小,以防我们处理消息的速度不够快
    ros::Subscriber chatter_sub = n.subscribe("chatter", 1000, ChatterCallback);
    
    // 启动了一个自循环,它会尽可能快地调用消息回调函数
    ros::spin();
    return 0;

}