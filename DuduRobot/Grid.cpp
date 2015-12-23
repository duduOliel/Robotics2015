/*
 * Grid.cpp
 *
 *  Created on: Dec 19, 2015
 *      Author: colman
 */

#include "Grid.h"
#include <iostream>

using namespace std;

BoolGrid::BoolGrid(unsigned int height, unsigned int width):height(height), width(width) {
	grid.resize(height);
	for (unsigned int i = 0 ; i < height ; ++i){
		grid[i].resize(width);
		for (unsigned int j = 0 ; j < width ; ++j){
			grid[i][j] = false;
		}
	}

}

void BoolGrid::print(){
	for (unsigned int i = 0 ; i < height ; ++i){
		for (unsigned int j = 0 ; j < width ; ++j){
			if (grid[i][j]){
				cout<<"0";
			} else {
				cout <<" ";
			}
//			cout<< (grid[i][j] ? "0" : " ");
		}
		cout<<endl;
	}
}

void BoolGrid::forEach(void (*func)(unsigned int row, unsigned int col, bool val)){
	for (unsigned int i = 0 ; i < height ; ++i){
		for (unsigned int j = 0 ; j < width ; ++j){
			func(i,j,grid[i][j]);
		}
		cout<<endl;
	}
}

bool BoolGrid::checkInRadius(unsigned int row, unsigned int col, unsigned int radius){
	for (unsigned int i = (row < radius ? 0 : row - radius) ; i < height && i < row + radius ; i++){
		for (unsigned int j = (col < radius ? 0 : col - radius) ; j < width && j < col + radius; j++){
			if (grid[i][j]){
				return true;
			}
		}
	}
	return false;
}

void BoolGrid::setVal(unsigned int row, unsigned int col, bool val){
	grid[row][col] = val;
}

BoolGrid::~BoolGrid() {
	// TODO Auto-generated destructor stub
}

