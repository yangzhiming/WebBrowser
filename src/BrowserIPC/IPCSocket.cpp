#include "StdAfx.h"
#include "IPCSocket.h"

IPCSocket::IPCSocket(void)
: m_dwState(State_Ready)
{
	memset(&m_overlapped, sizeof(m_overlapped), 0);
	memset(&m_addrLocal, sizeof(IPCAddress), 0);
	memset(&m_addrRemote, sizeof(IPCAddress), 0);

	Create(HWND_MESSAGE, NULL, NULL, WS_POPUP);
	assert(m_hWnd != NULL);
}

IPCSocket::~IPCSocket(void)
{
}

long IPCSocket::IPCBind(IPCAddress& addr)
{
	assert(false);
	return 0;
}

long IPCSocket::IPCListen(int nMax)
{
	assert(false);
	return 0;
}

long IPCSocket::IPCAccept(IPCAddress& addrClient, void* userdata, OnIPCAccept lpfnCallBack)
{
	assert(false);
	return 0;
}

long IPCSocket::IPCConnect(IPCAddress& addrHost, void* userdata, OnIPCConnect lpfnCallBack)
{
	assert(false);
	return 0;
}

long IPCSocket::IPCSend(const char* lpData, unsigned long len, void* userdata, OnIPCSend lpfnCallBack)
{
	assert(false);
	return 0;
}

long IPCSocket::IPCRecv(char* lpBuff, unsigned long len, void* userdata, OnIPCRecv lpfnCallBack)
{
	assert(false);
	return 0;
}

long IPCSocket::IPCClose()
{
	return 0;
}

LRESULT IPCSocket::OnIPCEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IPCOverlapped* lpOverlapped = (IPCOverlapped*)wParam;
	DWORD dwByteTransfered = lParam;
	assert(lpOverlapped);

	switch (lpOverlapped->m_dwOpCode)
	{
	case OP_ACCEPT:
		OnAccept(lpOverlapped);
		break;

	case OP_CONNECT:
		OnConnect(lpOverlapped);
		break;

	case OP_SEND:
		OnSend(lpOverlapped, dwByteTransfered);
		break;

	case OP_RECV:
		OnRecv(lpOverlapped, dwByteTransfered);
		break;

	default:
		assert(false);
		break;
	}

	return 0L;
}

void IPCSocket::OnSend(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered)
{
	assert(false);
}

void IPCSocket::OnRecv(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered)
{
	assert(false);
}

void IPCSocket::OnAccept(IPCOverlapped* lpOverlapped)
{
	assert(false);
}

void IPCSocket::OnConnect(IPCOverlapped* lpOverlapped)
{
	assert(false);
}

void IPCSocket::SetState(int state)
{
	m_dwState = state;
}