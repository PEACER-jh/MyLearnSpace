#include "../include/remap_port.hpp"
using namespace BT;

namespace BT
{
    NodeStatus MoveBaseAction::onStart()
    {
        if(!getInput<Pose2D>("goal", _goal))
            throw RuntimeError("missing required input [goal]");
        printf("[MoveBase - SEND REQUEST] goal: x=%f, y=%f, z=%f\n", _goal.x, _goal.y, _goal.z);
        this->_time = std::chrono::system_clock::now() + std::chrono::milliseconds(220);
        return NodeStatus::RUNNING;
    }
    NodeStatus MoveBaseAction::onRunning()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if(std::chrono::system_clock::now() >= this->_time)
        {
            std::cout << "[MoveBase - FINISHED]" << std::endl;
            return NodeStatus::SUCCESS;
        }
        return BT::NodeStatus::FAILURE;
    }
    void MoveBaseAction::onHalted()
    {
        printf("[MoveBase - ABORTED]");
    }

    NodeStatus SaySomething::tick()
    {
        BT::Expected<std::string> msg = getInput<std::string>("message");   
        if(!msg)
        {
            throw BT::RuntimeError("missing required input [message]: " ,msg.error());
            return NodeStatus::FAILURE;
        }
        std::cout << "[SaySomething] " << msg.value() << std::endl;
        return NodeStatus::SUCCESS;
    }

}