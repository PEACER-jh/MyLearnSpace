#include "../include/multi_xml.hpp"
// #include <filesystem>
// #include <iostream>
// #include <fstream>
// #include <algorithm>
using namespace std;
using namespace MultiXml;

int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<SaySomething>("SaySomething");
    
    factory.registerBehaviorTreeFromFile("../doc/multi/main_tree.xml");
    factory.registerBehaviorTreeFromFile("../doc/multi/subtree_A.xml");
    factory.registerBehaviorTreeFromFile("../doc/multi/subtree_B.xml");

    std::cout << "-------- MainTree tick --------" << std::endl;
    auto main_tree = factory.createTree("MainTree");
    main_tree.tickWhileRunning();

    // /*

    std::cout << "-------- Subtree_A tick --------" << std::endl;
    auto subtree_A = factory.createTree("SubTreeA");
    subtree_A.tickWhileRunning();

    std::cout << "-------- Subtree_B tick --------" << std::endl;
    auto subtree_B = factory.createTree("SubTreeB");
    subtree_B.tickWhileRunning();
    
    // */

    return 0;
}