#pragma once
#include <vector>
#include "Level.h"

class GameController
{
public:
	GameController();
	~GameController();





	//
	static void LevelInit();
	static vector<Level*> AllLevels;
	static Level* curLevel;


	static void LoadLevel(int lvid);
};

