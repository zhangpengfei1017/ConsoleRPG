#include "GameController.h"




GameController::GameController()
{
}


GameController::~GameController()
{
}

void GameController::LevelInit() {
	//lv00 Start
	Level* lv0 = new Level();
	AllLevels.push_back(lv0);
	LoadLevel(0);
	lv0->BackgroundId = 0;
	lv0->LevelLength = 360;
	lv0->ID = 0;

	//lv01 Connecting
	Level* lv1 = new Level();
	AllLevels.push_back(lv1);
	lv1->BackgroundId = 1;
	lv1->LevelLength = 360;
	lv1->ID = 1;

	//lv02 Connect Successfully
	Level* lv2 = new Level();
	AllLevels.push_back(lv2);
	lv2->BackgroundId = 2;
	lv2->LevelLength = 360;
	lv2->ID = 2;

	//lv03 Connect Unsuccessfully
	Level* lv3 = new Level();
	AllLevels.push_back(lv3);
	lv3->BackgroundId = 3;
	lv3->LevelLength = 360;
	lv3->ID = 3;

	//lv04 Waiting in hall
	Level* lv4 = new Level();
	AllLevels.push_back(lv4);
	lv4->BackgroundId = 4;
	lv4->LevelLength = 360;
	lv4->ID = 4;

	//lv05 connecting to the room
	Level* lv5 = new Level();
	AllLevels.push_back(lv5);
	lv5->BackgroundId = 5;
	lv5->LevelLength = 360;
	lv5->ID = 5;

	//lv05 failed to join room
	Level* lv6 = new Level();
	AllLevels.push_back(lv6);
	lv6->BackgroundId = 6;
	lv6->LevelLength = 360;
	lv6->ID = 6;

	//lv06 Waiting in Room
	Level* lv7 = new Level();
	AllLevels.push_back(lv7);
	lv7->BackgroundId = 7;
	lv7->LevelLength = 360;
	lv7->ID = 7;

	//lv08 lost connection
	Level* lv8 = new Level();
	AllLevels.push_back(lv8);
	lv8->BackgroundId = 8;
	lv8->LevelLength = 360;
	lv8->ID = 8;

	//lv09 Game Scene1
	Level* lv9 = new Level();
	AllLevels.push_back(lv9);
	lv9->BackgroundId = 9;
	lv9->LevelLength = 720;
	lv9->ID = 9;
	
}
void GameController::LoadLevel(int lvid) {
	curLevel = AllLevels[lvid];
}





//

vector<Level*> GameController::AllLevels;
Level* GameController::curLevel;