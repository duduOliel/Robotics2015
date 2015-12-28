/*
 * STC.h
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#ifndef STC_H_
#define STC_H_

#include <vector>
#include <stdexcept>
#include "Node.h"
#include "Map.h"

using namespace std;


class STC {
private:
	static STC* globalstc;
	Position initialRobotPos;
	Map &map;
	vector<vector<Node *> > graph;

	void buildGraph();
	void DFS(Node *node);
	void DFSInternal(Node* node, int rowOffset, int colOffset);
public:
	STC(Map &map, Position initialRobotPos);
	void buildSpanningTree();
	void drawSpanningTree();
	virtual ~STC();
};

#endif /* STC_H_ */
