#include "../include/subtree.hpp"

using namespace SubTree;

int main()
{
    BT::BehaviorTreeFactory factory;
    CrossDoor cross_door;
    cross_door.registerNodes(factory);

    factory.registerBehaviorTreeFromFile("../doc/sub_tree.xml");
    auto tree = factory.createTree("MainTree");
    // BT::printTreeRecursively(tree.rootNode());
    tree.tickWhileRunning();

    return 0;
}