#include "StdAfx.h"
#include "BrowserComunication.h"
#include "../BrowserProtocol/ConnectPackage.h"
#include "../BrowserProtocol/BrowserCreatedPackage.h"
#include "../BrowserProtocol/CommonPackageT.h"
#include "../BrowserProtocol/NavigatePackage.h"

BrowserComunication::BrowserComunication(void)
{
	m_lpMsgManager = new MsgManager();

	m_lpFactory = new UserPackageFactory();
	m_lpParser = new UserPackageParser(m_lpFactory);
}

BrowserComunication::~BrowserComunication(void)
{
}

bool BrowserComunication::Init()
{
	bool bRet = false;
	if(m_lpMsgManager)
	{
		bRet &= m_lpMsgManager->Init();
		//m_lpMsgManager->AddMsgHandler(this);
		m_lpMsgManager->SetRecvDataCallBack(OnCommunication, (void*)this);
	}

	//通过filemapping获取远程host的通信窗口
	HRESULT hr = m_fileMapping.OpenMapping(L"XLWebBrowserHostWnd_FileMapping", sizeof(HWND) );
	if(SUCCEEDED(hr))
	{
		m_hHostCommunWnd = *((HWND*)m_fileMapping.GetData());
		bRet &= true;
	}

	return bRet;
}

bool BrowserComunication::Uninit()
{
	if(m_lpMsgManager)
	{
		m_lpMsgManager->Uninit();
		delete m_lpMsgManager;
		m_lpMsgManager = NULL;
	}

	if(m_lpParser)
	{
		delete m_lpParser;
		m_lpParser = NULL;
	}

	if(m_lpFactory)
	{
		delete m_lpFactory;
		m_lpFactory = NULL;
	}
	return true;
}

void BrowserComunication::AddEventHandler(IEventHandler* lpHandler)
{
	std::list<IEventHandler*>::iterator it = m_HandlerList.begin();
	for(; it != m_HandlerList.end(); ++it)
	{
		if(*it == lpHandler)
		{
			return;
		}
	}

	m_HandlerList.push_back(lpHandler);
}

void BrowserComunication::RemoveEventHandler(IEventHandler* lpHandler)
{
	std::list<IEventHandler*>::iterator it = m_HandlerList.begin();
	for(; it != m_HandlerList.end(); ++it)
	{
		if(*it == lpHandler)
		{
			m_HandlerList.erase(it);
			break;
		}
	}
}

void BrowserComunication::Fire_OnNavigate(DWORD dwToThreadID, LPCTSTR strUrl)
{
	std::list<IEventHandler*>::iterator it = m_HandlerList.begin();
	for(; it != m_HandlerList.end(); ++it)
	{
		(*it)->OnNavigate(dwToThreadID, strUrl);
	}
}

void BrowserComunication::Fire_OnCreateAndNavigate(HWND hParentWnd, LPCTSTR strUrl, DWORD dwMark)
{
	std::list<IEventHandler*>::iterator it = m_HandlerList.begin();
	for(; it != m_HandlerList.end(); ++it)
	{
		(*it)->OnCreateAndNavigate(hParentWnd, strUrl, dwMark);
	}
}

//连接宿主通信端
long BrowserComunication::ConnectHostComunity()
{
	ConnectPackage* lpPackage = new ConnectPackage();
	lpPackage->hClientWnd = m_lpMsgManager->GetHwnd();
	InternalSendPackage(lpPackage);
	delete lpPackage;
	return 0;
}

long BrowserComunication::NotifyHostProcessCreated()
{
	ProcessCreatedPackage* lpPackage = new ProcessCreatedPackage();
	InternalSendPackage(lpPackage);
	delete lpPackage;
	return 0;
}

//此函数是在浏览器线程通知出来，所以直接GetCurrentThreadId没问题
long BrowserComunication::NotifyHostBrowserCreated(DWORD dwMark)
{
	DWORD dwThreadID = ::GetCurrentThreadId();
	BrowserCreatedPackage* lpPackage = new BrowserCreatedPackage();
	lpPackage->m_dwBrowserThreadID = dwThreadID;
	lpPackage->m_dwMark = dwMark;
	InternalSendPackage(lpPackage);
	delete lpPackage;
	return 0;
}

void BrowserComunication::OnCommunication(const char* lpData, unsigned long len, void* userdata)
{
	BrowserComunication* lpThis = (BrowserComunication*)userdata;
	if(lpThis)
	{
		lpThis->OnCommunication(lpData, len);
	}
}

void BrowserComunication::OnCommunication(const char* lpData, unsigned long len)
{
	if(m_lpParser->PushData((BYTE*)lpData, len) == 0)
	{
		BasePackage* lpPackage = m_lpParser->PopResultPackage();
	 	if(lpPackage)
	 	{
	 		OnRecvRespPackage(lpPackage);
	 	}
	}
}

void BrowserComunication::InternalSendPackage(BasePackage* lpPacakge)
{
	if(m_lpMsgManager)
	{
		int len = lpPacakge->GetEncodeLen();
		BYTE* lpData = new BYTE[len];
		lpPacakge->Encode(lpData, len);
		m_lpMsgManager->PostRemoteMessage(m_hHostCommunWnd, lpData, len);

		delete []lpData;
	}
}

void BrowserComunication::OnRecvRespPackage(BasePackage* lpPackage)
{
	DWORD dwMsgID = lpPackage->GetMessageID();
	switch(dwMsgID)
	{
	case XBM_MSG_NAVIGATE:
		{
			OnNavigate(lpPackage);
		}
		break;
	case XBM_MSG_CREATEANDNAVIGATE:
		{
			OnCreateAndNavigate(lpPackage);
		}
		break;
	default:
		assert(false);
		break;
	}

	delete lpPackage;
}

void BrowserComunication::OnNavigate(BasePackage* lpPackage)
{
	NavigatePackage* lpNavigatePackage = dynamic_cast<NavigatePackage*>(lpPackage);
	assert(lpNavigatePackage);

	std::string strUrl = lpNavigatePackage->m_strUrl;
	DWORD dwToThreadID = lpNavigatePackage->m_dwThreadID;
	Fire_OnNavigate(dwToThreadID, CString(strUrl.c_str()));
}

void BrowserComunication::OnCreateAndNavigate(BasePackage* lpPackage)
{
	CreateAndNavigatePackage* lpChildPackage = dynamic_cast<CreateAndNavigatePackage*>(lpPackage);
	assert(lpChildPackage);

	Fire_OnCreateAndNavigate(lpChildPackage->m_hParentWnd, CString(lpChildPackage->m_strUrl.c_str()), lpChildPackage->m_dwMark);
}