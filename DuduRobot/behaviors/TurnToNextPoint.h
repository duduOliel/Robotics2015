/*
 * TurnToNextPoint.h
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#ifndef TURNTONEXTPOINT_H_
#define TURNTONEXTPOINT_H_
#include <vector>
#include <math.h>
#include "Behavior.h"

using namespace std;

typedef pair<double, double> Position;

class TurnToNextPoint: public Behavior {
private:
	vector<Position> path;
	double constrainAngle(double x);
public:
	TurnToNextPoint(Robot* robot, vector<Position> & path);

	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();

	virtual ~TurnToNextPoint();
};

#endif /* TURNTONEXTPOINT_H_ */
