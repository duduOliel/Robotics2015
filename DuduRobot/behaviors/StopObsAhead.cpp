/*
 * StopObsAhead.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#include "StopObsAhead.h"

StopObsAhead::StopObsAhead(Robot* robot):Behavior(robot) {
	// TODO Auto-generated constructor stub

}

bool StopObsAhead::startCond(){
	return _robot->hasObsticalAhead();
}

bool StopObsAhead::stopCond(){
	return !_robot->hasObsticalAhead();
}

void StopObsAhead::action(){
	cout<<"Obstical ahead, please remove"<<endl;
	for (int i = 0 ; i < 20 ; i++){
		_robot->read();
	}
}

StopObsAhead::~StopObsAhead() {
	// TODO Auto-generated destructor stub
}

