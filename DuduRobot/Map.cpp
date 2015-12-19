/*
 * Map.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#include "Map.h"

Map::Map(const char* mapFile, float mapResolution, float robotSize):mapFile(mapFile) {
	loadImage();



}

void Map::loadImage(){
	cout << "Loading map file: " << mapFile << endl;
	unsigned int mapWidth = 0;
	unsigned int mapHeight = 0;
	vector<unsigned char> image;

	lodepng::decode(image, mapWidth, mapHeight, mapFile);
	cout<<"Image size: " << image.size() << " Map width: " << mapWidth << " Map height: " << mapHeight << endl;

	for (unsigned int i = 0 ; i < mapHeight ; ++i){
		vector<bool> row;
		for (unsigned int j = 0 ; j < mapWidth; ++j){
			row.push_back(image[((i * mapWidth) + j) * 4] == 0);
		}

		map.push_back(row);
	}

	for (unsigned int i = 0 ; i < mapHeight; ++i){
		for (unsigned int j = 0 ; j < mapWidth; ++j){
			cout << (map[i][j] ? "0" : " ");
		}
		cout<<"\n"<<endl;
	}
}
//void convertToGrig();
//void inflateGrig();
//void convertToFineGrid();

Map::~Map() {
	// TODO Auto-generated destructor stub
}

