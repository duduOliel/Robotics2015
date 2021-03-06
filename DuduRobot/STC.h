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

typedef vector<Position> Path();

class STC {
private:
	static STC* globalstc;
	Map &map;
	Position initialRobotPos;
	vector<vector<Node *> > graph;

	void buildGraph();
	void DFS(Node *node);
	void DFSInternal(Node* node, int rowOffset, int colOffset);
	void writeCourseToMap(Node* node);
	void followGraph(Node *node, Position& robotPos, vector<Position>& waypoints);
	void handleSingleNode(Node *node, Node* nextNode,Position& robotPos, vector<Position>& waypoints);
	void moveBotAddWaypoint(Position& robotPos, vector<Position>& waypoints, int dx, int dy);
	bool isNextStepInSameNode(const Position currPos,const Position nextStep);
	vector<Position> joinPath(const vector<Position> path);
	void printPath(const vector<Position> path);
public:
	STC(Map &map, Position initialRobotPos);
	void buildSpanningTree();
	void drawSpanningTree();
	vector<Position> generatePath();
	virtual ~STC();
};

#endif /* STC_H_ */
