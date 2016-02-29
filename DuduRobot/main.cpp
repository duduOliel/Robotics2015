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

	Config* conf = new Config("config.file");
	float mapResolution = strtof((*conf)[Config::MAP_RESOLUTION].c_str(), 0); // 0.025;
	float robotSize = conf->getFloat(Config::ROBOT_SIZE); //strtof(conf[Config::ROBOT_SIZE].c_str(), 0); //0.3;
	float confXPos = conf->getFloat(Config::ROBOT_INIITAL_X_POS);
	float confYPos = conf->getFloat(Config::ROBOT_INIITAL_Y_POS);
	float yaw = conf->getFloat(Config::ROBOT_INIITAL_YAW);

	Map map("roboticLabMap.png",mapResolution, robotSize);
	Robot robot("localhost",6665, confXPos, confYPos, yaw);
	robot.read();
	Position audoRobotPos(robot.getXPos(), robot.getYPos());
	Position robotPos = map.normalizeRobotPos(audoRobotPos);
	float xPos = robotPos.first;
	float yPos = robotPos.second;
	Position p(xPos, yPos);
	STC* stc = new STC(map, p);


	cout<<"Writing output file"<<endl;
	map.drowMapWithCourse("out.png", Position(xPos,yPos));


	/*vector<Position> path = stc->generatePath();


	// create behavior graph
	MoveToNextPoint nextPoint(&robot, path, map);
	TurnToNextPoint turn(&robot, path, map);
	StopObsAhead stop(&robot);

	nextPoint.addNext(&turn);
	nextPoint.addNext(&stop);

	turn.addNext(&nextPoint);

	stop.addNext(&nextPoint);

	Manager manager(&robot, &turn);

	manager.run();
/**/
	cout<<"bye from Dudu robot";
}
