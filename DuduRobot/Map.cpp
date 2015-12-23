/*
 * Map.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#include "Map.h"

Map* Map::globalmap = NULL;

Map::Map(const char* mapFile, float mapResolution, float robotSize):mapFile(mapFile), map(0,0),inflated(0,0), fineGrid(0,0), grid(0,0) {
	globalmap = this;
	loadImage();
	robotSizeInCells = robotSize/mapResolution;
	inflateGrig();
	createFineGrid();
	createGrid();
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

	globalmap->grid.setVal(row,col, globalmap->fineGrid.checkInRadius(row*2, col*2, 1));

//	if (val){
//		globalmap->grid.setVal(row/2, col/2, true);
//	}
}

void Map::createGrid(){
	cout<< "Creating grid"<<endl;

	grid = BoolGrid(globalmap->fineGrid.getHeight() / 2, globalmap->fineGrid.getWidth() / 2);

//	fineGrid.forEach(setInGrid);
	grid.forEach(setInGrid);
	grid.print();

}
//void convertToGrig();
//void inflateGrig();
//void convertToFineGrid();


Map::~Map() {
	// TODO Auto-generated destructor stub
}

