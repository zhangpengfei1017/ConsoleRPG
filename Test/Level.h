#pragma once
#include "GameObject.h"
#include <vector>
class Level
{
public:
	Level();
	~Level();
	int ID;
	int assetnum;
	int LevelLength;
	int BackgroundId;
	vector<GameObject*> GameObjectInLevel;



};

