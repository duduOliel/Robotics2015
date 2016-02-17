#include <iostream>
#include <string>
#include <libplayerc++/playerc++.h>
#include "Map.h"
#include "STC.h"
#include "Config.h"

using namespace std;
using namespace PlayerCc;


int main(){
//	PlayerClient pc("localhost",6665);
//	Position2dProxy pp(&pc,0);
//
//	pc.Read();
//	int initialYPos = pp.GetYPos();
//
////	pp.SetSpeed(0, 0.005);
////	for (int i = 0 ; i < 100 ; i++)
////		pc.Read();
//
//	pp.SetSpeed(1,  0);
//	do{
//		pc.Read();
//		cout << "yPox: " << pp.GetYPos()<<endl;
//	}while (pp.GetYPos() > initialYPos -1);
//	pp.SetSpeed(0,0);
//	cout << pp.GetYaw();
	Config conf("config.file");
	float mapResolution = strtof(conf[Config::MAP_RESOLUTION].c_str(), 0); // 0.025;
	float robotSize = conf.getFloat(Config::ROBOT_SIZE); //strtof(conf[Config::ROBOT_SIZE].c_str(), 0); //0.3;

	Map map("roboticLabMap.png",mapResolution, robotSize);
//	STC stc(map, Position(8.4, 9.7));
	STC stc(map, Position(7, 9));

	cout<<"Writing output file"<<endl;
	map.drowMapWithCourse("out.png", Position(7,9));
	cout<<"bye from Dudu robot";

	vector<Position> path = stc.generatePath();
}
