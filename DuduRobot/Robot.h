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

#define SAMPLES  666
#define MIN_DISTANCE_FROM_OBSTICLE  0.20

class Robot {
private:
	PlayerClient *pc;
	Position2dProxy *pp;
	LaserProxy *lp;

public:
	Robot(string ip, int port, float xPos, float yPos, float yaw);
	double getXPos();
	double getYPos();
	double getYaw();
	void read();
	void setSpeed(double linearSpeed, double angularSpeed);
	bool hasObsticalAhead();
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
