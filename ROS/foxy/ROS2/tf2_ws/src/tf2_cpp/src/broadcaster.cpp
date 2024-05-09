#include <functional>
#include <memory>
#include <sstream>
#include <string>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "turtlesim/msg/pose.hpp"

class FramePublisher : public rclcpp::Node
{
    public:

        FramePublisher() : Node("broadcaster")
        {
            //获取一个参数，该参数指定了海龟名称
            turtlename_ = this->declare_parameter<std::string>("turtlename", "turtle");
            tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
            std::ostringstream oss;
            oss << "/" << turtlename_.c_str() << "/pose";
            std::string topic_name = oss.str();
            //节点订阅主题，并在每条传入消息上运行函数
            subscription_ = this->create_subscription<turtlesim::msg::Pose>(
                topic_name, 10, std::bind(&FramePublisher::handle_pose, this, std::placeholders::_1));
        }

    private:
        void handle_pose(const std::shared_ptr<turtlesim::msg::Pose> msg)
        {
            geometry_msgs::msg::TransformStamped t;
            t.header.stamp = this->get_clock()->now();  //时间戳
            t.header.frame_id = "world";                //创建的链接的父框架的名称
            t.child_frame_id = turtlename_.c_str();     //创建的链接的子框架的名称

            t.transform.translation.x = msg->x;
            t.transform.translation.y = msg->y;
            t.transform.translation.z = 0.0;
            tf2::Quaternion q;
            q.setRPY(0, 0, msg->theta);
            t.transform.rotation.x = q.x();
            t.transform.rotation.y = q.y();
            t.transform.rotation.z = q.z();
            t.transform.rotation.w = q.w();
            //将变换传递给将负责广播的方法
            tf_broadcaster_->sendTransform(t);
        }

        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
        std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
        std::string turtlename_;

};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FramePublisher>());
    rclcpp::shutdown();
    return 0;
}