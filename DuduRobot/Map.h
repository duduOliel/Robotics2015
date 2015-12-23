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
#include "Grid.h"

using namespace std;

//typedef vector<vector<bool> > Grid;

class Map {
private:
	static Map *globalmap;
	const char* mapFile;
	BoolGrid map;
	BoolGrid inflated;
	BoolGrid fineGrid;
	BoolGrid grid;
	unsigned int robotSizeInCells = 0;

public:
	Map(const char* mapFile, float mapResolution, float robotSize);
	virtual ~Map();
private:
	void loadImage();
	void inflateGrig();
	void createFineGrid();
	void createGrid();

	static void checkRadiusForInflation(unsigned int row, unsigned int col, bool val);
	static void setInFineGrid(unsigned int row, unsigned int col, bool val);
	static void setInGrid(unsigned int row, unsigned int col, bool val);

//	void convertToGrig();

//	void convertToFineGrid();
};

#endif /* MAP_H_ */
