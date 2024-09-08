#include "../include/multi_xml.hpp"

namespace MultiXml
{
    BT::NodeStatus SaySomething::tick()
    {
        BT::Expected<std::string> msg = getInput<std::string>("message");   
        if(!msg)
        {
            throw BT::RuntimeError("missing required input [message]: " ,msg.error());
            return BT::NodeStatus::FAILURE;
        }
        std::cout << "[SaySomething] " << msg.value() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
}