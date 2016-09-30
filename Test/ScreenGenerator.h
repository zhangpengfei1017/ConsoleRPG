#pragma once
#include "Picture.h"
#include <windows.h>
#include <vector>
#include "GameObject.h"
using namespace std;
class ScreenGenerator
{
public:
	ScreenGenerator();
	~ScreenGenerator();	
	static Picture* allasset;
	static bool IsFirstFrame;
	static CHAR_INFO cBuffer[115200];
	static int nextASIlayer;
	static char FullScreen[57600];
	static vector<GameObject> activeGO;
	static int CamPosX;

	//
	static void init();
	static CHAR_INFO* NextScreen();
	static void LoadAssets(int num);
	static int WorldPosToScreenPos_X(int WX, int LevelScroll);
	static int WorldPosToScreenPos_Y(int WY, int WZ);
	static void CamMove(int x);
	
};

