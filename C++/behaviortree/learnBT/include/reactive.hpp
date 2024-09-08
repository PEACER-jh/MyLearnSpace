#ifndef _GENERIC_PORT_HPP_
#define _GENERIC_PORT_HPP_

#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"
#include <chrono>

// namespace chr = std::chrono;

typedef struct Position2D
{
    double x;
    double y;
    // double theta;
}Position2D;

namespace BT
{

template <> inline Position2D BT::convertFromString(StringView str)
{
    auto parts = BT::splitString(str, ';');
    if(parts.size() != 2)
        throw BT::RuntimeError("invalid input");
    else
    {
        Position2D output;
        output.x = convertFromString<double>(parts[0]);
        output.y = convertFromString<double>(parts[1]);
        // output.theta = convertFromString<double>(parts[2]);
        return output;
    }
}

BT::NodeStatus CheckBattery();

class SaySomething : public BT::SyncActionNode
{
public:
    SaySomething(const std::string& name, const BT::NodeConfig& config)
        : BT::SyncActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return {
            BT::InputPort<std::string>("message")
        };
    }

    BT::NodeStatus tick() override;
    // {
    //     BT::Expected<std::string> msg = getInput<std::string>("message");
    //     if(!msg)
    //         throw BT::RuntimeError("missing required input [message]: ", msg.error());
    //         // return NodeStatus::FAILURE;
    //     std::cout << "[ SaySomething: " << msg.value() << " ]" << std::endl;
    //     return BT::NodeStatus::SUCCESS;
    // }

private:

};

class CalculateGoal : public BT::SyncActionNode
{
public:
    CalculateGoal(const std::string& name, const BT::NodeConfig& config) 
        : BT::SyncActionNode(name, config)  
    {}

    static BT::PortsList providedPorts()
    {
        return{
            OutputPort<Position2D>("goal")
        };
    } 

    BT::NodeStatus tick() override;
    // {
    //     Position2D mygoal = {1.1, 2.2};
    //     setOutput<Position2D>("goal", mygoal);
    //     return BT::NodeStatus::SUCCESS;
    // }

private:

};

class PrintTarget : public BT::SyncActionNode
{
public:
    PrintTarget(const std::string& name, const BT::NodeConfig& config)
        : BT::SyncActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        const char* description = "Simply print the goal on console...";
        return{
            InputPort<Position2D>("target", description)
        };
    }

    BT::NodeStatus tick() override;
    // {
    //     auto res = getInput<Position2D>("target");
    //     if(!res)
    //         throw RuntimeError("error reading port [target]: ", res.error());
    //     Position2D target = res.value();
    //     printf("Target positions: [ %.1f, %.1f ]\n", target.x, target.y);
    //     return BT::NodeStatus::SUCCESS;
    // }
private:

};

class MoveBaseAction : public BT::StatefulActionNode
{
public:
    MoveBaseAction(const std::string& name, const BT::NodeConfig& config)
        : StatefulActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return{
            BT::InputPort<Position2D>("goal")
        };
    }

    BT::NodeStatus onStart() override;
    BT::NodeStatus onRunning() override;
    void onHalted() override;

private:
    Position2D _goal;
    std::chrono::system_clock::time_point _completion_time;
};

}

#endif // _GENERIC_PORT_HPP_