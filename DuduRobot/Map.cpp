/*
 * Map.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#include "Map.h"

Map* Map::globalmap = NULL;

Map::Map(const char* mapFile, float mapResolution, float robotSize):mapFile(mapFile), mapResolution(mapResolution),map(0,0),inflated(0,0), fineGrid(0,0), grid(0,0),proccessedCourse(0,0) {
	globalmap = this;
	loadImage();
	robotSizeInCells = robotSize/mapResolution;
	inflateGrig();
	createFineGrid();
	createGrid();
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

void Map::setInFineGrid(unsigned int row, unsigned int col, bool val){
	if (val){
		globalmap->fineGrid.setVal(row/globalmap->robotSizeInCells, col/globalmap->robotSizeInCells, true);
	}
}

void Map::createFineGrid(){

	cout << "Creating fine grid"<<endl;
	unsigned int fineWidth = inflated.getWidth() / robotSizeInCells;
	unsigned int fineHeight = inflated.getHeight() / robotSizeInCells;


	fineGrid = BoolGrid(fineHeight, fineWidth);

	inflated.forEach(setInFineGrid);
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

void Map::drowCourseLine(unsigned int startX, unsigned int startY, unsigned int endX, unsigned int endY){
	float factor = robotSizeInCells * 2;
	unsigned int mapStartX = startX * factor;
	unsigned int mapStartY = startY * factor;
	unsigned int mapEndX = endX * factor;
	unsigned int mapEndY = endY * factor;

	if (proccessedCourse.getHeight() == 0 && proccessedCourse.getWidth() == 0){
		proccessedCourse = BoolGrid(map.getHeight(), map.getWidth());
	}

	if (mapStartX != mapEndX && mapStartY != mapEndY){
		throw "No diagonal lines supported";
	}

	cout<<"FromX: " << mapStartX << " FromY: " << mapStartY << " ToX: " << mapEndX << " ToY: " << mapEndY << endl;

	for (unsigned int i = min(mapStartX,mapEndX) ; i <= max(mapStartX,mapEndX) ; i++){
		for (unsigned int j = min(mapStartY,mapEndY) ; j <= max(mapStartY, mapEndY); j++){
			proccessedCourse[i][j] = true;
		}
	}

	//	proccessedCourse.print();
}

void Map::drowMapWithCourse(const char* outputFile){
	proccessedCourse.print();
	vector<unsigned char> image;
	for (unsigned int i = 0 ; i < map.getHeight() ; i++){
		for (unsigned int j = 0 ; j < map.getWidth() ; j++){
			if (proccessedCourse[i][j]){ // Add red pixel
				image.push_back(255);
				image.push_back(0);
				image.push_back(0);
				image.push_back(255);
			} else if (!map[i][j]){ // add white pixel
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

//void convertToGrig();
//void inflateGrig();
//void convertToFineGrid();


Map::~Map() {
	// TODO Auto-generated destructor stub
}

