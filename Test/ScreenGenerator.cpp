#include "ScreenGenerator.h"
#include <windows.h>
#include <fstream>
#include <string>
#include "GameController.h"
using namespace std;
ScreenGenerator::ScreenGenerator()
{

}
ScreenGenerator::~ScreenGenerator()
{
}
void ScreenGenerator::init() {
	IsFirstFrame = true;
	nextASIlayer = 0;
	CamPosX = 0;
	ScreenGenerator::LoadAssets(10);
}
void ScreenGenerator::LoadAssets(int num) {
	allasset = new Picture[num];
	for (int i = 0; i < num; i++) {//read every txt file to load image
		string str = to_string(i) + ".txt";
		char* mdata;
		vector<char> txtdata;
		ifstream fin(str, ios::in);
		int o = 0;
		while (fin) {
			char data;
			fin >> data;
			txtdata.push_back(data);
			o++;
		}
		fin.close();
		int w1, w2, w3, h1, h2, h3;
		h1 = (int)txtdata[txtdata.size() - 4] - 48;
		h2 = (int)txtdata[txtdata.size() - 3] - 48;
		h3 = (int)txtdata[txtdata.size() - 2] - 48;
		w1 = (int)txtdata[txtdata.size() - 7] - 48;
		w2 = (int)txtdata[txtdata.size() - 6] - 48;
		w3 = (int)txtdata[txtdata.size() - 5] - 48;
		for (int pop = 0; pop < 6; pop++) {
			txtdata.pop_back();
		}
		mdata = new char[txtdata.size() - 1];
		for (size_t j = 0; j < txtdata.size() - 1; j++) {
			mdata[j] = txtdata[j];
		}
		Picture asset = Picture((w1 * 100 + w2 * 10 + w3), (h1 * 100 + h2 * 10 + h3), mdata, i);
		//Sprite asset = Sprite(360, 160, mdata, i);
		allasset[i] = asset;
	}

	//

}
CHAR_INFO* ScreenGenerator::NextScreen() {
	activeGO.clear();
	if (IsFirstFrame) {
		for (int i = 0; i < 115200; i++) {
			cBuffer[i].Char.AsciiChar = ' ';
			cBuffer[i].Attributes = NULL;
		}
		IsFirstFrame = false;
		return cBuffer;
	}//
	//

	for (int layer = 0; layer < 1; layer++) {
		//遍历currentActive的sprite，计算其绘制矩形，循环绘制/
		//计算绘制矩形
		int beginx = 0;
		int beginy = 0;
		int endx = 360;
		int endy = 160;
		for (int l = beginy; l < endy; l++) {
			for (int r = beginx; r < endx; r++) {
				FullScreen[(l) * 360 + r] = allasset[GameController::curLevel->BackgroundId].data[(l - beginy)*GameController::curLevel->LevelLength + (r - beginx)+CamPosX];
			}
		}
	}
	//原来是用来画背景的


	//排序
	//输出到FullScreen上

	//

	//
	for (int i = 0; i < GameController::curLevel->GameObjectInLevel.size(); i++) {
		int Wx = GameController::curLevel->GameObjectInLevel[i]->PosX;
		int Wy = GameController::curLevel->GameObjectInLevel[i]->PosY;
		int Wz = GameController::curLevel->GameObjectInLevel[i]->PosZ;
		int GOWidth = allasset[GameController::curLevel->GameObjectInLevel[i]->assetid].Width;
		int GOHeight = allasset[GameController::curLevel->GameObjectInLevel[i]->assetid].Height;
		int beginx = WorldPosToScreenPos_X(Wx, CamPosX)-(GOWidth/2);
		int beginy = WorldPosToScreenPos_Y(Wy, Wz) - (GOHeight);
		int endx = (beginx + GOWidth) > 360 ? 360 : (beginx + GOWidth);
		int endy = (beginy + GOHeight)> 160 ? 160 : (beginy + GOHeight);
		for (int l = beginy; l < endy; l++) {
			for (int r = beginx; r < endx; r++) {
				if(r>=0&& allasset[GameController::curLevel->GameObjectInLevel[i]->assetid].data[(l - beginy)*GOWidth + (r - beginx)]!='K')
					FullScreen[(l) * 360 + r] = allasset[GameController::curLevel->GameObjectInLevel[i]->assetid].data[(l - beginy)*GOWidth + (r - beginx)];
			}
		}
	}

	const static WORD color_map[16] =
	{
		NULL,
		BACKGROUND_INTENSITY,
		BACKGROUND_BLUE,
		BACKGROUND_BLUE | BACKGROUND_INTENSITY,
		BACKGROUND_GREEN,
		BACKGROUND_GREEN | BACKGROUND_INTENSITY,
		BACKGROUND_RED,
		BACKGROUND_RED | BACKGROUND_INTENSITY,
		BACKGROUND_BLUE | BACKGROUND_GREEN,
		BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
		BACKGROUND_BLUE | BACKGROUND_RED,
		BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY,	
		BACKGROUND_RED | BACKGROUND_GREEN,
		BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
		BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN,
		BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	};

	//先定义一个大数组，遍历，没有图片显示的地方变黑，有图片显示的地方判断图片的层级，最后确定取哪个颜色，尽管是个数组，仍然用两个循环来写入，以确定行与列
	//后面是合并成一个画面
	for (int i = 0; i < 115200; i += 2) {
		WORD att;
		char c = FullScreen[i / 2];//维护大数组
		att = color_map[c <= '9' ? c - '0' : c - 'A' + 10];
		cBuffer[i].Char.AsciiChar = ' ';
		cBuffer[i].Attributes = att;
		cBuffer[i + 1].Char.AsciiChar = ' ';
		cBuffer[i + 1].Attributes = att;
	}
	return cBuffer;

}
int ScreenGenerator::WorldPosToScreenPos_X(int WX, int LevelScroll) {
	return(WX - LevelScroll);
}
int ScreenGenerator::WorldPosToScreenPos_Y(int WY, int WZ) {
	return(WZ/2+ WY+80);
}
void ScreenGenerator::CamMove(int x) {
	CamPosX = CamPosX + x > 0 ? (CamPosX + x < GameController::curLevel->LevelLength-360 ? CamPosX + x  : GameController::curLevel->LevelLength-360) : 0;
}







//
Picture* ScreenGenerator::allasset;
bool ScreenGenerator::IsFirstFrame;
CHAR_INFO ScreenGenerator::cBuffer[115200];
int ScreenGenerator::nextASIlayer;
char ScreenGenerator::FullScreen[57600];
vector<GameObject> ScreenGenerator::activeGO;
int ScreenGenerator::CamPosX;


