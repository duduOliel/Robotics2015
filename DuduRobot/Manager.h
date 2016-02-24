/*
 * Manager.h
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "Robot.h"
#include "behaviors/Behavior.h"

class Manager {
private:
    Robot *_robot;
    Behavior *_currBehavior;

public:
    Manager(Robot *robot, Behavior *startBehavior);
    void run();
    virtual ~Manager();
};

#endif /* MANAGER_H_ */
