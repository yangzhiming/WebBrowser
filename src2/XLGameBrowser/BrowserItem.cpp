#include "StdAfx.h"
#include "BrowserItem.h"
#include "BrowserWnd.h"

BrowserThreadItem::BrowserThreadItem(void) : m_pBrowserWnd(NULL),
											 m_hThread(NULL),
											 m_hParentWnd(NULL),
											 m_dwMark(0)
{
}

BrowserThreadItem::~BrowserThreadItem(void)
{
}

bool BrowserThreadItem::Create(DWORD& dwThreadID, HWND hParent, LPCTSTR strUrl, DWORD dwMark)
{
	m_strToNavigate = strUrl;
	m_hParentWnd = hParent;
	m_dwMark = dwMark;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, BrowserWorkerThread, this, 0, (unsigned int*)&dwThreadID);
	if(m_hThread != NULL)
	{
		return true;
	}

	return false;
}

bool BrowserThreadItem::Destroy()
{
	if(m_hThread != NULL)
	{
		//A thread cannot use DestroyWindow to destroy a window created by a different thread.
		//so it post wm_browserquit message to browser thread and wait for ondestroy event
		//then postquitmessage to message loop to quit the thread
		m_pBrowserWnd->DestroyBrowserWnd();
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
		delete m_pBrowserWnd;
		m_pBrowserWnd = NULL;
	}
	return true;
}

unsigned int WINAPI BrowserThreadItem::BrowserWorkerThread(LPVOID param)
{
	HRESULT hRes = ::CoInitialize(NULL);
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	BrowserThreadItem* lpBrowserThreadItem = (BrowserThreadItem*)param;
	lpBrowserThreadItem->m_pBrowserWnd = new BrowserWnd();
	lpBrowserThreadItem->m_pBrowserWnd->SetMark(lpBrowserThreadItem->m_dwMark);
	lpBrowserThreadItem->m_pBrowserWnd->CreateBrowserWnd(lpBrowserThreadItem->m_hParentWnd);
	lpBrowserThreadItem->m_pBrowserWnd->ShowWindow(SW_SHOW);
	lpBrowserThreadItem->m_pBrowserWnd->Navigate(lpBrowserThreadItem->m_strToNavigate);

	CMessageLoop theLoop;

	_Module.AddMessageLoop(&theLoop);
	theLoop.Run();
	_Module.RemoveMessageLoop();

	::CoUninitialize();

	return 0;
}