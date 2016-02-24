/*
 * TurnToNextPoint.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#include "TurnToNextPoint.h"

TurnToNextPoint::TurnToNextPoint(Robot* robot, vector<Position> & path):Behavior(robot), path(path) {
	// TODO Auto-generated constructor stub

}

bool TurnToNextPoint::startCond(){
	// Robot at first point in path
	return (abs(_robot->getXPos() - path[0].second) > 10 * DISTANCE_TOLERANCE &&
			abs(_robot->getYPos() - path[0].first) > 10 * DISTANCE_TOLERANCE);
}

bool TurnToNextPoint::stopCond(){
// Robot points next position
	if (path[0].first == path[1].first){ // Moving on x axis
		if (path[0].second > path[1].second){ // go west
			return abs(_robot->getYaw() - 180) < 5;
		}else{ // go east
			return abs(_robot->getYaw()) < 5;
		}
	} else { //moving on y axis
		if (path[0].first > path[1].first){ // go south
			return abs(_robot->getYaw() - 270) < 5;
		}else{ // go north
			return abs(_robot->getYaw() - 90) < 5;
		}
	}

	// Remove point to move to next position
	path.erase(path.begin());
}
void TurnToNextPoint::action(){
	// turn robot
	_robot->setSpeed(0,0.2);
}

TurnToNextPoint::~TurnToNextPoint() {
	// TODO Auto-generated destructor stub
}

