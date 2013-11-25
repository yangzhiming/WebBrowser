#include "StdAfx.h"
#include "HostComunication.h"
#include "../BrowserProtocol/ConnectPackage.h"
#include "../BrowserProtocol/CommonPackageT.h"
#include "../BrowserProtocol/NavigatePackage.h"
#include "../BrowserProtocol/ThreadPackageT.h"

HostComunication::HostComunication(void)
{
	m_lpMsgManager = new MsgManager();

	m_lpFactory = new UserPackageFactory();
	m_lpParser = new UserPackageParser(m_lpFactory);
}

HostComunication::~HostComunication(void)
{
}

bool HostComunication::Init()
{
	bool bRet = false;
	if(m_lpMsgManager)
	{
		bRet = m_lpMsgManager->Init();
		//m_lpMsgManager->AddMsgHandler(this);
		m_lpMsgManager->SetRecvDataCallBack(OnCommunication, (void*)this);
	}

	HRESULT hr = m_fileMapping.MapSharedMem(sizeof(HWND), L"XLWebBrowserHostWnd_FileMapping");
	if(SUCCEEDED(hr))
	{
		void* lpAddress = m_fileMapping.GetData();
		*((HWND*)lpAddress) = m_lpMsgManager->GetHwnd();
		bRet &= true;
	}

	return true;
}

bool HostComunication::Uninit()
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

void HostComunication::AddEventHandler(IEventHandler* lpHandler)
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

void HostComunication::RemoveEventHandler(IEventHandler* lpHandler)
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

bool HostComunication::HasConnection(DWORD dwProcessID)
{
	std::map<DWORD, HWND>::iterator it = m_BrowserConnHwnds.begin();
	for(; it != m_BrowserConnHwnds.end(); ++it)
	{
		if(it->first == dwProcessID)
			return true;
	}

	return false;
}

void HostComunication::Fire_ProcessCreated(DWORD dwProcessID)
{
	std::list<IEventHandler*>::iterator it = m_HandlerList.begin();
	for(; it != m_HandlerList.end(); ++it)
	{
		(*it)->OnProcessCreated(dwProcessID);
	}
}

void HostComunication::Fire_Connected()
{
	std::list<IEventHandler*>::iterator it = m_HandlerList.begin();
	for(; it != m_HandlerList.end(); ++it)
	{
		(*it)->OnConnect();
	}
}

void HostComunication::Fire_BrowserCreated(DWORD dwProcessID, DWORD dwThreadID, DWORD dwMark)
{
	std::list<IEventHandler*>::iterator it = m_HandlerList.begin();
	for(; it != m_HandlerList.end(); ++it)
	{
		(*it)->OnBrowserCreated(dwProcessID, dwThreadID, dwMark);
	}
}

void HostComunication::OnCommunication(const char* lpData, unsigned long len, void* userdata)
{
	HostComunication* lpThis = (HostComunication*)userdata;
	if(lpThis)
	{
		lpThis->OnCommunication(lpData, len);
	}
}

void HostComunication::OnCommunication(const char* lpData, unsigned long len)
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

void HostComunication::InternalSendPackageToProcess(DWORD dwProcessID, BasePackage* lpPackage)
{
	std::map<DWORD, HWND>::iterator it = m_BrowserConnHwnds.find(dwProcessID);
	if(it != m_BrowserConnHwnds.end())
	{
		int len = lpPackage->GetEncodeLen();
		BYTE* lpData = new BYTE[len];
		lpPackage->Encode(lpData, len);
		m_lpMsgManager->PostRemoteMessage(it->second, lpData, len);

		delete []lpData;
	}
}

long HostComunication::NotifyBrowserNavigate(DWORD dwProcessID, DWORD dwThreadID, LPCTSTR url)
{
	std::string strUrl = CStringA(url);
	NavigatePackage* lpPackage = new NavigatePackage();
	lpPackage->m_dwThreadID = dwThreadID;
	lpPackage->m_strUrl = strUrl;
	InternalSendPackageToProcess(dwProcessID, lpPackage);
	delete lpPackage;
	return 0;
}

long HostComunication::NotifyBrowserCreateAndNavigate(DWORD dwProcessID, HWND hParentWnd, DWORD dwMark, LPCTSTR url)
{
	std::string strUrl = CStringA(url);
	CreateAndNavigatePackage* lpPackage = new CreateAndNavigatePackage();
	lpPackage->m_hParentWnd = hParentWnd;
	lpPackage->m_dwMark = dwMark;
	lpPackage->m_strUrl = strUrl;
	InternalSendPackageToProcess(dwProcessID, lpPackage);
	delete lpPackage;
	return 0;
}

long HostComunication::NotifyBrowserDestroy(DWORD dwProcessID, DWORD dwThreadID)
{
	DestroyPackage * lpPackage = new DestroyPackage();
	lpPackage->m_dwThreadID = dwThreadID;
	InternalSendPackageToProcess(dwProcessID, lpPackage);
	delete lpPackage;
	return 0;
}

void HostComunication::OnRecvRespPackage(BasePackage* lpPackage)
{
	DWORD dwMsgID = lpPackage->GetMessageID();
	switch(dwMsgID)
	{
	case XBM_MSG_CONNECT:
		OnConnect(lpPackage);
		break;
	case XBM_MSG_BROWSERCREATED:
		OnBrowserCreate(lpPackage);
		break;
	case XBM_MSG_PROCESSCREATED:
		OnProcessCreated(lpPackage);
		break;
	default:
		assert(false);
		break;
	}

	delete lpPackage;
}

void HostComunication::OnConnect(BasePackage* lpPackage)
{
	//建立起连接后，记录一下远程的通信窗口句柄
	ConnectPackage* lpConnPackage = dynamic_cast<ConnectPackage*>(lpPackage);
	assert(lpConnPackage);
	DWORD dwProcessID = lpConnPackage->GetProcessID();
	HWND hConnWnd = lpConnPackage->hClientWnd;
	m_BrowserConnHwnds.insert(std::make_pair(dwProcessID, hConnWnd));

	Fire_Connected();
}

void HostComunication::OnBrowserCreate(BasePackage* lpPackage)
{
	BrowserCreatedPackage* lpBrowserCreatedPackage = dynamic_cast<BrowserCreatedPackage*>(lpPackage);
	assert(lpPackage);

	DWORD dwProcessID = lpBrowserCreatedPackage->GetProcessID();
	DWORD dwThreadID = lpBrowserCreatedPackage->m_dwBrowserThreadID;
	DWORD dwMark = lpBrowserCreatedPackage->m_dwMark;
	Fire_BrowserCreated(dwProcessID, dwThreadID, dwMark);
}

void HostComunication::OnProcessCreated(BasePackage* lpPackage)
{
	ProcessCreatedPackage* lpProcessPackage = dynamic_cast<ProcessCreatedPackage*>(lpPackage);
	assert(lpPackage);

	DWORD dwProcessID = lpProcessPackage->GetProcessID();
	Fire_ProcessCreated(dwProcessID);
}
