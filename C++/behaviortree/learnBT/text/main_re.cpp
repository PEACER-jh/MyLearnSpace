#include "../include/reactive.hpp"

using namespace BT;

int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerSimpleCondition("BatteryOK", std::bind(CheckBattery));
    factory.registerNodeType<MoveBaseAction>("MoveBase");
    factory.registerNodeType<SaySomething>("SaySomething");

    // auto tree = factory.createTreeFromFile("../doc/react_tree1.xml");
    auto tree = factory.createTreeFromFile("../doc/react_tree2.xml");
    std::cout << "---ticking" << std::endl;
    auto status = tree.tickOnce();
    std::cout << "---status: " << BT::toStr(status) << std::endl << std::endl;

    while(status == NodeStatus::RUNNING)
    {
        tree.sleep(std::chrono::milliseconds(100));
        std::cout << "---ticking" << std::endl;
        status = tree.tickOnce();
        std::cout << "---status: " << BT::toStr(status) << std::endl << std::endl;
    }

    return 0;
}