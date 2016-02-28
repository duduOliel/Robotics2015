/*
 * Robot.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(string ip, int port) {
	pc = new PlayerClient(ip, port);
	lp = new LaserProxy(pc);
	pp = new Position2dProxy(pc);

	pc->Read();
	double x = pp->GetXPos(), y = pp->GetYPos();

	pp->SetOdometry(2.175, -2.875, M_PI / 4);
	double x1 = pp->GetXPos(), y1 = pp->GetYPos();
}

double Robot::getXPos() {
	return pp->GetXPos();
}

double Robot::getYPos() {
	return pp->GetYPos();
}

double Robot::getYaw() {
	return pp->GetYaw();
}

void Robot::read() {
	pc->Read();
}

void Robot::setSpeed(double linearSpeed, double angularSpeed) {
	pp->SetSpeed(linearSpeed, angularSpeed);
}

bool Robot::hasObsticalAhead(){
	return (*lp)[ 2] < MIN_DISTANCE_FROM_OBSTICLE;
}

Robot::~Robot() {
	delete pp;
	delete lp;
	delete pc;
}

