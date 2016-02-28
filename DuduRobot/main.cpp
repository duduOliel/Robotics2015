#include <iostream>
#include <string>
#include <libplayerc++/playerc++.h>
#include "Map.h"
#include "STC.h"
#include "Config.h"
#include "Robot.h"
#include "behaviors/MoveToNextPoint.h"
#include "behaviors/StopObsAhead.h"
#include "behaviors/TurnToNextPoint.h"
#include "Manager.h"

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
	float xPos = conf.getFloat(Config::ROBOT_INIITAL_X_POS);
	float yPos = conf.getFloat(Config::ROBOT_INIITAL_Y_POS);
//	STC stc(map, Position(7, 9));
	STC stc(map, Position(xPos, yPos));


	cout<<"Writing output file"<<endl;
	map.drowMapWithCourse("out.png", Position(xPos,yPos));


	vector<Position> path = stc.generatePath();


	// create behavior graph
	Robot robot("localhost",6665);
	MoveToNextPoint nextPoint(&robot, path);
	TurnToNextPoint turn(&robot, path);
	StopObsAhead stop(&robot);

	nextPoint.addNext(&turn);
	nextPoint.addNext(&stop);

	turn.addNext(&nextPoint);

	stop.addNext(&nextPoint);

	Manager manager(&robot, &turn);

	manager.run();

	cout<<"bye from Dudu robot";
}
