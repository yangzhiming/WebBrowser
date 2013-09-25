#include "StdAfx.h"
#include "IPCEnv.h"
#include "./IPCInternalDef.h"

IPCEnv::IPCEnv(void)
: m_hThread(NULL),
  m_hIOCP(NULL),
  m_bRunning(true)
{
}

IPCEnv::~IPCEnv(void)
{
}

long IPCEnv::IPCStartup()
{
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	assert(m_hIOCP);

	m_hThread = CreateThread(NULL, 0, WorkerThread, this, 0, 0);
	assert(m_hThread);

	return 0;
}

long IPCEnv::IPCCleanup()
{
	if(m_hThread)
	{
		m_bRunning = false;

		assert(m_hIOCP);
		::PostQueuedCompletionStatus(m_hIOCP, 0, NULL, NULL);

		WaitForSingleObject(m_hThread, INFINITE);

		CloseHandle(m_hThread);
	}
	
	return 0;
}

bool IPCEnv::AssociateHandle(HANDLE hFile)
{
	assert(hFile);
	assert(m_hIOCP);

	if(NULL == hFile || NULL == m_hIOCP)
	{
		return false;
	}

	bool ret = true;
	HANDLE hRet = ::CreateIoCompletionPort(hFile, m_hIOCP, 0, 0);
	if (hRet == NULL)
	{
		DWORD err = ::GetLastError();
		if (err == ERROR_INVALID_PARAMETER)
		{
			// 可能是重复绑定
		}
		else
		{
			ret = false;
			assert(false);
		}
	}

	return !!ret;
}

bool IPCEnv::IsRunning() const
{
	return m_bRunning;
}

DWORD WINAPI IPCEnv::WorkerThread(LPVOID lpParam)
{
	return IPCEnv::Instance()->WorkerProc();
}

DWORD IPCEnv::WorkerProc()
{
	do 
	{
		if (!IsRunning())
		{
			break;
		}

		assert(m_hIOCP);

		unsigned long bytesTransferred;
		ULONG_PTR key;
		LPOVERLAPPED lpOverLapped = NULL;

		BOOL ret = ::GetQueuedCompletionStatus(m_hIOCP, &bytesTransferred, &key, 
			&lpOverLapped, INFINITE);
		if (!ret)
		{
			if(lpOverLapped == NULL)
			{
				break;
			}
		}

		if(!IsRunning())
		{
			break;
		}

		OnIoComplete(lpOverLapped, bytesTransferred);

	}while(true);

	return 0;
}

void IPCEnv::OnIoComplete(LPOVERLAPPED lpOverlapped, DWORD dwByteTransfered)
{
	IPCOverlapped* lpIpcOverlapped = (IPCOverlapped*)lpOverlapped;
	assert(lpIpcOverlapped);
	assert(lpIpcOverlapped->m_hWnd != NULL);
	::PostMessage(lpIpcOverlapped->m_hWnd, UM_IPC_EVENT, (WPARAM)lpIpcOverlapped, dwByteTransfered);
}