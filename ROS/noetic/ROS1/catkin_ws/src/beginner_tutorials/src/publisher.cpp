#include "ros/ros.h"
// 包括了使用ROS系统中最常见的公共部分所需的全部头文件
#include "std_msgs/String.h"
// 引用了位于std_msgs包里的std_msgs/String消息
#include <sstream>

int main(int argc, char **argv)
{
    // 初始化ROS,使得ROS可以通过命令行进行名称重映射
    ros::init(argc, argv, "talker");
    
    // 进程的节点创建句柄
    // 创建的第一个NodeHandle实际上将执行节点的初始化
    // 最后一个被销毁的NodeHandle将清除节点所使用的任何资源
    ros::NodeHandle n;

    // 告诉主节点将要在chatter话题上发布一个类型为std_msgs/String的消息
    // 第二个参数是发布队列的大小
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    // NodeHandle::advertise()返回一个ros::Publisher对象
    // 1. 它包含一个publish()方法，可以将消息发布到创建它的话题上
    // 2. 当超出范围时，它将自动取消这一宣告操作

    // 指定循环的频率
    ros::Rate loop_rate(10);

    // ros::ok()在以下情况会返回false：
        // 1. 收到SIGINT信号(Ctrl+C)
        // 2. 被另一个同名的节点踢出了网络
        // 3. ros::shutdown()被程序的另一部分调用
        // 4. 所有的ros::NodeHandles都已被销毁
    int count = 0;
    while(ros::ok())
    {
        std_msgs::String msg;
        std::stringstream ss;
        ss << "Hello World " << count;
        // 标准的String消息,它有一个成员:data
        msg.data = ss.str();

        ROS_INFO("[Publisher] %s",msg.data.c_str());

        chatter_pub.publish(msg);

        ros::spinOnce();
        // 使用ros::Rate在剩下的时间内睡眠,以达到10Hz的发布速率
        loop_rate.sleep();
        ++count;
    }
    return 0;
}

