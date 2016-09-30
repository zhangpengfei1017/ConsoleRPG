#include "TcpClient.h"
#include "GameController.h"
#include "Time.h"
struct HeadPackage_C00 {
	int UID;
	int CmdID;
};
struct JoinRoom_C03 {
	int RoomID;
};

//
// server struct below
struct HeadPackage_S00 {
	int UID;
	int CmdID;
};
struct RoomInfo_S02 {
	int RoomId;
};
struct RoomCurentInfo_S05 {
	int RoomID;
	int UIDs[4];
	int PlayerNum;
};
void TcpClient::CheckMsg(char Msg[]) {
	HeadPackage_S00 hp;
	int BufPos = 0;
	memset(&hp, 0, sizeof(hp));
	memcpy(&hp, Msg, sizeof(hp));
	BufPos += sizeof(hp);
	switch (hp.CmdID)
	{
	case 0:// receive the fist package from server to get the UID
		UID = hp.UID;
		break;
	case 1:// receive the heart beat request from server
		SendMsg(1, 0, nullptr);
		break;
	case 2:// receive the room# from server
		RoomInfo_S02 ri;
		memset(&ri, 0, sizeof(ri));
		memcpy(&ri, Msg + BufPos, sizeof(ri));
		BufPos += sizeof(ri);
		mRoom.RoomID= ri.RoomId;
		break;
	case 3:// succeed to join
		JoinOk = true;
		break;
		//jumplevel;
	case 4://fail to join
		JoinOk = false;
		break;
		//jumplevel;
	case 5://update the room inside info
		RoomCurentInfo_S05 rci;
		memset(&rci, 0, sizeof(rci));
		memcpy(&rci, Msg + BufPos, sizeof(rci));
		BufPos += sizeof(rci);
		mRoom.RoomID = rci.RoomID;
		mRoom.PlayerNum = rci.PlayerNum;
		for (int i = 0; i < mRoom.PlayerNum; i++) {
			mRoom.UIDs[i] = rci.UIDs[i];
		}
		SendMsg(1, 0, nullptr);
		break;
	default:
		break;
	}
	LastConnectTime = Time::NowTime();
}
void TcpClient::SendMsg(int CmdId,int MsgNum, char MsgChar[]) {
	HeadPackage_C00 hp = { UID,CmdId };
	int BufPos = 0;
	memset(bufSend, 0, 1024);
	memcpy(bufSend, &hp, sizeof(hp));
	BufPos += sizeof(hp);
	switch (CmdId)
	{
	case 1://心跳回应 00.
		break;
	case 2://建立房间 00.
		
		break;
	case 3://加入房间 00 03.
		JoinRoom_C03 jr;
		jr.RoomID = MsgNum;
		memcpy(bufSend + BufPos, &jr, sizeof(jr));
		BufPos += sizeof(jr);
		break;
	case 4://退出大厅 .
		break;
	case 5://退出房间 .
		break;
	case 6://开始游戏 .
		break;
	default:
		break;
	}
	send(sHost, bufSend, 1024, 0);
	//outfile << "发送了" << CmdId << std::endl;
}
TcpClient::TcpClient()
{
}
TcpClient::~TcpClient()
{
}
int TcpClient::ConnectServer() {
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		std::cout << "WSAStartup failed!" << std::endl;
		return -1;
	}
	//创建套接字  	
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//	ioctlsocket(sHost, FIONBIO, &mode);
	if (INVALID_SOCKET == sHost)
	{
		std::cout << "socket failed!" << std::endl;
		WSACleanup();//释放套接字资源  
		return  -1;
	}

	//设置服务器地址  
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons((short)4999);
	int nServAddlen = sizeof(servAddr);
	//连接服务器  	
	int attempt = 0;
	while (true) {
		Sleep(1000);
		retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
		if (SOCKET_ERROR != retVal)
		{
			break;
		}
		else {
			attempt++;
		}
		if (attempt >= 30) {
			return(-1);
		}
	}
	std::thread RecvThread(&RecvMsg);
	LastConnectTime = Time::NowTime();
	RecvThread.detach();
	return 0;
}
void TcpClient::RecvMsg() {
	while (true)
	{
		ZeroMemory(bufRecv, 1024);
		if (recv(sHost, bufRecv, 1024, 0) != SOCKET_ERROR) {
			CheckMsg(bufRecv);
		}
		//退出  
		if (Time::NowTime() - LastConnectTime > 10000) {
			GameController::LoadLevel(8);
			break;
		}
	}
		closesocket(sHost); //关闭套接字  
		WSACleanup(); //释放套接字资源  
}

///

SOCKET TcpClient::sHost; //服务器套接字  
WSADATA TcpClient::wsd; //WSADATA变量  
SOCKADDR_IN TcpClient::servAddr; //服务器地址  
char TcpClient::bufSend[1024]; //接收数据缓冲区  
char TcpClient::bufRecv[1024];
int TcpClient::retVal; //返回值  
int TcpClient::UID;//UID for this client, default is 0;
TcpClient::Room TcpClient::mRoom;
int TcpClient::LastConnectTime;
bool TcpClient::JoinOk;
