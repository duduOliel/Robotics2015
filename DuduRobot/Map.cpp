/*
 * Map.cpp
 *
 *  Created on: Dec 18, 2015
 *      Author: colman
 */

#include "Map.h"

Map::Map(const char* mapFile, float mapResolution, float robotSize):mapFile(mapFile) {
	loadImage();
	unsigned int robotInCells = robotSize/mapResolution;
	inflateGrig(robotInCells);
	createFineGrid(robotInCells);

}

void Map::loadImage(){
	cout << "Loading map file: " << mapFile << endl;
	unsigned int mapWidth = 0;
	unsigned int mapHeight = 0;
	vector<unsigned char> image;

	lodepng::decode(image, mapWidth, mapHeight, mapFile);
	cout<<"Image size: " << image.size() << " Map width: " << mapWidth << " Map height: " << mapHeight << endl;

	map.resize(mapHeight);
	for (unsigned int i = 0 ; i < mapHeight ; i++){
		map[i].resize(mapWidth);
		for (unsigned int  j = 0 ; j < mapWidth ; j++){
			map[i][j] = image[((i * mapWidth) + j) * 4] == 0;
		}
	}

	// Pring map
	for (unsigned int i = 0 ; i < mapHeight; ++i){
		for (unsigned int j = 0 ; j < mapWidth; ++j){
			cout << (map[i][j] ? "0" : " ");
		}
		cout<<"\n"<<endl;
	}
}

void Map::inflateGrig(unsigned int robotSizeInCells){
	cout << "Inflating map" <<endl;
	unsigned int inflateRadius = robotSizeInCells / 2;

	unsigned int mapWidth = map[0].size();
	unsigned int mapHeight = map.size();


	for (unsigned int i = 0 ; i < mapHeight ; i++){
		vector<bool> row;

		for (unsigned int j = 0 ; j < mapWidth ; j++){
			bool cellValue = false;
			for (unsigned int k = (i < inflateRadius ? 0 : i - inflateRadius) ; k < mapHeight && k < i + inflateRadius ; k++){
				for (unsigned int l = (j < inflateRadius ? 0 : j - inflateRadius) ; l < mapWidth && l < j+inflateRadius; l++){
					if (map[k][l]){
						cellValue = true;
					}
				}
			}
			row.push_back(cellValue);
		}
		inflated.push_back(row);
	}

	// print inflated map
	for (unsigned int i = 0 ; i < mapHeight; i++){
		for (unsigned int j = 0 ; j < mapWidth; j++){
			cout << (inflated[i][j] ? "0" : " ");
		}
		cout<<"\n"<<endl;
	}
}

void Map::createFineGrid(unsigned int robotSizeInCells){
	cout << "Creating fine grid"<<endl;
	unsigned int fineWidth = inflated[0].size() / robotSizeInCells;
	unsigned int fineHeight = inflated.size() / robotSizeInCells;

	fineGrid.resize(fineHeight);
	for (unsigned int i = 0 ; i < fineHeight ; i++){
		fineGrid[i].resize(fineWidth);
		for (int j = 0 ; j < fineWidth ; j++){
			fineGrid[i][j] = false;
		}
	}

	for (unsigned int i = 0 ; i < inflated.size() ; i++){
		for (unsigned int j = 0 ; j < inflated[i].size() ; j++){
			if (inflated[i][j]){
				fineGrid[i/robotSizeInCells][j/robotSizeInCells] = true;
			}
		}
	}
	// print inflated map
	for (unsigned int i = 0 ; i < fineHeight; i++){
		for (unsigned int j = 0 ; j < fineWidth; j++){
			cout << (fineGrid[i][j] ? "0" : " ");
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

