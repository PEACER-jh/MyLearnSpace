#include "ros/ros.h"
// 从之前创建的srv文件中生成的头文件
#include "beginner_tutorials/AddTwoInts.h"

// 接受srv文件中定义的请求(request)和响应(response)类型,并返回一个布尔值
bool add(beginner_tutorials::AddTwoInts::Request &req,
         beginner_tutorials::AddTwoInts::Response &res)
{
    res.sum = req.a + req.b;
    ROS_INFO("[Server] request: x = %ld, y = %ld", (long int)req.a, (long int)req.b);
    ROS_INFO("[Server] sending back response: sum = %ld", (long int)res.sum);
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "add_two_ints_server");
    ros::NodeHandle n;
    // 服务被创建，并在ROS中宣告
    ros::ServiceServer service_server = n.advertiseService("add_two_ints", add);
    ROS_INFO("[Server] READY TO ADD TWO INTS.");
    ros::spin();

    return 0;
}