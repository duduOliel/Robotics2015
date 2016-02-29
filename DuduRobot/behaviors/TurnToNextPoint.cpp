/*
 * TurnToNextPoint.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#include "TurnToNextPoint.h"

TurnToNextPoint::TurnToNextPoint(Robot* robot, vector<Position> & path, Map& map):MapAwareBehavior(robot, map), path(path) {
	// TODO Auto-generated constructor stub

}

double TurnToNextPoint::constrainAngle(double x){
    x = fmod(x,2 * M_PI);
    if (x < 0)
        x += M_PI;
    return x;
}

bool TurnToNextPoint::startCond(){
	// start if robot is not on the same place as next point
//	cout<<"TurnToNextPoint start condition robot pos: "<<_robot->getXPos() - path[0].first<<endl;
	return !(abs(_robot->getXPos() - path[0].first) < DISTANCE_TOLERANCE &&
			abs(_robot->getYPos() - path[0].second) <  DISTANCE_TOLERANCE);
}

bool TurnToNextPoint::stopCond(){
// Robot points next position

	double robotYaw = _robot->getYaw();
//	cout << "Robot Yaw: " << robotYaw;
	robotYaw = constrainAngle(robotYaw);
//	cout << " Constrained robot Yaw: " << robotYaw;


	Position audoPos(_robot->getXPos(), _robot->getYPos());
	//Position robotPos = _map.normalizeRobotPos(audoPos);
//	double angleToNextPoint = constrainAngle(atan2(path[1].second - path[0].second, path[1].first - path[0].second));
		double angleToNextPoint = constrainAngle(atan2(path[0].first - audoPos.first, path[0].second - audoPos.second));
//	cout << "Points ["<<path[0].first <<","<<path[0].second<<"] ["<<audoPos.first <<","<<audoPos.second<<"] angle"<<angleToNextPoint<<endl;


	if (abs(robotYaw - angleToNextPoint) < 0.0523599){ // 3 degrees
//		path.erase(path.begin());
		_robot->setSpeed(0,0);
		return true;
	}
	return false;
}
void TurnToNextPoint::action(){
	// turn robot
	if (!stopCond()){ // don't move if pointing to right angle
		_robot->setSpeed(0,0.2);
	}
}

TurnToNextPoint::~TurnToNextPoint() {
	// TODO Auto-generated destructor stub
}

