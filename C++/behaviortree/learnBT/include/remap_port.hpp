#ifndef _REMAP_PORT_HPP_
#define _REMAP_PORT_HPP_

#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"
#include <chrono>

typedef struct Pose2D
{
    double x, y, z;
}Pose2D;

namespace BT
{
template <> inline Pose2D BT::convertFromString(BT::StringView str)
{
    auto parts = BT::splitString(str, ';');
    if(parts.size() != 3)
        throw BT::RuntimeError("[error] Invalid Pose2D input!");
    else
    {
        Pose2D output;
        output.x = convertFromString<double>(parts[0]);
        output.y = convertFromString<double>(parts[1]);
        output.z = convertFromString<double>(parts[2]);
        return output;
    }
}
// };

// namespace RemapPorts
// {
class MoveBaseAction : public BT::StatefulActionNode
{
public:
    MoveBaseAction(const std::string& name, const BT::NodeConfig& config)
        : StatefulActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return{
            BT::InputPort<Pose2D>("goal")
        };
    }

    BT::NodeStatus onStart() override;
    BT::NodeStatus onRunning() override;
    void onHalted() override;

private:
    Pose2D _goal;
    std::chrono::system_clock::time_point _time;

};

class SaySomething : public BT::SyncActionNode
{
public:
    SaySomething(const std::string& name, const BT::NodeConfig& config)
        : BT::SyncActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return{
            BT::InputPort<std::string>("message")
        };
    }

    BT::NodeStatus tick() override;

private:

};

// }
}

#endif //_REMAP_PORT_HPP_