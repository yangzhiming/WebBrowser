// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include "../BrowserIPC/BrowserIPC.h"

char tmpBuff[1024];


void OnIPCRecvCallBack(HIPCSOCKET hConn, const char* lpData, unsigned long len, void* userdata)
{
	printf("%s \n", lpData);
	IPCSend(hConn, "我是宿主EXE", strlen("我是宿主EXE"), NULL, NULL);
}

void OnIPCSendCallBack(HIPCSOCKET hConn, const char* lpData, unsigned long len, void* userdata)
{

}

void OnIPCAcceptCallBack(HIPCSOCKET hListener, HIPCSOCKET hConn, IPCAddress* lpAddrClient, void* userdata)
{
	IPCRecv(hConn, tmpBuff, 1024, NULL, OnIPCRecvCallBack);
}

int _tmain(int argc, _TCHAR* argv[])
{
	IPCStartup();

	HIPCSOCKET hSocket = IPCNewListener();

	IPCAddress addr;
	addr.uPid = 2345;
	addr.uPort = 8000;

	IPCBind(hSocket, addr);
	IPCListen(hSocket, 20);

	IPCAddress addrRemote;
	IPCAccept(hSocket, addrRemote, NULL, OnIPCAcceptCallBack);

	MSG msg;
	while(::GetMessage(&msg, NULL, 0, 0))
	{
		if(msg.message == WM_QUIT)
		{
			break;
		}

		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	system("pause");

	return 0;
}

