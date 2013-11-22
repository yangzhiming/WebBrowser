#include "StdAfx.h"
#include "MsgManager.h"

MsgManager::MsgManager(void) : m_lpfnRecvCallBack(NULL),
							   m_lpUserData(NULL),
							   m_hSendEvent(NULL),
							   m_hEndEvent(NULL),
							   m_hThread(NULL)
{
	m_pMsgWindow = new MsgWindow();
	m_pMsgWindow->SetOwner(this);

	::InitializeCriticalSection(&m_SendLock);
}

MsgManager::~MsgManager(void)
{
	::DeleteCriticalSection(&m_SendLock);
}

bool MsgManager::Init()
{
	if(m_pMsgWindow)
	{
		m_pMsgWindow->Create(HWND_MESSAGE, NULL, NULL, WS_POPUP);
		assert(m_pMsgWindow->m_hWnd);
	}

	m_hSendEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hEndEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	unsigned int dwThreadID;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, MsgSendThread, this, 0, &dwThreadID);

	return true;
}

bool MsgManager::Uninit()
{
	if (m_pMsgWindow)
	{
		m_pMsgWindow->DestroyWindow();
		delete m_pMsgWindow;
		m_pMsgWindow = NULL;
	}

	if(m_hThread)
	{
		SetEvent(m_hEndEvent);
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		CloseHandle(m_hSendEvent);
		CloseHandle(m_hEndEvent);
	}
	
	return true;
}

void MsgManager::OnMessage(COPYDATASTRUCT* lpCopyData)
{
	if(m_lpfnRecvCallBack)
	{
		m_lpfnRecvCallBack((const char*)lpCopyData->lpData, lpCopyData->cbData, m_lpUserData);
	}
}

void MsgManager::PostRemoteMessage(HWND hCommunWnd, const BYTE* lpData, unsigned long len)
{
	if(hCommunWnd)
	{
		BYTE* lpTempData = new BYTE[len];
		::RtlCopyMemory(lpTempData, lpData, len);

		::EnterCriticalSection(&m_SendLock);
		SendDataItem data;
		data.lpData = lpTempData;
		data.len = len;
		data.hCommunWnd = hCommunWnd;
		m_SendDataList.push_back(data);
		::LeaveCriticalSection(&m_SendLock);

		::SetEvent(m_hSendEvent);
	}
}

void MsgManager::SendRemoteMessage(HWND hCommunWnd, const BYTE* lpData, unsigned long len)
{
	if(hCommunWnd)
	{
		COPYDATASTRUCT data;
		data.lpData = (LPVOID)lpData;
		data.cbData = len;
		data.dwData = 0;
		BOOL bResult = ::SendMessage(hCommunWnd, WM_COPYDATA, 0, (LPARAM)&data);
		if(!bResult)
		{
			DWORD dwErr = ::GetLastError();
		}
	}
}

void MsgManager::SetRecvDataCallBack(OnRecvDataCallBack lpfnCallBack, void* userdata)
{
	assert(lpfnCallBack);
	m_lpfnRecvCallBack = lpfnCallBack;
	m_lpUserData = userdata;
}

HWND MsgManager::GetHwnd()
{
	if(m_pMsgWindow)
		return m_pMsgWindow->m_hWnd;
	return NULL;
}

unsigned int __stdcall MsgManager::MsgSendThread(LPVOID param)
{
	MsgManager* lpManager = (MsgManager*)param;
	lpManager->HandleSendData();

	return 0;
}

void MsgManager::HandleSendData()
{
	HANDLE hEvents[2] = {m_hSendEvent, m_hEndEvent};
	while(true)
	{
		DWORD dwResult = WaitForMultipleObjects(2, hEvents, FALSE, INFINITE);
		if( dwResult == WAIT_OBJECT_0)
		{
			::EnterCriticalSection(&m_SendLock);
			std::list<SendDataItem>::iterator it = m_SendDataList.begin();
			for(; it != m_SendDataList.end(); it++)
			{
				SendRemoteMessage(it->hCommunWnd, it->lpData, it->len);

				delete []it->lpData;
			}
			m_SendDataList.clear();
			::LeaveCriticalSection(&m_SendLock);
		}
		else
		{
			break;
		}
	}
}