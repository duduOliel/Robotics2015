/*
 * Behavior.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#include "Behavior.h"

Behavior::Behavior(Robot *robot) : _robot(robot){
}

Behavior::~Behavior() {
}

Behavior *Behavior::addNext(Behavior *beh) {
    _nextBehaviors.push_back(beh);
    return this;
}

Behavior *Behavior::selectNext() {
    for (unsigned int i = 0; i < _nextBehaviors.size(); i++)
    {
        if (_nextBehaviors[i]->startCond())
            return _nextBehaviors[i];
    }
    return NULL;
}
