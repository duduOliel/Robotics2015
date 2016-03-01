/*
 * MoveForward.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#include "MoveToNextPoint.h"

MoveToNextPoint::MoveToNextPoint(Robot *robot, vector<Position>* path, Map& map):MapAwareBehavior(robot, map), path(path) {
	// TODO Auto-generated constructor stub

}

bool MoveToNextPoint::startCond(){
	cout<<(path->empty() ? "path is empty, " : "path is not empty, ")<<(_robot->hasObsticalAhead() ? "Obstical ahead" : "No obstical ahead")<<endl;
	return !path->empty() && !_robot->hasObsticalAhead();

}
bool MoveToNextPoint::stopCond(){
//	Position audoRobotPos(_robot->getXPos(), _robot->getYPos());
	Position audoRobotPos = _robot->getRobotPosition();

	//	Position robotPos = _map.normalizeRobotPos(audoRobotPos);

	if ( _robot->hasObsticalAhead() ||
			(abs(audoRobotPos.first - (*path)[0].first) < DISTANCE_TOLERANCE &&
			 abs(audoRobotPos.second - (*path)[0].second) < DISTANCE_TOLERANCE)){
		_robot->setSpeed(0,0);
		path->erase(path->begin());
		cout<<"Got to ["<<audoRobotPos.first<<","<<audoRobotPos.second<<"] stopping"<<endl;
		return true;
	}

	return false;
}
void MoveToNextPoint::action(){
//	Position audoRobotPos(_robot->getXPos(), _robot->getYPos());
	Position audoRobotPos = _robot->getRobotPosition();
//	Position robotPos = _map.normalizeRobotPos(audoRobotPos);
	cout<< "moving form ["<<audoRobotPos.first<<","<<audoRobotPos.second<<"] to ["<<(*path)[0].first<<","<<(*path)[0].second<<"]"<<endl;
	_robot->setSpeed(0.5,0);

	// Slow down when we get closer
	float distance = sqrt(pow(audoRobotPos.first - (*path)[0].first, 2) + pow(audoRobotPos.second - (*path)[0].second, 2));
	if (distance < 2 * DISTANCE_TOLERANCE){
		_robot->setSpeed(0.1, 0);
	} else {
		_robot->setSpeed(0.5,0);
	}
}

MoveToNextPoint::~MoveToNextPoint() {
	// TODO Auto-generated destructor stub
}

