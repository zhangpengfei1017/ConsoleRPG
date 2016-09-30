#include "TcpClient.h"
#include "Header.h"
#include<chrono>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include "Input.h"
#include "Time.h"
#include "GameObject.h"
#include "GameController.h"
#include <windows.h> 
using namespace std;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CHAR_INFO* chiBuffer;
COORD coordBufSize = { 720,160 };
COORD coordBufCoord = { 0,0 };
SMALL_RECT srctWriteRect = { 0,0,720,160 };
HANDLE hNewScreenBuffer;
ofstream outfile("output.txt", ios::in | ios::trunc);
 int LastFrameTime;
int FramesCount = 0;
float deltaTime = 0;
void Start() {
	GameController::LevelInit();
	Input::Init();	
	ScreenGenerator::init();
	Time::init();
	SetWindow();
	
}
void Update() {
	UpdateScreen();
	//
	outfile << Time::NowTime() - TcpClient::LastConnectTime << endl;
	if (GameController::curLevel->ID == 0) {
		if (Input::GetKey(0x59)) {//Y connect
			GameController::LoadLevel(1);
			return;
		}
		if (Input::GetKey(0x4E)) {//N exit
			exit(0);
		}
	}
	if (GameController::curLevel->ID == 1) {
		int i = TcpClient::ConnectServer();
		if (i == 0) {
			GameController::LoadLevel(2);
			return;//Succeed! goto lv3
		}
		else if (i == -1) {
			GameController::LoadLevel(3);//failed! goto lv2
			return;
		}
	}
	if (GameController::curLevel->ID == 2) {
		Sleep(1000);
		GameController::LoadLevel(4);
		return;
	}
	if (GameController::curLevel->ID == 3) {
		Sleep(1000);
		GameController::LoadLevel(0);
		return;
	}
	
	if (GameController::curLevel->ID == 6) { //failed to join
		Sleep(1000);
		GameController::LoadLevel(4);
	}
	if (GameController::curLevel->ID == 7) { //succeed to join
											 //进入房间 周期发房间内信息
		if (Input::GetKeyDown(0x45)) {//e create
			TcpClient::SendMsg(5, 0, nullptr);
			GameController::LoadLevel(4);
		}
	}
	if (GameController::curLevel->ID == 5) { //wait to join room
		Sleep(1000);
		if (TcpClient::JoinOk) {
			GameController::LoadLevel(7);
		}
		else {
			GameController::LoadLevel(6);
		}

	}
	if (GameController::curLevel->ID == 4) {
		//进入大厅 只做心跳测试
		if (Input::GetKeyDown(0x43)) {//C create
			GameController::LoadLevel(5);
			TcpClient::SendMsg(2, 0, nullptr);
		}
		if (Input::GetKeyDown(0x4A)) {//j create
			GameController::LoadLevel(5);
			TcpClient::SendMsg(3, 1, nullptr);
		}
		if (Input::GetKeyDown(0x45)) {//e create
			TcpClient::SendMsg(4, 0, nullptr);
			GameController::LoadLevel(0);
		}
	}
	if (GameController::curLevel->ID >= 8) {// lost connection
		if (Input::GetKeyDown(0x45)) {//e create
			GameController::LoadLevel(0);
		}
	}
	if (GameController::curLevel->ID >= 9) {
		//进入游戏 先发一个场景初始化信息包 之后周期发游戏内信息
	}
	
}







int main() {
	Start();
	while (1) {
		if (Time::UpdateTime()) {
			Update();
		}
	}
}
void SetWindow() {
	chiBuffer = ScreenGenerator::NextScreen();
	hNewScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |           // read/write access 
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,        // shared 
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);
	SetConsoleActiveScreenBuffer(hNewScreenBuffer);
	SetConsoleScreenBufferSize(hNewScreenBuffer, coordBufSize);
	WriteConsoleOutput(
		hNewScreenBuffer, // screen buffer to write to 
		chiBuffer,        // buffer to copy from 
		coordBufSize,     // col-row size of chiBuffer 
		coordBufCoord,    // top left src cell in chiBuffer 
		&srctWriteRect);  // dest. screen buffer rectangle 
	SMALL_RECT rc = { 0,0, 720 - 1, 160 - 1 }; // 重置窗口位置和大小
	SetConsoleWindowInfo(hNewScreenBuffer, TRUE, &rc);
}
void UpdateScreen() {
	auto t1 = chrono::high_resolution_clock::now();
	chiBuffer = ScreenGenerator::NextScreen();
	auto t2 = chrono::high_resolution_clock::now();
	WriteConsoleOutput(
		hNewScreenBuffer, // screen buffer to write to 
		chiBuffer,        // buffer to copy from 
		coordBufSize,     // col-row size of chiBuffer 
		coordBufCoord,    // top left src cell in chiBuffer 
		&srctWriteRect);  // dest. screen buffer rectangle 
	auto t3 = chrono::high_resolution_clock::now();
	auto delta1 = chrono::duration<float>(t2 - t1).count();
	auto delta2 = chrono::duration<float>(t3 - t2).count();
}

