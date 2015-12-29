/*
 * Driver.h
 *
 *  Created on: Dec 17, 2015
 *      Author: colman
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#include "Robot.h"
#include <vector>

typedef pair<double, double> Position;
typedef vector<Position> Path;

class Driver {
private:
	const double linearTolerance = 0.01;
	const double linearSpeed = 0.6;

	Position currPos;

	Robot &robot;
	void moveForward(Position targetPos);
	void turn(double newDirection);
	void getCurrentPos();
public:
	Driver(Robot &robot);
	void moveRobot(Path path);
	virtual ~Driver();
};

#endif /* DRIVER_H_ */
