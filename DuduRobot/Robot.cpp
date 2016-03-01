/*
 * Robot.cpp
 *
 *  Created on: Dec 17, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot(string ip, int port, float xPos, float yPos, float yaw, float worldHeight):worldHeight(worldHeight) {
	pc = new PlayerClient(ip, port);
	lp = new LaserProxy(pc);
	pp = new Position2dProxy(pc);

	// set audometry in meter
	double _xpos = xPos / 100.0;
	double _ypos = (worldHeight - yPos) / 100.0;
//	double _ypos = yPos / 100.0;
	pp->SetOdometry(_xpos, _ypos, yaw);
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

Position Robot::getRobotPosition(){
	return Position(worldHeight - (getYPos() * 100), getXPos()*100);
//	return Position(getYPos() * 100, getXPos()*100);
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

