#pragma once
#include "Picture.h"
#include <string>
#include <vector>
class GameObject
{
public:
	GameObject();
	GameObject(int assetid, string name, string tag, int posX,int posY,int posZ,bool ia);
	~GameObject();
	int PosX;
	int PosY;
	int PosZ;
	int Direction=1;
	bool isActive;
	int minX;
	int maxX;
	string name="";
	string tag="";
	int assetid;
	void MoveTo(int x, int y, int z);
	void MoveBy(int x, int y, int z);
	void Turn();


	//static 
	static vector<GameObject*> AllGameObjects;
	static GameObject* FindWithName(string n);
	static GameObject FindWithTag(string t);
	static GameObject* Instantiate(int x, int y, int z, int assetid, int name, int tag);
	static void Destroy(GameObject &go);
	static bool ComparePosZ(GameObject* a, GameObject* b);
};

