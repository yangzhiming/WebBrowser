#pragma once

#include "MsgWindow.h"

typedef void (*OnRecvDataCallBack)(const char* lpData, unsigned long len, void* userdata);

class MsgManager
{
public:
	struct SendDataItem
	{
		const BYTE* lpData;
		unsigned long len;
		HWND hCommunWnd;
	};
public:
	MsgManager(void);
	~MsgManager(void);
	
	bool Init();
	bool Uninit();

	void SetRecvDataCallBack(OnRecvDataCallBack lpfnCallBack, void* userdata);

	void PostRemoteMessage(HWND hCommunWnd, const BYTE* lpData, unsigned long len);
	void SendRemoteMessage(HWND hCommunWnd, const BYTE* lpData, unsigned long len);

	HWND GetHwnd();

public:
	virtual void OnMessage(COPYDATASTRUCT* lpCopyData);

protected:
	void HandleSendData();

	static unsigned int __stdcall MsgSendThread(LPVOID param);

private:
	MsgWindow*		m_pMsgWindow;
	std::list<SendDataItem> m_SendDataList;
	OnRecvDataCallBack m_lpfnRecvCallBack;
	LPVOID m_lpUserData;
	CRITICAL_SECTION m_SendLock;
	HANDLE m_hSendEvent;
	HANDLE m_hEndEvent;
	HANDLE m_hThread;
};
