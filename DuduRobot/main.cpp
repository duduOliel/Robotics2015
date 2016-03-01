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
	Robot robot("localhost",6665, confXPos, confYPos, yaw, map.getMap().getHeight() * mapResolution);
	robot.read();
	Position robotPos = robot.getRobotPosition();

	STC* stc = new STC(map, robotPos);


	cout<<"Writing output file"<<endl;
	map.drowMapWithCourse("out.png", robotPos);


	vector<Position> path = stc->generatePath();

	////////////////////////////////////////////////////////////////////////////////////////
	robot.read();
	float x = robot.getXPos();
	float y = robot.getYPos();
	float _yaw = robot.getYaw();

	if(abs(robotPos.second - path[0].second) < DISTANCE_TOLERANCE &&
	   abs(robotPos.first - path[0].first) < DISTANCE_TOLERANCE){

		path.erase(path.begin());
	}
	float angle = atan2(path[0].second - y, path[0].first - x);
	cout<<robotPos.first<<" "<<robotPos.second<<" "<<_yaw<<" "<<angle<<endl;
	////////////////////////////////////////////////////////////////////////////////////////

	// create behavior graph
	MoveToNextPoint* nextPoint = new MoveToNextPoint(&robot, &path, map);
	TurnToNextPoint* turn = new TurnToNextPoint(&robot, &path, map);
	StopObsAhead* stop = new StopObsAhead(&robot);


	nextPoint->addNext(turn);
	nextPoint->addNext(stop);

	turn->addNext(nextPoint);

	stop->addNext(nextPoint);

	Manager manager(&robot, turn);
//	Manager manager(&robot, nextPoint);

	manager.run();
/**/


	cout<<"bye from Dudu robot";

	delete conf;
	delete stc;
	delete nextPoint;
	delete turn;
	delete stop;

}
