#include "StdAfx.h"
#include "MsgWindow.h"
#include "MsgManager.h"

MsgWindow::MsgWindow(void)
{
}

MsgWindow::~MsgWindow(void)
{
}

BOOL MsgWindow::ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
						  LRESULT& lResult, DWORD dwMsgMapID)
{
	MsgManager* pMsgManager = (MsgManager*)m_lpOwner;
	if(uMsg == WM_COPYDATA)
	{
		COPYDATASTRUCT* lpCopyData = (COPYDATASTRUCT*)lParam;
		pMsgManager->OnMessage(lpCopyData);
		return FALSE;
	}

	return FALSE;
}