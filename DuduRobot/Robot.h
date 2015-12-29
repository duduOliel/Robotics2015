/*
 * Robot.h
 *
 *  Created on: Dec 17, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include <string>
using namespace PlayerCc;
using namespace std;

class Robot {
private:
	PlayerClient *pc;
	Position2dProxy *pp;
	LaserProxy *lp;

public:
	Robot(string ip, int port);
	double getXPos();
	double getYPos();
	double getYaw();
	void read();
	void setSpeed(double linearSpeed, double angularSpeed);
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
