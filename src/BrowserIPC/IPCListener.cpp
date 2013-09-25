#include "StdAfx.h"
#include "IPCListener.h"
#include "IPCConnection.h"

const UINT BUFFERSIZE = 512;

IPCListener::IPCListener(void)
: m_lpfnOnAccept(NULL),
  m_lpUserData(NULL)
{
}

IPCListener::~IPCListener(void)
{
}

long IPCListener::IPCBind(IPCAddress& addr)
{
	m_addrLocal = addr;
	return 0;
}

long IPCListener::IPCListen(int nMax)
{
	if(nMax > PIPE_UNLIMITED_INSTANCES || nMax <= 0) 
	{
		assert(false);
		return -1;
	}

	wchar_t szPipeName[MAX_PATH];
	wsprintf(szPipeName, L"\\\\.\\pipe\\XLWebBrowserPipe_%d_%d", m_addrLocal.uPid, m_addrLocal.uPort);

	for(int i = 0; i < (int)nMax; i++)
	{
		HANDLE hNamedPipe = CreateNamedPipe(szPipeName, 
			PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED,   
			PIPE_TYPE_BYTE, nMax, 
			BUFFERSIZE,  
			BUFFERSIZE, NMPWAIT_USE_DEFAULT_WAIT, NULL); 
		if(hNamedPipe == INVALID_HANDLE_VALUE)  
		{  
			assert(false);
			return -1;
		} 

		IPCConnection* pNewConnection = new IPCConnection(hNamedPipe);
		pNewConnection->AssociateIOCP();
		m_connList.push_back(pNewConnection);
	}

	return 0;
}

long IPCListener::IPCAccept(IPCAddress& addrClient, void* userdata, OnIPCAccept lpfnCallBack)
{
	m_lpfnOnAccept = lpfnCallBack;
	m_lpUserData = userdata;

	//连接耗尽
	if(m_connList.empty())
	{
		if(m_lpfnOnAccept)
		{
			m_lpfnOnAccept((HIPCSOCKET)this, NULL, NULL, userdata);
		}
		return -1;
	}

	//建立新连接
	IPCConnection* lpConn = m_connList.front();
	m_connList.pop_front();
	lpConn->m_overlapped.m_dwOpCode = OP_ACCEPT;
	lpConn->m_overlapped.m_hWnd = m_hWnd;
	lpConn->m_overlapped.m_lpOwner = lpConn;
	if(!ConnectNamedPipe(lpConn->m_hFile, &lpConn->m_overlapped.m_ol))
	{
		DWORD dwErr = ::GetLastError();
		if(ERROR_IO_PENDING != dwErr)
		{
			m_lpfnOnAccept((HIPCSOCKET)this, NULL, NULL, userdata);
			return -1;
		}
	}

	return 0;
}

long IPCListener::IPCClose()
{
	return 0;
}

void IPCListener::OnAccept(IPCOverlapped* lpOverlapped)
{
	assert(lpOverlapped->m_dwOpCode == OP_ACCEPT);

	//置为连接状态
	lpOverlapped->m_lpOwner->SetState((int)State_Connected);

	if(m_lpfnOnAccept)
	{
		m_lpfnOnAccept((HIPCSOCKET)this, (HIPCSOCKET)lpOverlapped->m_lpOwner, NULL, m_lpUserData);
	}
}

void IPCListener::OnConnect(IPCOverlapped* lpOverlapped)
{
	assert(false);
}

void IPCListener::OnRecv(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered)
{
	assert(false);
}

void IPCListener::OnSend(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered)
{
	assert(false);
}