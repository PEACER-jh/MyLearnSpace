#include "../include/generic_port.hpp"

using namespace BT;

int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<CalculateGoal>("CalculateGoal");
    factory.registerNodeType<PrintTarget>("PrintTarget");

    auto tree = factory.createTreeFromFile("../doc/gp_tree.xml");
    tree.tickWhileRunning();

    return 0;
}