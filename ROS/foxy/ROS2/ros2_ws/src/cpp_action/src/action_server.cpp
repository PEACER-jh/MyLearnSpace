#include <functional>
#include <memory>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

#include "tutorial_interfaces/action/fibonacci.hpp"

namespace ActionCpp
{
    class FibonacciActionServer : public rclcpp::Node
    {   
        public:
            using Fibonacci = tutorial_interfaces::action::Fibonacci;
            using GoalHandFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;
            
            explicit FibonacciActionServer
                    (const rclcpp::NodeOptions & options = rclcpp::NodeOptions()) : Node("fibonacci_action_server", options)
            {
                using namespace std::placeholders;
                // 实例化了一个action服务器
                this->action_server_ = rclcpp_action::create_server<Fibonacci>(this,
                                            "fibonacci",
                                            std::bind(&FibonacciActionServer::handle_goal, this, _1, _2),   // 处理目标的回调函数
                                            std::bind(&FibonacciActionServer::handle_cancel, this, _1),     // 处理取消的回调函数
                                            std::bind(&FibonacciActionServer::handle_accepted, this, _1));  // 处理目标接受的回调函数
            }

        private:
            rclcpp_action::Server<Fibonacci>::SharedPtr action_server_;

            // 接受所有目标
            rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID & uuid,
                                                    std::shared_ptr<const Fibonacci::Goal> goal)
            {
                RCLCPP_INFO(this->get_logger(), "Received goal request with order %d", goal->order);
                (void)uuid;
                return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
            }
            
            // 处理取消的回调
            rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandFibonacci> goal_handle)
            {
                RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
                (void)goal_handle;
                return rclcpp_action::CancelResponse::ACCEPT;
            }
            
            // 接受一个新目标并开始处理
            void handle_accepted(const std::shared_ptr<GoalHandFibonacci> goal_handle)
            {
                using namespace std::placeholders;
                //生成一个线程来执行实际工作并快速返回
                std::thread{std::bind(&FibonacciActionServer::execute, this, _1), goal_handle}.detach();
            }
            // 处理和更新都在新线程的方法
            void execute(const std::shared_ptr<GoalHandFibonacci> goal_handle)
            {
                RCLCPP_INFO(this->get_logger(), "Executing gaol");
                rclcpp::Rate loop_rate(1);
                const auto goal = goal_handle->get_goal();
                auto feedback = std::make_shared<Fibonacci::Feedback>();
                auto & sequence = feedback->partial_sequence;
                sequence.push_back(0);
                sequence.push_back(1);
                auto result = std::make_shared<Fibonacci::Result>();

                for(int i = 1; (i <= goal->order) && rclcpp::ok(); ++i)
                {
                    if(goal_handle->is_canceling())
                    {
                        result->sequence = sequence;
                        goal_handle->canceled(result);
                        RCLCPP_INFO(this->get_logger(), "Goal canceled");
                        return;
                    }  
                    sequence.push_back(sequence[i] + sequence[i-1]);
                    goal_handle->publish_feedback(feedback);
                    RCLCPP_INFO(this->get_logger(), "Publish feedback");

                    loop_rate.sleep();
                }

                if(rclcpp::ok())
                {
                    result->sequence = sequence;
                    goal_handle->succeed(result);
                    RCLCPP_INFO(this->get_logger(), "Goal succeeded");
                }
            }

    };  // class FibonacciActionServer
    
}   // namespace ActionCpp

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(ActionCpp::FibonacciActionServer)