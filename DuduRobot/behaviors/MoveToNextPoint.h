/*
 * MoveForward.h
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#ifndef MOVEFORWARD_H_
#define MOVEFORWARD_H_

#include <vector>
#include <math.h>
#include "MapAwareBehavior.h"

using namespace std;

typedef pair<double, double> Position;


class MoveToNextPoint: public MapAwareBehavior {

private:
	vector<Position> path;

public:
	MoveToNextPoint(Robot *robot, vector<Position>& path, Map& map);
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	virtual ~MoveToNextPoint();
};

#endif /* MOVEFORWARD_H_ */
