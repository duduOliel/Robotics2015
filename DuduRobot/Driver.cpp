/*
 * Driver.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: colman
 */

#include "Driver.h"

Driver::Driver(Robot &robot) : robot(robot) {
	// TODO Auto-generated constructor stub

}

void Driver::moveForward(Position targetPos) {
	getCurrentPos();

	robot.setSpeed(linearSpeed, 0);
	while (abs(currPos.first - targetPos.first) > 10 * linearTolerance ||
			abs(currPos.second - targetPos.second) > 10 * linearTolerance) {
		getCurrentPos();
	}

	// slow down before reaching the target
	robot.setSpeed(0.1 * linearSpeed, 0);
	while (abs(currPos.first - targetPos.first) > linearTolerance ||
		abs(currPos.second - targetPos.second) > linearTolerance) {
		getCurrentPos();
	}
}

void Driver::moveRobot(Path path) {
	Position targetPos(2.475, -2.575);
	moveForward(targetPos);
}

void Driver::getCurrentPos() {
	robot.read();
	currPos.first = robot.getXPos();
	currPos.second = robot.getYPos();

	cout << "curr pos: " << currPos.first << "," << currPos.second << endl;
}

Driver::~Driver() {
	// TODO Auto-generated destructor stub
}


