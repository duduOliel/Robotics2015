/*
 * Config.h
 *
 *  Created on: Jan 2, 2016
 *      Author: colman
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>

using namespace std;


class Config {
public:
	enum Keys{
			ROBOT_SIZE,
			ROBOT_INIITAL_X_POS,
			ROBOT_INIITAL_Y_POS,
			ROBOT_INIITAL_YAW,
			MAP_RESOLUTION
		};
private:
	map<string, string> conf;

public:
	Config(string const filename);
	string operator[](Keys key);
	unsigned int getUInt(Keys key);
	float getFloat(Keys key);

	virtual ~Config();
};

#endif /* CONFIG_H_ */
