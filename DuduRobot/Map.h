/*
 * Map.h
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include "lodepng.h"
#include <vector>
#include <iostream>

using namespace std;

//typedef vector<vector<bool> > Grid;

class Map {
private:
	const char* mapFile;
	Grid map;
	Grid inflated;
	Grid fineGrid;

public:
	Map(const char* mapFile, float mapResolution, float robotSize);
	void printGrig();
	virtual ~Map();
private:
	void loadImage();
	void inflateGrig(unsigned int robotSizeInCells);
	void createFineGrid(unsigned int robotSizeInCells);

//	void convertToGrig();

//	void convertToFineGrid();
};

#endif /* MAP_H_ */
