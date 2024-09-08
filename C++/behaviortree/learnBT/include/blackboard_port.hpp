#ifndef _BLACKBOARD_PORT_HPP_
#define _BLACKBOARD_PORT_HPP_

#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"

namespace BlackboardPort
{
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

class ThinkWhatToSay : public BT::SyncActionNode
{
public:
    ThinkWhatToSay(const std::string& name, const BT::NodeConfig& config)
        : BT::SyncActionNode(name, config)
    {}

    static BT::PortsList providedPorts()
    {
        return{
            BT::OutputPort<std::string>("text")
        };
    }

    BT::NodeStatus tick() override;
    // {
    //     setOutput("text", "HELLO");
    //     return BT::NodeStatus::SUCCESS;
    // }

private:


};

}

#endif // _BLACKBOARD_PORT_HPP_