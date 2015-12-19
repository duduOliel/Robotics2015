#include <iostream>
#include <libplayerc++/playerc++.h>
#include "Map.h"

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

	float mapResolution = 0.025;
	float robotSize = 0.3;

	Map map("roboticLabMap.png",mapResolution, robotSize);

	cout<<"bye from Dudu robot";
}