#include "StdAfx.h"
#include "IPCConnection.h"
#include "IPCEnv.h"

IPCConnection::IPCConnection(void)
: m_lpfnOnSend(NULL),
  m_lpfnOnRecv(NULL),
  m_lpfnOnConnect(NULL),
  m_lpOnRecvUserData(NULL),
  m_lpOnSendUserData(NULL),
  m_lpOnConnUserData(NULL),
  m_hFile(NULL),
  m_lpBufferRecv(NULL),
  m_lpBufferSend(NULL)
{
}

IPCConnection::IPCConnection(HANDLE hFile)
: m_lpfnOnSend(NULL),
  m_lpfnOnRecv(NULL),
  m_lpfnOnConnect(NULL),
  m_lpOnRecvUserData(NULL),
  m_lpOnSendUserData(NULL),
  m_lpOnConnUserData(NULL),
  m_hFile(hFile),
  m_lpBufferSend(NULL),
  m_lpBufferRecv(NULL)
{
	
}

IPCConnection::~IPCConnection(void)
{
}

bool IPCConnection::AssociateIOCP()
{
	assert(m_hFile);
	if(!m_hFile)
	{
		return false;
	}

	return IPCEnv::Instance()->AssociateHandle(m_hFile);
}

long IPCConnection::IPCConnect(IPCAddress& addrHost, void* userdata, OnIPCConnect lpfnCallBack)
{
	m_lpfnOnConnect = lpfnCallBack;
	m_lpOnConnUserData = userdata;

	wchar_t szPipeName[MAX_PATH];
	wsprintf(szPipeName, L"\\\\.\\pipe\\XLWebBrowserPipe_%d_%d", addrHost.uPid, addrHost.uPort);

	m_hFile = CreateFile(szPipeName, GENERIC_WRITE|GENERIC_READ,  
		FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);  
	if(m_hFile == INVALID_HANDLE_VALUE)
	{
		if(m_lpfnOnConnect)
		{
			m_lpfnOnConnect((HIPCSOCKET)this, NULL, m_lpOnConnUserData);
			return -1;
		}
	}

	AssociateIOCP();
	SetState((int)State_Connected);

	return 0;
}

long IPCConnection::IPCSend(const char* lpData, unsigned long len, void* userdata, OnIPCSend lpfnCallBack)
{
	m_lpfnOnSend = lpfnCallBack;
	m_lpOnSendUserData = userdata;
	m_lpBufferSend = lpData;

	assert(m_dwState == State_Connected);
	if(m_dwState != State_Connected)
	{
		return -1;
	}

	DWORD ioRead = 0;
	m_overlapped.m_lpOwner = this;
	m_overlapped.m_hWnd = m_hWnd;
	m_overlapped.m_dwOpCode = OP_SEND;
	if(!WriteFile(m_hFile, lpData, len, &ioRead, &m_overlapped.m_ol))
	{
		DWORD dwErr = GetLastError();
		if(ERROR_IO_PENDING != dwErr)
		{
			m_lpfnOnSend((HIPCSOCKET)this, NULL, 0, m_lpOnSendUserData);
			return -1;
		}
	}
	else
	{
		//IO立即成功，那么直接回复
		m_lpfnOnSend((HIPCSOCKET)this, m_lpBufferSend, ioRead, m_lpOnRecvUserData);
	}

	return 0;
}

long IPCConnection::IPCRecv(char* lpBuff, unsigned long len, void* userdata, OnIPCRecv lpfnCallBack)
{
	m_lpfnOnRecv = lpfnCallBack;
	m_lpOnRecvUserData = userdata;
	m_lpBufferRecv = lpBuff;

	assert(m_dwState == State_Connected);
	if(m_dwState != State_Connected)
	{
		return -1;
	}

	DWORD ioRead = 0;
	m_overlapped.m_lpOwner = this;
	m_overlapped.m_hWnd = m_hWnd;
	m_overlapped.m_dwOpCode = OP_RECV;
	if(!ReadFile(m_hFile, lpBuff, len, &ioRead, &m_overlapped.m_ol))
	{
		DWORD dwErr = GetLastError();
		if(ERROR_IO_PENDING != dwErr)
		{
			m_lpfnOnRecv((HIPCSOCKET)this, NULL, 0, m_lpOnRecvUserData);
			return -1;
		}
	}
	else
	{
		//IO立即成功，那么直接回复
		m_lpfnOnRecv((HIPCSOCKET)this, lpBuff, ioRead, m_lpOnRecvUserData);
	}

	return 0;
}

long IPCConnection::IPCClose()
{
	CloseHandle(m_hFile);
	m_hFile = INVALID_HANDLE_VALUE;
	return 0;
}

void IPCConnection::OnAccept(IPCOverlapped* lpOverlapped)
{
	assert(false);
}

void IPCConnection::OnConnect(IPCOverlapped* lpOverlapped)
{
	m_dwState = State_Connected;

	if(m_lpfnOnConnect)
	{
		m_lpfnOnConnect((HIPCSOCKET)this, NULL, m_lpOnConnUserData);
	}
}

void IPCConnection::OnRecv(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered)
{
	if(m_lpfnOnRecv)
	{
		m_lpfnOnRecv((HIPCSOCKET)this, (const char*)m_lpBufferRecv, dwByteTransfered, m_lpOnRecvUserData);
	}
}

void IPCConnection::OnSend(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered)
{
	if(m_lpfnOnConnect)
	{
		m_lpfnOnSend((HIPCSOCKET)this, m_lpBufferSend, dwByteTransfered, m_lpOnSendUserData);
	}
}