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
	static SOCKET sHost; //�������׽���  
	static WSADATA wsd; //WSADATA����  
	static SOCKADDR_IN servAddr; //��������ַ  
	static char bufSend[1024]; //�������ݻ�����  
	static char bufRecv[1024];
	static int retVal; //����ֵ  
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

