/*
 * Config.cpp
 *
 *  Created on: Jan 2, 2016
 *      Author: colman
 */

#include "Config.h"

Config::Config(string const filename):conf() {
	ifstream file(filename.c_str());

	string line;
	while(std::getline(file, line)){
		if (line.length() == 0){
			continue;
		}

		int delimiterPosition = line.find("=");
		string key = line.substr(0, delimiterPosition);
		string value = line.substr(delimiterPosition+1);
		conf[key] = value;
	}


}

string Config::operator[](Keys key){
	string fileValues[] = {"robotSize", "robotInitialXpos", "robotInitialYpos", "robotInitialYaw", "mapResolution"};
	return conf[fileValues[key]];
}

unsigned int Config::getUInt(Keys key){
	return strtol((*this)[key].c_str(), 0, 10);
}

float Config::getFloat(Keys key){
	return strtof((*this)[key].c_str(), 0);
}


Config::~Config() {
	// TODO Auto-generated destructor stub
}

