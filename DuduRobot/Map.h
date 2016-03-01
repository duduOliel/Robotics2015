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
#include <math.h>
#include <stdlib.h>
#include "Grid.h"

using namespace std;

//typedef vector<vector<bool> > Grid;
typedef pair<double, double> Position;


class Map {
private:
	static Map *globalmap;
	const char* mapFile;
	float mapResolution;
	BoolGrid map;
	BoolGrid inflated;
	BoolGrid fineGrid;
	BoolGrid grid;
	BoolGrid graphOnMap;
	unsigned int robotSizeInCells;

public:
	Map(const char* mapFile, float mapResolution, float robotSize);
	BoolGrid& getCourseGrid();
	BoolGrid& getMap();
	Position pointToCourseGridCell(Position p);
	Position pointToFineGridCell(Position p);
	Position courseGridCellToMapPoint(Position p);
	Position courseGridCellToWorldPosition(Position p);
	Position fineGridToWorldPosition(Position p);
	void drowCourseLine(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY);
	void drowMapWithCourse(const char* outputFile, Position robotStartingPoing);
	Position getCounterColockwiseDefaultStep(Position& rotobPos);
	Position normalizeRobotPos(Position& p);
	virtual ~Map();
private:
	void loadImage();
	void inflateGrig();
	void createFineGrid();
	void createGrid();


	static void checkRadiusForInflation(unsigned int row, unsigned int col, bool val);
	static void setInFineGrid(unsigned int row, unsigned int col, bool val);
	static void setInGrid(unsigned int row, unsigned int col, bool val);
};

#endif /* MAP_H_ */
