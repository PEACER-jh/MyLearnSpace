#include <memory>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/static_transform_broadcaster.h"

class StaticFramePublisher : public rclcpp::Node
{
    public:
        explicit StaticFramePublisher(char *transformation[]) : Node("static_broadcaster")
        {
            tf_static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
            this->make_transforms(transformation);  //启动时发送一个静态转换
        }

    private:
        void make_transforms(char *transformation[])
        {
            //时间戳
            geometry_msgs::msg::TransformStamped t;
            t.header.stamp = this->get_clock()->now();  
            //创建的链接的父框架的名称
            t.header.frame_id = "world";
            //创建的链接的子帧的名称
            t.child_frame_id = transformation[1];
            
            //平移和旋转
            t.transform.translation.x = atof(transformation[2]);
            t.transform.translation.y = atof(transformation[3]);
            t.transform.translation.z = atof(transformation[4]);
            tf2::Quaternion q;
            q.setRPY(atof(transformation[5]), atof(transformation[6]), atof(transformation[7]));
            t.transform.rotation.x = q.x();
            t.transform.rotation.y = q.y();
            t.transform.rotation.z = q.z();
            t.transform.rotation.w = q.w();

            //广播静态转换
            tf_static_broadcaster_->sendTransform(t);
        }

        std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;

};

int main(int argc, char *argv[])
{
    auto logger = rclcpp::get_logger("logger");

    if(argc != 8)
    {
        RCLCPP_INFO(logger, 
            "Invalid number of parameters\nusage: "
            "$ ros2 run tf2_cpp static_broadcaster "
            "child_frame_name x y z roll pitch yaw");
        return 1;
    }

    if(strcmp(argv[1], "world") == 0)
    {
        RCLCPP_INFO(logger, "Your static turrle name cannot be 'world'");
        return 1;
    }

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<StaticFramePublisher>(argv));
    rclcpp::shutdown();

    return 0;
}