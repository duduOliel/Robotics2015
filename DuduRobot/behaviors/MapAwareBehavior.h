/*
 * MapAwareBehavior.h
 *
 *  Created on: Feb 28, 2016
 *      Author: colman
 */

#ifndef MAPAWAREBEHAVIOR_H_
#define MAPAWAREBEHAVIOR_H_

#include "Behavior.h"
#include "../Map.h"

class MapAwareBehavior: public Behavior {
private:
public:
	Map& _map;
	MapAwareBehavior(Robot *robot, Map& map);
	virtual ~MapAwareBehavior();
};

#endif /* MAPAWAREBEHAVIOR_H_ */
