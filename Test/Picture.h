#pragma once
using namespace std;
class Picture
{
public:
	int Width;
	int Height;
	char* data;
	int id;
	Picture(int w,int h, char* d,int i);
	Picture();
	~Picture();
	
};

