#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"
#include <cstdlib>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "add_two_ints_client");
    if(argc != 3)
    {
        ROS_INFO("[Client] usage: add_two_ints_client X Y");
        return 1;
    }

    ros::NodeHandle n;

    // 为服务创建一个客户端
    ros::ServiceClient service_client = n.serviceClient<beginner_tutorials::AddTwoInts>("add_two_ints");
    
    // 实例化一个自动生成的服务类，并为它的request成员赋值
    // 1. 2个成员变量：request和response
    // 2. 2个类定义：Request和Response
    beginner_tutorials::AddTwoInts srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);
    
    // 如果服务调用成功,call()将返回true,并且srv.response中的值将是有效的
    // 如果调用不成功,则call()将返回false,并且srv.response的值将不可用
    if(service_client.call(srv))
    {
        ROS_INFO("[Client] sum = %ld", (long int)srv.response.sum);
    }
    else
    {
        ROS_ERROR("[Client] FAILED TO CALL service add_two_ints");
        return 1;
    }
    
    return 0;
}