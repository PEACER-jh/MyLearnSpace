#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "tutorial_interfaces/action/fibonacci.hpp"

namespace ActionCpp
{
    class FibonacciActionClient : public rclcpp::Node
    {
        public:
            using Fibonacci = tutorial_interfaces::action::Fibonacci;
            using GoalHandleFibonacci = rclcpp_action::ClientGoalHandle<Fibonacci>;

            explicit FibonacciActionClient
                    (const rclcpp::NodeOptions & options) : Node("fibonacci_action_client", options)
            {
                //实例化一个action客户端
                this->action_client_ = rclcpp_action::create_client<Fibonacci>(this, "fibonacci");
                //实例化了一个ROS计时器
                this->timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                                                       std::bind(&FibonacciActionClient::send_goal, this));
            }

            void send_goal()
            {
                using namespace std::placeholders;

                this->timer_->cancel();     //取消计时器（只调用一次）
                if(!this->action_client_->wait_for_action_server()) //等待action服务器启动
                {
                    RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
                    rclcpp::shutdown();
                }

                auto goal_msg = Fibonacci::Goal();  //实例化新的 Fibonacci::Goal
                goal_msg.order = 10;
                RCLCPP_INFO(this->get_logger(), "Sending goal");

                auto send_goal_options = rclcpp_action::Client<Fibonacci>::SendGoalOptions();
                send_goal_options.goal_response_callback = std::bind(&FibonacciActionClient::goal_response_callback, this, _1); //响应回调
                send_goal_options.feedback_callback = std::bind(&FibonacciActionClient::feedback_callback, this, _1, _2);       //反馈回调
                send_goal_options.result_callback = std::bind(&FibonacciActionClient::result_callback, this, _1);               //结果回调

                this->action_client_->async_send_goal(goal_msg, send_goal_options);
            }
        
        private:
            rclcpp_action::Client<Fibonacci>::SharedPtr action_client_;
            rclcpp::TimerBase::SharedPtr timer_;

            // 当服务器接收并接受目标时向客户端发送响应
            void goal_response_callback(std::shared_future<GoalHandleFibonacci::SharedPtr> future)
            {
                auto goal_handle = future.get();
                if(!goal_handle)
                    RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
                else    
                    RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
            }

            // 对客户的任何反馈理
            void feedback_callback(GoalHandleFibonacci::SharedPtr,
                                   const std::shared_ptr<const Fibonacci::Feedback> feedback)
            {
                std::stringstream ss;
                ss << "Next number in sequence received: ";
                for(auto number : feedback->partial_sequence)
                    ss << number << " ";

                RCLCPP_INFO(this->get_logger(), ss.str().c_str());
            }

            // 当服务器完成处理后向客户端返回结果
            void result_callback(const GoalHandleFibonacci::WrappedResult & result)
            {
                switch(result.code)
                {
                    case rclcpp_action::ResultCode::SUCCEEDED:
                        break;
                    case rclcpp_action::ResultCode::ABORTED:
                        RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
                        return;
                    case rclcpp_action::ResultCode::CANCELED:
                        RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
                        return;
                    default:
                        RCLCPP_ERROR(this->get_logger(), "Unknow result code");
                        return;
                }
                std::stringstream ss;
                ss << "Result received: ";
                for(auto number : result.result->sequence)
                    ss << number << " ";
                RCLCPP_INFO(this->get_logger(), ss.str().c_str());
                rclcpp::shutdown();
            }

    }; // class FibonacciActionClient

}   // namespace ActionCpp

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(ActionCpp::FibonacciActionClient)