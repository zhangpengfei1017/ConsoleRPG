#pragma once
#include "winsock2.h"  
#include <iostream>  
#pragma comment(lib, "ws2_32.lib") 
#include <thread>
#include <fstream>
class TcpClient
{
	
public:
	struct Room {
		int RoomID = 0;
		int PlayerNum;
		int UIDs[4];
	};
	TcpClient();
	~TcpClient();
	static SOCKET sHost; //服务器套接字  
	static WSADATA wsd; //WSADATA变量  
	static SOCKADDR_IN servAddr; //服务器地址  
	static char bufSend[1024]; //接收数据缓冲区  
	static char bufRecv[1024];
	static int retVal; //返回值  
	static int UID;
	static Room mRoom;
	static std::ofstream outfile;
	static int LastConnectTime;
	static bool JoinOk;
	//
	static void RecvMsg();
	static int ConnectServer();
	static void SendMsg(int CmdId, int MsgNum,char Msg[]);
	static void CheckMsg(char Msg[]);
};

