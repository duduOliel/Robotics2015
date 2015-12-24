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
//	DFS(graph[map.])  //  calculate node by start point
}

void STC::buildGraph(){
	graph.resize(map.getCourseGrid().getHeight());
	for(unsigned int i = 0 ; i < map.getCourseGrid().getHeight() ; i++){
		graph[i].resize(map.getCourseGrid().getWidth());
		for (unsigned int j = 0 ; j < map.getCourseGrid().getWidth() ; i++){
			if (map.getCourseGrid()[i][j]){
				graph[i][j] = new Node(i,j);
			} else {
				graph[i][j] = NULL;
			}
		}
	}
}

void STC::DFS(Node *node){
	unsigned int r = node->row;
	unsigned int c = node->col;

	DFSInternal(node,-1 , 0); // north
	DFSInternal(node, 0	, 1); // east
	DFSInternal(node, 1	, 0); // south
	DFSInternal(node, 0	,-1); //west

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

STC::~STC() {
	for (unsigned int i = 0 ; i < graph.size() ; i++){
		for (unsigned int j = 0 ; j < graph[i].size() ; j++){
			delete graph[i][j];
		}
	}
}
