/*
 * MoveForward.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#include "MoveToNextPoint.h"

MoveToNextPoint::MoveToNextPoint(Robot *robot, vector<Position>& path):Behavior(robot), path(path) {
	// TODO Auto-generated constructor stub

}

bool MoveToNextPoint::startCond(){
	return !path.empty() && _robot->hasObsticalAhead();

}
bool MoveToNextPoint::stopCond(){
	return _robot->hasObsticalAhead() ||
			(abs(_robot->getXPos() - path[0].second) > 10 * DISTANCE_TOLERANCE &&
						abs(_robot->getYPos() - path[0].first) > 10 * DISTANCE_TOLERANCE);
}
void MoveToNextPoint::action(){
	_robot->setSpeed(0.5,0);
}

MoveToNextPoint::~MoveToNextPoint() {
	// TODO Auto-generated destructor stub
}

