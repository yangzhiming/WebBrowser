#include "StdAfx.h"
#include "BrowserApp.h"
#include "BrowserThreadManager.h"
#include "BrowserItem.h"
#include "BrowserWnd.h"

BrowserApp::BrowserApp(void)
{
}

BrowserApp::~BrowserApp(void)
{
}

void BrowserApp::InitInstance()
{
	BrowserComunication::Instance()->Init();
	BrowserComunication::Instance()->AddEventHandler(&m_BrowserHandler);
	BrowserComunication::Instance()->ConnectHostComunity();
	BrowserComunication::Instance()->NotifyHostProcessCreated();
}

void BrowserApp::ExitInstance()
{

}

void BrowserApp::Run()
{

}

void BrowserEventHandler::OnNavigate(DWORD dwToThreadID, LPCTSTR strUrl)
{
	BrowserThreadItem* lpItem = BrowserThreadManager::Instance()->FindBrowserItem(dwToThreadID);
	if(lpItem)
	{
		BrowserWnd* lpWnd = lpItem->GetBrowserWnd();
		if(lpWnd)
		{
			lpWnd->Navigate(strUrl);
		}
	}
}

void BrowserEventHandler::OnCreateAndNavigate(HWND hParentWnd, LPCTSTR strUrl, DWORD dwMark)
{
	BrowserThreadManager::Instance()->CreateBrowserThread(hParentWnd, strUrl, dwMark);
}

void BrowserEventHandler::OnDestroy(DWORD dwToThreadID)
{
	BrowserThreadItem* lpItem = BrowserThreadManager::Instance()->FindBrowserItem(dwToThreadID);
	if(lpItem)
	{
		lpItem->Destroy();
	}
}