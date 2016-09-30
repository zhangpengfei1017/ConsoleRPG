#include "ScreenItem.h"
#include "Header.h"

ScreenItem::ScreenItem()
{
	PosX = 0;
	PosY = 0;
	Weith = 0;
	Height = 0;
	picture = Picture();
	layer = 0;
}

ScreenItem::ScreenItem(int x, int y, int w, int h, Picture p, int l)
{
	PosX = x;
	PosY = y;
	Weith = w;
	Height = h;
	picture = p;
	layer = l;

}


ScreenItem::~ScreenItem()
{
}
