/*
 * Robot.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(string ip, int port, float xPos, float yPos, float yaw) {
	pc = new PlayerClient(ip, port);
	lp = new LaserProxy(pc);
	pp = new Position2dProxy(pc);

	pp->SetOdometry(xPos, yPos, yaw);
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
	for (int i = 0 ; i < 50 ; i++){
		if ((*lp)[(SAMPLES / 2) + i] < MIN_DISTANCE_FROM_OBSTICLE || (*lp)[(SAMPLES / 2) - i] < MIN_DISTANCE_FROM_OBSTICLE){
			cout<<"obstical at distance: " << (*lp)[(SAMPLES / 2) + i]<<" or " << (*lp)[(SAMPLES / 2) - i]<<endl;
			return true;
		}
	}
	return false;
}

Robot::~Robot() {
	delete pp;
	delete lp;
	delete pc;
}

