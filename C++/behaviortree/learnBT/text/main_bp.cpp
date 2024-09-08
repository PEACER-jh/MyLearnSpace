#include "../include/blackboard_port.hpp"

using namespace BlackboardPort;

int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<SaySomething>("SaySomething");
    factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

    auto tree = factory.createTreeFromFile("../doc/bp_tree.xml");
    tree.tickExactlyOnce();

    return 0;
}