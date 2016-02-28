/*
 * MoveForward.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#include "MoveToNextPoint.h"

MoveToNextPoint::MoveToNextPoint(Robot *robot, vector<Position>& path, Map& map):MapAwareBehavior(robot, map), path(path) {
	// TODO Auto-generated constructor stub

}

bool MoveToNextPoint::startCond(){
	cout<<(path.empty() ? "path is empty, " : "path is not empty, ")<<(_robot->hasObsticalAhead() ? "Obstical ahead" : "No obstical ahead")<<endl;
	return !path.empty() && !_robot->hasObsticalAhead();

}
bool MoveToNextPoint::stopCond(){
	Position audoRobotPos(_robot->getXPos(), _robot->getYPos());
	Position robotPos = _map.normalizeRobotPos(audoRobotPos);

	return _robot->hasObsticalAhead() ||
			(abs(robotPos.second - path[0].second) < 10 * DISTANCE_TOLERANCE &&
						abs(robotPos.first - path[0].first) < 10 * DISTANCE_TOLERANCE);
}
void MoveToNextPoint::action(){
	Position audoRobotPos(_robot->getXPos(), _robot->getYPos());
	Position robotPos = _map.normalizeRobotPos(audoRobotPos);
	cout<< "moving form ["<<robotPos.first<<","<<robotPos.second<<"] to ["<<path[0].first<<","<<path[0].second<<"]"<<endl;
	_robot->setSpeed(0.5,0);
}

MoveToNextPoint::~MoveToNextPoint() {
	// TODO Auto-generated destructor stub
}

