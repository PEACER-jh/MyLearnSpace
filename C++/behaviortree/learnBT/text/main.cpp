#include "../include/mytree.hpp"
#include <iostream>

using namespace BT;
using namespace MyTree;

int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<ApproachObject>("ApproachObject");
    factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));
    GripperInterface gripper;
    factory.registerSimpleAction("OpenGripper",
                                    std::bind(&GripperInterface::_open, &gripper));
    factory.registerSimpleAction("CloseGripper", 
                                    std::bind(&GripperInterface::_close, &gripper));
    // factory.registerSimpleAction("OpenGripper", [&](){ return gripper._open(); });
    // factory.registerSimpleAction("CloseGripper", [&](){ return gripper._close(); });

    auto tree = factory.createTreeFromFile("../doc/my_tree.xml");
    tree.tickExactlyOnce();   
    // tree.tickWhileRunning();                             

    return 0;
}