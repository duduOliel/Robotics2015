/*
 * Grid.h
 *
 *  Created on: Dec 19, 2015
 *      Author: colman
 */

#ifndef GRID_H_
#define GRID_H_

#include <vector>
using namespace std;

class Grid {
public:
	class GridRow {
			friend class Grid;
	private:
		Grid& parent;
		unsigned int row;
	public:
		std::_Bit_reference& operator[](unsigned int col);
	private:
		GridRow(Grid &parent, int row);

		};

private:
	vector<vector<bool>> grid;
	unsigned int height;
	unsigned int width;

public:
	Grid(unsigned int Height, unsigned int width);
	void print();
	GridRow operator[];
	virtual ~Grid();



};

#endif /* GRID_H_ */
