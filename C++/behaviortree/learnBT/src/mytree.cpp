#include "../include/mytree.hpp"

using namespace BT;

namespace MyTree
{
    BT::NodeStatus ApproachObject::tick()
    {
        std::cout << "[ ApproachObject " << this->name() << " ]" << std::endl;
        return NodeStatus::SUCCESS;
    }

    BT::NodeStatus CheckBattery()
    {
        std::cout << "[ CheckBattery: OK ]" << std::endl;
        return NodeStatus::SUCCESS;
    }

    BT::NodeStatus GripperInterface::_open()
    {
        isOpen = true;
        std::cout << "[ GripperInterface: open ]" << std::endl;
        return NodeStatus::SUCCESS;
    }

    BT::NodeStatus GripperInterface::_close()
    {
        isOpen = false;
        std::cout << "[ GripperInterface: close ]" << std::endl;
        return NodeStatus::SUCCESS;
    }

}