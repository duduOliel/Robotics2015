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
//	Position audoRobotPos(_robot->getXPos(), _robot->getYPos());
	Position audoRobotPos(_robot->getYPos(), _robot->getXPos());

	//	Position robotPos = _map.normalizeRobotPos(audoRobotPos);

	if ( _robot->hasObsticalAhead() ||
			(abs(audoRobotPos.first - path[0].second) < DISTANCE_TOLERANCE &&
						abs(audoRobotPos.second - path[0].first) < DISTANCE_TOLERANCE)){
		path.erase(path.begin());
		_robot->setSpeed(0,0);
		return true;
	}

	return false;
}
void MoveToNextPoint::action(){
//	Position audoRobotPos(_robot->getXPos(), _robot->getYPos());
	Position audoRobotPos(_robot->getYPos(), _robot->getXPos());
//	Position robotPos = _map.normalizeRobotPos(audoRobotPos);
	cout<< "moving form ["<<audoRobotPos.first<<","<<audoRobotPos.second<<"] to ["<<path[0].second<<","<<path[0].first<<"]"<<endl;
	_robot->setSpeed(0.5,0);
}

MoveToNextPoint::~MoveToNextPoint() {
	// TODO Auto-generated destructor stub
}

