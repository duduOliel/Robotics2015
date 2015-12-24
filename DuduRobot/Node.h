/*
 * Node.h
 *
 *  Created on: Dec 10, 2015
 *      Author: colman
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>
using namespace std;

class Node {
public:
	vector<Node *> neighborsInTree;
	int row, col;
	bool visited;
	Node(int row, int col);
	virtual ~Node();
};

#endif /* NODE_H_ */
