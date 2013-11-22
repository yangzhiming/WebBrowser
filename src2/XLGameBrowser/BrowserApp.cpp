#include "StdAfx.h"
#include "BrowserApp.h"
#include "BrowserThreadManager.h"

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

void BrowserEventHandler::OnNavigate(LPCTSTR strUrl)
{
	BrowserThreadManager::Instance()->CreateBrowserThread(strUrl);
}