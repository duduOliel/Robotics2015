/*
 * Grid.cpp
 *
 *  Created on: Dec 19, 2015
 *      Author: colman
 */

#include "Grid.h"
#include <iostream>

using namespace std;

///////////////////////////////////
Grid::GridRow::GridRow(Grid &parent, int row) :	parent(parent),row(row){
}

std::_Bit_reference& Grid::GridRow::operator[](unsigned int col)
{
	return parent.grid[row][col];
}
/////////////////////////////

Grid::Grid(unsigned int height, unsigned int width):height(height), width(width) {
	grid.resize(height);
	for (unsigned int i = 0 ; i < height ; ++i){
		grid[i].resize(width);
		for (unsigned int j = 0 ; j < width ; ++j){
			grid[i][j] = false;
		}
	}

}

void Grid::print(){
	for (unsigned int i = 0 ; i < height ; ++i){
		for (unsigned int j = 0 ; j < width ; ++j){
			cout<<grid[i][j];
		}
		cout<<endl;
	}
}

GridRow Grid::operator[](unsigned int row){
	return new GridRow(this, row);
}

Grid::~Grid() {
	// TODO Auto-generated destructor stub
}

