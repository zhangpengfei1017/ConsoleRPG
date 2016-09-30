#include "GameObject.h"
#include "ScreenGenerator.h"
#include <algorithm> 
#include "GameController.h"

GameObject::GameObject()
{
}



GameObject::GameObject(int assetid, string name, string tag, int posX, int posY, int posZ, bool ia) {
	this->name = name;
	this->tag = tag;
	this->PosX = posX;
	this->PosY = posY;
	this->PosZ = posZ;
	this->isActive = ia;
	this->assetid=assetid;
}


GameObject::~GameObject()
{
}
void GameObject::MoveTo(int x, int y, int z) {
	this->PosX = x;
	this->PosY = y;
	this->PosZ = z;
	std::sort(GameController::curLevel->GameObjectInLevel.begin(), GameController::curLevel->GameObjectInLevel.end(), ComparePosZ);
}
void GameObject::MoveBy(int x, int y, int z) {
	minX = ScreenGenerator::allasset[this->assetid].Width / 2+10;
	maxX = GameController::curLevel->LevelLength - minX-10;
	this->PosX = this->PosX + x > minX ? this->PosX + x < maxX ? this->PosX + x : maxX : minX;
	this->PosZ = this->PosZ+z<10?10: this->PosZ + z>130?130: this->PosZ + z;
	if (this->PosX -ScreenGenerator::CamPosX< minX) {
		ScreenGenerator::CamMove(x);
	}
	else if (this->PosX - ScreenGenerator::CamPosX > 360 - minX) {
		ScreenGenerator::CamMove(x);
	}
	std::sort(GameController::curLevel->GameObjectInLevel.begin(), GameController::curLevel->GameObjectInLevel.end(), ComparePosZ);
}
void GameObject::Turn() {}


GameObject* GameObject::FindWithName(string n) {
	for (int i = 0; i < GameController::curLevel->GameObjectInLevel.size(); i++) {
		if (GameController::curLevel->GameObjectInLevel[i]->name == n) {
			return(GameController::curLevel->GameObjectInLevel[i]);
		}
	}
	return(nullptr);
}
GameObject GameObject::FindWithTag(string t) {
	return(GameObject());
}
GameObject* GameObject::Instantiate(int x, int y, int z, int assetid, int name, int tag) {
	return(&(GameObject()));
}
void GameObject::Destroy(GameObject &go) {
	
}
bool GameObject::ComparePosZ(GameObject* a, GameObject* b) {
	return(a->PosZ < b->PosZ);
}



vector<GameObject*> GameObject::AllGameObjects;
