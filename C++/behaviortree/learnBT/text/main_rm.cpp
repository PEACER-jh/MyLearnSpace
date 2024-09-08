#include "../include/remap_port.hpp"
using namespace BT;
// using namespace RemapPorts;

int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<SaySomething>("SaySomething");
    factory.registerNodeType<MoveBaseAction>("MoveBase");
    
    factory.registerBehaviorTreeFromFile("../doc/remap_tree.xml");
    auto tree = factory.createTree("MainTree");
    tree.tickWhileRunning();

    std::cout << "\n------ FIRST BB ---------" << std::endl;
    tree.subtrees[0]->blackboard->debugMessage();
    std::cout << "\n------ SECOND BB --------" << std::endl;
    tree.subtrees[1]->blackboard->debugMessage();

    return 0;
}