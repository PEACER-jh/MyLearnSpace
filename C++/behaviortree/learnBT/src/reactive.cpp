#include "../include/reactive.hpp"

using namespace BT;

namespace BT
{
    BT::NodeStatus CheckBattery()
    {
        std::cout << "[ CheckBattery: OK ]" << std::endl;
        return NodeStatus::SUCCESS;
    }

    BT::NodeStatus SaySomething::tick()
    {
        BT::Expected<std::string> msg = getInput<std::string>("message");
        if(!msg)
        {
            throw BT::RuntimeError("missing required input [message]: ", msg.error());
            return NodeStatus::FAILURE;
        }
        std::cout << "[ SaySomething: " << msg.value() << " ]" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    NodeStatus CalculateGoal::tick()
    {
        Position2D mygoal = {1.1, 2.2};
        setOutput<Position2D>("goal", mygoal);
        return BT::NodeStatus::SUCCESS;
    }

    NodeStatus PrintTarget::tick()
    {
        auto res = getInput<Position2D>("target");
        if(!res)
            throw RuntimeError("error reading port [target]: ", res.error());
        Position2D target = res.value();
        printf("Target positions: [ %.1f, %.1f ]\n", target.x, target.y);
        return BT::NodeStatus::SUCCESS;
    }

    NodeStatus MoveBaseAction::onStart()
    {
        if(!getInput<Position2D>("goal", this->_goal))
            throw BT::RuntimeError("missing required input [goal]");
        printf("[ MoveBase: SEND REQUEST ]. goal: x=%f y=%f \n", _goal.x, _goal.y);
        this->_completion_time = std::chrono::system_clock::now() + std::chrono::milliseconds(220);
        return BT::NodeStatus::RUNNING;
    }

    NodeStatus MoveBaseAction::onRunning()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if(std::chrono::system_clock::now() >= this->_completion_time)
        {
            std::cout << "[ MoveBase : FINISHED ]" << std::endl;
            return BT::NodeStatus::SUCCESS;
        }
        return BT::NodeStatus::RUNNING;
    }

    void MoveBaseAction::onHalted()
    {
        printf("[ MoveBase : ABORTED]");
    }
}