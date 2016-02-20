/*
 * Map.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#include "Map.h"

Map* Map::globalmap = NULL;

Map::Map(const char* mapFile, float mapResolution, float robotSize):mapFile(mapFile), mapResolution(mapResolution),map(0,0),inflated(0,0), fineGrid(0,0), grid(0,0),graphOnMap(0,0) {
	globalmap = this;
	loadImage();
	robotSizeInCells = robotSize/mapResolution;
	inflateGrig();
	createFineGrid();
	createGrid();


	map.printSizes("map");
	inflated.printSizes("inflated");
	fineGrid.printSizes("fineGrid");
	grid.printSizes("grid");
	graphOnMap.printSizes("proccessedCourse");
}

BoolGrid& Map::getCourseGrid(){
	return grid;
}
void Map::loadImage(){
	cout << "Loading map file: " << mapFile << endl;
	unsigned int mapWidth = 0;
	unsigned int mapHeight = 0;
	vector<unsigned char> image;

	lodepng::decode(image, mapWidth, mapHeight, mapFile);
	cout<<"Image size: " << image.size() << " Map width: " << mapWidth << " Map height: " << mapHeight << endl;

	map = BoolGrid(mapHeight, mapWidth);
	for (unsigned int i = 0 ; i < mapHeight ; i++){
		for (unsigned int  j = 0 ; j < mapWidth ; j++){
			if (image[((i * mapWidth) + j) * 4] == 0){
				map[i][j] =true;
			} else {
				map[i][j] = false;
			}
			//			map[i][j] = image[((i * mapWidth) + j) * 4] == 0;
		}
	}

	map.print();
}

void Map::checkRadiusForInflation(unsigned int row, unsigned int col, bool val){
	globalmap->inflated.setVal(row, col, globalmap->map.checkInRadius(row, col, globalmap->robotSizeInCells / 2));
}

void Map::inflateGrig(){
	cout << "Inflating map" <<endl;

	inflated = BoolGrid(map.getHeight(), map.getWidth());

	inflated.forEach(checkRadiusForInflation);
	inflated.print();
}

//void Map::setInFineGrid(unsigned int row, unsigned int col, bool val){
//	if (val){
//		globalmap->fineGrid.setVal(row/globalmap->robotSizeInCells, col/globalmap->robotSizeInCells, true);
//	}
//}

void Map::setInFineGrid(unsigned int row, unsigned int col, bool val){
	bool isOcupied = globalmap->inflated.checkInRadius((row * globalmap->robotSizeInCells) + globalmap->robotSizeInCells / 2, (col * globalmap->robotSizeInCells) + globalmap->robotSizeInCells / 2, globalmap->robotSizeInCells / 2);
	globalmap->fineGrid.setVal(row,col,isOcupied);
}

void Map::createFineGrid(){

	cout << "Creating fine grid"<<endl;
	unsigned int fineWidth = inflated.getWidth() / robotSizeInCells;
	unsigned int fineHeight = inflated.getHeight() / robotSizeInCells;


	fineGrid = BoolGrid(fineHeight, fineWidth);

//	inflated.forEach(setInFineGrid);
	fineGrid.forEach(setInFineGrid);
	fineGrid.print();
}

void Map::setInGrid(unsigned int row, unsigned int col, bool val){

	//	globalmap->grid.setVal(row,col, globalmap->fineGrid.checkInRadius(row*2, col*2, 1));

	if (val){
		globalmap->grid.setVal(row/2, col/2, true);
	}
}

void Map::createGrid(){
	cout<< "Creating grid"<<endl;

	grid = BoolGrid((globalmap->fineGrid.getHeight() / 2) + 1, (globalmap->fineGrid.getWidth() / 2) + 1);

	//	fineGrid.forEach(setInGrid);
	fineGrid.forEach(setInGrid);
	grid.print();

}

Position Map::pointToCourseGridCell(Position p){
	float factor = mapResolution * robotSizeInCells * 2;
	return Position(round(p.first/ factor), round(p.second /factor));
}

Position Map::pointToFineGridCell(Position p){
	float factor = mapResolution * robotSizeInCells;
	return Position(round(p.first/ factor), round(p.second /factor));
}

Position Map::courseGridCellToMapPoint(Position p){
	// could do it single like but made it verbose for readability
	double x = p.first;
	double y = p.second;

	// To fine grid cell
	x *= 2;
	y *= 2;

	// To map coordinates
	x *= robotSizeInCells;
	y *= robotSizeInCells;

	// to middle of area represented by fine grid
	x += robotSizeInCells;
	y += robotSizeInCells;

	return Position(x, y);
}

Position Map::courseGridCellToWorldPosition(Position p){
	float factor = mapResolution * robotSizeInCells;
	return Position(p.first* factor, p.second *factor);
}

void Map::drowCourseLine(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY){

	Position start = courseGridCellToMapPoint(Position(startX, startY));
	Position end = courseGridCellToMapPoint(Position(endX, endY));

	if (graphOnMap.getHeight() == 0 && graphOnMap.getWidth() == 0){
		graphOnMap = BoolGrid(map.getHeight(), map.getWidth());
	}

	if (start.first != end.first && start.second != end.second){
		throw "No diagonal lines supported";
	}

	cout<<"FromX: " << start.first << " FromY: " << start.second << " ToX: " << end.first << " ToY: " << end.second << endl;

	for (unsigned int i = min(start.first,end.first) ; i <= max(start.first,end.first) ; i++){
		for (unsigned int j = min(start.second,end.second) ; j <= max(start.second, end.second); j++){
			graphOnMap[i][j] = true;
		}
	}

	//	proccessedCourse.print();
}

void Map::drowMapWithCourse(const char* outputFile, Position robotStartingPoing){
	Position convertedStartingPoint(robotStartingPoing.first / mapResolution, robotStartingPoing.second / mapResolution);
	graphOnMap.print();
	vector<unsigned char> image;
	for (unsigned int i = 0 ; i < map.getHeight() ; i++){
		for (unsigned int j = 0 ; j < map.getWidth() ; j++){
			// First if checks if we are in the robot area, then paint robot in blue
			if (abs((int)i - (int)convertedStartingPoint.first) < (int)robotSizeInCells / 2 && abs((int)j - (int)convertedStartingPoint.second) < (int)robotSizeInCells / 2){
				image.push_back(0);
				image.push_back(0);
				image.push_back(255);
				image.push_back(255);
			} else if (graphOnMap[i][j]){ // Add red pixel
				image.push_back(255);
				image.push_back(0);
				image.push_back(0);
				image.push_back(255);
			} else if ((i%(robotSizeInCells*2) == 0)  || (j%(robotSizeInCells*2) == 0)){
				image.push_back(70);
				image.push_back(70);
				image.push_back(0);
				image.push_back(255);
			} else if ((i%(robotSizeInCells) == 0)  || (j%(robotSizeInCells) == 0)){ // Add red pixel
				image.push_back(70);
				image.push_back(120);
				image.push_back(255);
				image.push_back(255);

//			}  else if (!map[i][j]){ // add black pixel
			} else if (!inflated[i][j]){ // add white pixel
				image.push_back(255);
				image.push_back(255);
				image.push_back(255);
				image.push_back(255);
			} else { // add white pixel
				image.push_back(0);
				image.push_back(0);
				image.push_back(0);
				image.push_back(255);
			}
		}
	}

	lodepng::encode(outputFile, image, map.getWidth(), map.getHeight());
}

Position Map::getCounterColockwiseDefaultStep(Position& fineGridCell){
	int row = ((int)fineGridCell.first) % 2;
	int col = ((int)fineGridCell.second) % 2;

	return Position(1 -(row+col), -col+row);

//	if ( x % 2 == 0 && y % 2 == 0){
//		return Position(0,1);
//	} else if(x % 2 == 0 && y % 2 == 1){
//		return Position(1,0);
//	} else if(x % 2 == 1 && y % 2 == 1){
//		return Position(0, -1);
//	} else if(x % 2 == 1 && y % 2 == 0){
//		return Position(-1, 0);
//	}
//
//	// shouldn't get here, all options are covered above
//	cout<<"Error in getCounterCloclwiseDefaultStep";
//	throw "Error in getCounterCloclwiseDefaultStep";
////	return Position(0,0);
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

