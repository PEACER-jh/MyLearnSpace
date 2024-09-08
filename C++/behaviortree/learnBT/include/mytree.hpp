#ifndef _MY_TREE_HPP_
#define _MY_TREE_HPP_

#include "behaviortree_cpp/behavior_tree.h"
#include "behaviortree_cpp/bt_factory.h"
namespace MyTree
{

class ApproachObject : public BT::SyncActionNode
{
public:
    ApproachObject(const std::string& name) : BT::SyncActionNode(name, {})  {}
    BT::NodeStatus tick() override;
};

BT::NodeStatus CheckBattery();

class GripperInterface
{
public:
    GripperInterface() : isOpen(true) {}
    BT::NodeStatus _open();
    BT::NodeStatus _close();
private:
    bool isOpen;
};

};

#endif // _MY_TREE_HPP_