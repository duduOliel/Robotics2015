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
#include "../Map.h"
#include "MapAwareBehavior.h"

using namespace std;

typedef pair<double, double> Position;

class TurnToNextPoint: public MapAwareBehavior {
private:
	vector<Position>* path;
	double constrainAngle(double x);
	float calcNextAngle();
	float calcDirection(float robotYaw, float direction);
public:
	TurnToNextPoint(Robot* robot, vector<Position>* path, Map& map);

	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();

	virtual ~TurnToNextPoint();
};

#endif /* TURNTONEXTPOINT_H_ */
