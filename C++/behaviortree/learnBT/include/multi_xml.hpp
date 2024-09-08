#ifndef _MULTI_XML_HPP_
#define _MULTI_XML_HPP_

#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"

namespace MultiXml
{
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
};
}


#endif // _MULTI_XML_HPP_