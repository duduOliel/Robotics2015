/*
 * STC.cpp
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#include "STC.h"

STC* STC::globalstc;

STC::STC(Map &map, Position initialRobotPos) : map(map), initialRobotPos(initialRobotPos) {
	STC::globalstc = this;

	// init graph


	buildGraph();
	Position initialPosInCourseGrid = map.pointToCourseGridCell(initialRobotPos);
	cout<<"Graph"<<endl;
	for (unsigned int i = 0 ; i < graph.size() ; i++){
		for (unsigned int j = 0 ; j < graph[i].size() ; j++){
			if (i == initialPosInCourseGrid.first && j == initialPosInCourseGrid.second){
				cout <<((graph[i][j] != NULL)  ? "+" : "-");
			} else {
				cout<<((graph[i][j] != NULL)  ? "0" : " ");
			}
		}
		cout<<endl;
	}

	cout << "DFS start on: " << initialPosInCourseGrid.first<< "x" <<initialPosInCourseGrid.second <<endl;
	DFS(graph[initialPosInCourseGrid.first][initialPosInCourseGrid.second]);  //  calculate node by start pointd

	cout<<"After DFS"<<endl;
	for (unsigned int i = 0 ; i < graph.size() ; i++){
		for (unsigned int j = 0 ; j < graph[i].size() ; j++){
			cout<<((graph[i][j] != NULL) && (graph[i][j]->neighborsInTree.size() > 0) ? graph[i][j]->neighborsInTree.size() : 0);
		}
		cout<<endl;
	}

	writeCourseToMap(graph[initialPosInCourseGrid.first][initialPosInCourseGrid.second]);
}

void STC::buildGraph(){
	graph.resize(map.getCourseGrid().getHeight());
	for(unsigned int i = 0 ; i < map.getCourseGrid().getHeight() ; i++){
		graph[i].resize(map.getCourseGrid().getWidth());

		for (unsigned int j = 0 ; j < map.getCourseGrid().getWidth() ; j++){
			if (!map.getCourseGrid()[i][j]){
				graph[i][j] = new Node(i,j);
			} else {
				graph[i][j] = NULL;
			}
		}
	}
}

void STC::DFS(Node *node){
	node->visited = true;
	DFSInternal(node,-1 , 0); // north
	DFSInternal(node, 0	,-1); // west
	DFSInternal(node, 1	, 0); // south
	DFSInternal(node, 0	, 1); // east
}

void STC::DFSInternal(Node* node, int rowOffset, int colOffset){
	unsigned int r = node->row + rowOffset;
	unsigned int c = node->col + colOffset;

	Node* other;
	try{
		other = graph.at(r).at(c);
	}catch (const std::out_of_range& err) {
		return; // index is out of range, might happen if we are on the edges of the grid
	}

	if (graph[r][c] != NULL && !graph[r][c]->visited ){
		graph[r][c]->visited = true;
		node->neighborsInTree.push_back(graph[r][c]);

		DFS(graph[r][c]);
	}
}

void STC::writeCourseToMap(Node* node){
	if (node != NULL){
		for (unsigned int i = 0 ; i < node->neighborsInTree.size() ; i++){
			map.drowCourseLine(node->row, node->col, node->neighborsInTree[i]->row, node->neighborsInTree[i]->col);
			writeCourseToMap(node->neighborsInTree[i]);
		}
	}
}

void STC::followGraph(Node *node, Position& robotPos, vector<Position>& waypoints){
	if (node->neighborsInTree.size() == 0) {// U turn
		for (int i = 0 ; i < 3 ; i++){ // Add 3 steps for the robot withing the same course grid cell
			Position nextStep = map.getCounterColockwiseDefaultStep(robotPos);
			moveBotAddWaypoint(robotPos, waypoints, nextStep.first, nextStep.second);
		}
	}

	for (unsigned int i = 0 ; i < node->neighborsInTree.size() ; i++){
		Node* currNeighbor = node->neighborsInTree[i];
		int dx = currNeighbor->row - node->row;
		int dy = currNeighbor->col - node->col;


		Position nextStep = map.getCounterColockwiseDefaultStep(robotPos);
		// if robot next counter clock wise step is similar to next neighbor, move in that direction
		if (dx == nextStep.first && dy == nextStep.second){
			moveBotAddWaypoint(robotPos, waypoints, dx, dy);
		}



	}
}

void STC::moveBotAddWaypoint(Position& robotPos, vector<Position>& waypoints, int dx, int dy){
	robotPos.first = robotPos.first + dx;
	robotPos.second = robotPos.second + dy;
	waypoints.push_back(*new Position(robotPos.first, robotPos.second)); // create new object for waypoints list
}

vector<Position> STC::generatePath(Position initialRobotPos){
	vector<Position> retval;
	// get robot initial position on fine grid
	Position robotPos = map.pointToFineGridCell(initialRobotPos);
	Position firstCoursGridCell = map.pointToCourseGridCell(initialRobotPos);

	retval.push_back(*new Position(robotPos.first, robotPos.second));
	followGraph(graph[robotPos.first][firstCoursGridCell.second], robotPos, retval);

	return retval;
}

STC::~STC(){

}
