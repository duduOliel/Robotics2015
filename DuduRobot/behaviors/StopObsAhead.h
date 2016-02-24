/*
 * StopObsAhead.h
 *
 *  Created on: Feb 23, 2016
 *      Author: colman
 */

#ifndef STOPOBSAHEAD_H_
#define STOPOBSAHEAD_H_

#include "Behavior.h"

class StopObsAhead: public Behavior {
public:
	StopObsAhead(Robot* robot);
	virtual bool startCond();
	virtual bool stopCond();
	virtual void action();
	virtual ~StopObsAhead();
};

#endif /* STOPOBSAHEAD_H_ */
