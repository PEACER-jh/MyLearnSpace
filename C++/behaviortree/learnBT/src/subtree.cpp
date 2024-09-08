#include "../include/subtree.hpp"
#include <iostream>

using namespace std;
using namespace BT;

namespace SubTree
{
    void CrossDoor::registerNodes(BT::BehaviorTreeFactory& factory)
    {
        factory.registerSimpleCondition("IsDoorClosed", std::bind(&CrossDoor::isDoorClosed, this));
        factory.registerSimpleAction("PassThroughDoor", std::bind(&CrossDoor::passThroughDoor, this));
        factory.registerSimpleAction("OpenDoor", std::bind(&CrossDoor::openDoor, this));
        factory.registerSimpleAction("PickLock", std::bind(&CrossDoor::pickLock, this));
        factory.registerSimpleCondition("SmashDoor", std::bind(&CrossDoor::smashDoor, this));
    }

    BT::NodeStatus CrossDoor::isDoorClosed()
    {
        if(this->_door_open != true)
        {
            cout << "Door is closed" << endl;
            return BT::NodeStatus::SUCCESS;
        }
        cout << "Door is open" << endl;
        return BT::NodeStatus::FAILURE;
    }

    BT::NodeStatus CrossDoor::passThroughDoor()
    {
        if(this->_door_open == true)
        {
            cout << "Passing through door" << endl;
            return BT::NodeStatus::SUCCESS;
        }
        cout << "Fail to pass through door" << endl;
        return BT::NodeStatus::FAILURE;
    }

    BT::NodeStatus CrossDoor::pickLock()
    {
        if(this->_pick_attempts <= 3)
        {
            this->_pick_attempts += 1;
            cout << "Picking lock: " << this->_pick_attempts << endl;
            return BT::NodeStatus::FAILURE;
            // return BT::NodeStatus::RUNNING;
        }
        cout << "The door is unlocked" << endl;
        this->_door_locked = false;
        this->_pick_attempts = 0;
        this->_door_open = true;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus CrossDoor::openDoor()
    {
        if(this->_door_locked == true)
        {
            cout << "The door is locked" << endl;
            return BT::NodeStatus::FAILURE;
        }
        cout << "The door is open" << endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus CrossDoor::smashDoor()
    {
        cout << "Smashing door" << endl;
        this->_door_locked = false;
        this->_door_open = true;
        this->_pick_attempts = 0;
        return BT::NodeStatus::SUCCESS;
    }

}