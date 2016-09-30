#pragma once

#include "Picture.h"

using namespace std;
class ScreenItem
{
public:
	int PosX;
	int PosY;
	int Weith;
	int Height;
	int layer;
	Picture picture;
	ScreenItem();
	ScreenItem(int x, int y, int w, int h, Picture p, int l);
	~ScreenItem();
};

