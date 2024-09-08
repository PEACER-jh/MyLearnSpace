#include "../include/blackboard_port.hpp"

using namespace BT;

namespace BlackboardPort
{
    BT::NodeStatus SaySomething::tick()
    {
        BT::Expected<std::string> msg = getInput<std::string>("message");
        if(!msg)
        {
            throw BT::RuntimeError("missing required input [message]: ", msg.error());
            return NodeStatus::FAILURE;
        }
        std::cout << "[ SaySomething: " << msg.value() << " ]" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus ThinkWhatToSay::tick()
    {
        setOutput("text", "HELLO");
        return BT::NodeStatus::SUCCESS;
    }
}