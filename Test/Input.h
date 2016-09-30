#pragma once
class Input
{
public:
	Input();
	~Input();
	static bool GetKey(int vKey);
	static bool GetKeyDown(int vKey);
	static bool IsKeyUp[256];
	static void Init();

};

