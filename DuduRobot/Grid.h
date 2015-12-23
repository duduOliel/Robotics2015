/*
 * Grid.h
 *
 *  Created on: Dec 19, 2015
 *      Author: colman
 */

#ifndef GRID_H_
#define GRID_H_

#include <iostream>
#include <vector>
using namespace std;

class BoolGrid {

private:
	vector<vector<bool> > grid;
	unsigned int height;
	unsigned int width;

public:
	unsigned int getHeight(){return height;}
	unsigned int getWidth(){return width;}


	BoolGrid(unsigned int height, unsigned int width);
	void print();
	vector<bool>& operator[](unsigned int row) {return grid[row];}
	void forEach(void (*func)(unsigned int row, unsigned int col, bool val));
	void setVal(unsigned int row, unsigned int col, bool val);
	bool checkInRadius(unsigned int row, unsigned int col, unsigned int radius);
	virtual ~BoolGrid();
};

#endif /* GRID_H_ */
