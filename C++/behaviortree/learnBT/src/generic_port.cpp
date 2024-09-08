#include "../include/generic_port.hpp"

using namespace BT;

namespace BT
{
    NodeStatus CalculateGoal::tick()
    {
        Position2D mygoal = {1.1, 2.2};
        setOutput<Position2D>("goal", mygoal);
        return BT::NodeStatus::SUCCESS;
    }

    NodeStatus PrintTarget::tick()
    {
        auto res = getInput<Position2D>("target");
        if(!res)
            throw RuntimeError("error reading port [target]: ", res.error());
        Position2D target = res.value();
        printf("Target positions: [ %.1f, %.1f ]\n", target.x, target.y);
        return BT::NodeStatus::SUCCESS;
    }

}