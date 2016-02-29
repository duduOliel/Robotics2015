/*
 * Manager.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#include "Manager.h"

#include "Robot.h"

Manager::Manager(Robot *robot, Behavior *startBehavior) : _robot(robot), _currBehavior(startBehavior){

}

void Manager::run()
{
    _robot->read();
    if (!_currBehavior->startCond()) {
        cout << "Cannot start the first behavior" << endl;
        return;
    }
    while (_currBehavior != NULL) {
        _currBehavior->action();
        _robot->read();

        // Update particles...

        if (_currBehavior->stopCond()) {
            _currBehavior = _currBehavior->selectNext();
        }
    }
    cout << "Manager stopped" << endl;
}

Manager::~Manager(){

}
