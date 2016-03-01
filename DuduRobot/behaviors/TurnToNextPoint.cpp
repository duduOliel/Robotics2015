/*
 * TurnToNextPoint.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#include "TurnToNextPoint.h"

TurnToNextPoint::TurnToNextPoint(Robot* robot, vector<Position>* path, Map& map):MapAwareBehavior(robot, map), path(path) {
	// TODO Auto-generated constructor stub

}

double TurnToNextPoint::constrainAngle(double x){
    x = fmod(x,2 * M_PI);
    if (x < 0)
        x += (2 * M_PI);
    return x;
}

float TurnToNextPoint::calcNextAngle(){
	Position audoPos = _robot->getRobotPosition();
	double robotYaw = constrainAngle(_robot->getYaw());
	double angle = constrainAngle(atan2(-((*path)[0].first - audoPos.first), (*path)[0].second - audoPos.second));
//	double angle = constrainAngle(atan2((*path)[0].second - audoPos.second,(*path)[0].first - audoPos.first));

	// Fix angle to move only in straight lines
//	if (angle < M_PI / 4  || angle > (7*M_PI)/4){
//		angle = 0;
//	} else if (angle > M_PI / 4 && angle < (3 * M_PI)/4){
//		angle = M_PI / 2;
//	} else if (angle > (3 * M_PI)/4 && angle < (5 * M_PI)/4){
//		angle = M_PI;
//	} else if (angle > (5 * M_PI)/4 && angle < (7*M_PI)/4){
//		angle = (3 * M_PI)/2;
//	}
	return angle;
}
float lastDirection = -1;
float lastDir = 1;
float TurnToNextPoint::calcDirection(float robotYaw, float direction){
	if (abs(lastDirection - direction) > 0.05){
		cout<< "Switching direction, last: " << lastDirection << " Direction: "<<direction<<endl;
		if (robotYaw > direction){
			lastDirection = direction;
			lastDir  = -1;
		} else {
			lastDirection = direction;
			lastDir = 1;
		}
	}
	return lastDir;
//	if (robotYaw > M_PI && direction > (2 * M_PI) - 0.002){
//		direction = 6.24828; // set just below zero
//	}
	if (abs(robotYaw - direction) > M_PI){
		return -1;
	}
	return 1;
}

bool TurnToNextPoint::startCond(){
	// start if robot is not on the same place as next point
//	cout<<"TurnToNextPoint start condition robot pos: "<<_robot->getXPos() - path[0].first<<endl;
	return true;
	Position robotPos = _robot->getRobotPosition();
	return !(abs(robotPos.first - (*path)[0].first) < DISTANCE_TOLERANCE &&
			abs(robotPos.second - (*path)[0].second) <  DISTANCE_TOLERANCE);
}

bool TurnToNextPoint::stopCond(){
// Robot points next position

	double robotYaw = _robot->getYaw();
	cout << "Robot Yaw: " << robotYaw;
	robotYaw = constrainAngle(robotYaw);
	cout << " Constrained robot Yaw: " << robotYaw <<" " <<robotYaw * 180 /M_PI;


	Position audoPos = _robot->getRobotPosition();
//	double angleToNextPoint = constrainAngle(atan2(path[1].second - path[0].second, path[1].first - path[0].second));
//		double angleToNextPoint = constrainAngle(atan2((*path)[0].first - audoPos.first, (*path)[0].second - audoPos.second));
	double angleToNextPoint = calcNextAngle();
	cout << "Points ["<<(*path)[0].first <<","<<(*path)[0].second<<"] ["<<audoPos.first <<","<<audoPos.second<<"] angle"<<angleToNextPoint<<endl;


	if (abs(robotYaw - angleToNextPoint) < 0.0523599){ // 3 degrees
//		path.erase(path.begin());
		_robot->setSpeed(0,0);
		return true;
	}
	return false;
}
void TurnToNextPoint::action(){
	double robotYaw = constrainAngle(_robot->getYaw());
	double angleToNextPoint = calcNextAngle();
	float direction = calcDirection(robotYaw, angleToNextPoint);

	// turn robot
	if (!stopCond()){ // don't move if pointing to right angle
		if (abs(robotYaw - angleToNextPoint) < 0.2){
			_robot->setSpeed(0,direction * 0.05);
		} else {
			_robot->setSpeed(0,direction * 0.3);
		}
	}
}

TurnToNextPoint::~TurnToNextPoint() {
	// TODO Auto-generated destructor stub
}

