#include "Picture.h"







Picture::Picture(int w, int h, char* d, int i)
{
	Width = w;
	Height = h;
	data = d;
	id = i;
}
Picture::Picture(){
	Width = 0;
	Height = 0;
	data = nullptr;
	id = 0;
}
Picture::~Picture()
{
}
