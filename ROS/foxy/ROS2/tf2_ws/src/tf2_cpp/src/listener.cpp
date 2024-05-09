#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "turtlesim/srv/spawn.hpp"

using namespace std::chrono_literals;

class FramListener : public rclcpp::Node
{
    public:
        FramListener() : Node("listener"), is_spawning_srv_ready_(false), is_spawned_(false)
        {
            target_frame_ = this->declare_parameter<std::string>("target_frame", "turtle1");
            
            // 创建侦听器后，它将开始通过网络接收tf2转换
            tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
            tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

            spawner_ = this->create_client<turtlesim::srv::Spawn>("spawn");
            publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle2/cmd_vel", 1);
            timer_ = this->create_wall_timer(1s, std::bind(&FramListener::on_timer, this));
        }

    private:
        // compute transformations
        void on_timer()
        {
            std::string fromFrameRel = target_frame_.c_str();
            std::string toFranmeRel = "turtle2";

            if(is_spawning_srv_ready_)
            {
                if(is_spawned_)
                {
                    geometry_msgs::msg::TransformStamped t;
                    try
                        {t = tf_buffer_->lookupTransform(toFranmeRel, fromFrameRel, tf2::TimePointZero);}
                                                        //（目标框架， 原框架， 转换时刻）
                    catch(const tf2::TransformException & ex)
                    {
                        RCLCPP_INFO(this->get_logger(), "Could not transform %s to %s: %s", 
                                                        toFranmeRel.c_str(), fromFrameRel.c_str(), ex.what());
                        return;
                    }
                    geometry_msgs::msg::Twist msg;
                    static const double scaleRotationRate = 1.0;
                    msg.angular.z = scaleRotationRate * atan2(t.transform.translation.y, t.transform.translation.x);
                    static const double scaleForwardSpeed = 0.5;
                    msg.linear.x = scaleForwardSpeed * sqrt(pow(t.transform.translation.x, 2) + pow(t.transform.translation.y, 2));

                    publisher_->publish(msg);
                }
                else
                {
                    RCLCPP_INFO(this->get_logger(), "Successfully spawned");
                    is_spawned_ = true;    
                }
            }
            else
            {
                if(spawner_->service_is_ready())
                {
                    auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
                    request->x = 4.0;
                    request->y = 2.0;
                    request->theta = 0.0;
                    request->name = "turtle2";

                    using ServiceResponseFuture = rclcpp::Client<turtlesim::srv::Spawn>::SharedFuture;
                    auto response_received_callback = [this](ServiceResponseFuture future)
                                                    {
                                                        auto result = future.get();
                                                        if(strcmp(result->name.c_str(), "turtle2") == 0)
                                                            this->is_spawning_srv_ready_ = true;
                                                        else
                                                            RCLCPP_INFO(this->get_logger(), 
                                                                        "Service callback result mismatch");
                                                    };
                    auto result = spawner_->async_send_request(request, response_received_callback);
                }
                else
                    RCLCPP_INFO(this->get_logger(), "Service is not ready");
            }
        }
    
        bool is_spawning_srv_ready_;   // if the service for spawning turtle is available
        bool is_spawned_;              // if the turtle was successfully spawned
        
        rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawner_{nullptr};
        rclcpp::TimerBase::SharedPtr timer_{nullptr};
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_{nullptr};

        std::shared_ptr<tf2_ros::TransformListener> tf_listener_{nullptr};
        std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
        std::string target_frame_;

};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FramListener>());
    rclcpp::shutdown();
    return 0;
}