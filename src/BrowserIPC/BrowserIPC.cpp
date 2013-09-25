#include "stdafx.h"
#include "./BrowserIPC.h"
#include "./IPCConnection.h"
#include "./IPCListener.h"
#include "./IPCEnv.h"

long __stdcall IPCStartup()
{
	return IPCEnv::Instance()->IPCStartup();
}

long __stdcall IPCCleanup()
{
	return IPCEnv::Instance()->IPCCleanup();
}

HIPCSOCKET __stdcall IPCNewListener()
{
	return (HIPCSOCKET)(new IPCListener());
}

long __stdcall IPCListen(HIPCSOCKET hListener, int nMax)
{
	IPCSocket* pListener = (IPCSocket*)hListener;
	if(pListener)
	{
		return pListener->IPCListen(nMax);
	}

	return 0;
}

long __stdcall IPCBind(HIPCSOCKET hListener, IPCAddress& addrLocal)
{
	IPCSocket* pListener = (IPCSocket*)hListener;
	if(pListener)
	{
		return pListener->IPCBind(addrLocal);
	}

	return 0;
}

long __stdcall IPCAccept(HIPCSOCKET hListener, IPCAddress& addrClient, void* userdata, OnIPCAccept lpfnCallBack)
{
	IPCSocket* pListener = (IPCSocket*)hListener;
	if(pListener)
	{
		return pListener->IPCAccept(addrClient, userdata, lpfnCallBack);
	}

	return 0;
}

HIPCSOCKET __stdcall IPCNewConnection()
{
	return (HIPCSOCKET)(new IPCConnection());
}

long __stdcall IPCConnect(HIPCSOCKET hConn, IPCAddress& addrHost, void* userdata, OnIPCConnect lpfnCallBack)
{
	IPCSocket* pConn = (IPCSocket*)hConn;
	if(pConn)
	{
		return pConn->IPCConnect(addrHost, userdata, lpfnCallBack);
	}

	return 0;
}

long __stdcall IPCSend(HIPCSOCKET hConn, const char* lpData, unsigned long len, void* userdata, OnIPCSend lpfnCallBack)
{
	IPCSocket* pConn = (IPCSocket*)hConn;
	if(pConn)
	{
		return pConn->IPCSend(lpData, len, userdata, lpfnCallBack);
	}
	return 0;
}

long __stdcall IPCRecv(HIPCSOCKET hConn, char* lpBuff, unsigned long len, void* userdata, OnIPCRecv lpfnCallBack)
{
	IPCSocket* pConn = (IPCSocket*)hConn;
	if(pConn)
	{
		return pConn->IPCRecv(lpBuff, len, userdata, lpfnCallBack);
	}

	return 0;
}

long __stdcall IPCClose(HIPCSOCKET hSocket)
{
	IPCSocket* pSocket = (IPCSocket*)hSocket;
	if(pSocket)
	{
		return pSocket->IPCClose();
	}
	return 0;
}