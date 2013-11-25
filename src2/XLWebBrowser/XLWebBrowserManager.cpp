// XLWebBrowserManager.cpp : Implementation of CXLWebBrowserManager

#include "stdafx.h"
#include "XLWebBrowserManager.h"

// CXLWebBrowserManager
CXLWebBrowserManager::CXLWebBrowserManager()
{

}

HRESULT CXLWebBrowserManager::FinalConstruct()
{
	HostComunication::Instance()->Init();
	HostComunication::Instance()->AddEventHandler(this);
	return S_OK;
}

void CXLWebBrowserManager::FinalRelease()
{
	HostComunication::Instance()->Uninit();
}

STDMETHODIMP CXLWebBrowserManager::CreateBrowser(LONG dwProcessID, LONG hParentWnd, IXLMSWebBrowser** ppMSWebBrowser)
{
	// TODO: Add your implementation code here
	XLMSWebBrowserObjType* pMSWebBrowser = NULL;
	XLMSWebBrowserObjType::CreateInstance(&pMSWebBrowser);

	pMSWebBrowser->Create(dwProcessID, (HWND)hParentWnd);

	pMSWebBrowser->AddRef();
	CComPtr<IXLMSWebBrowser> spWebBrowser = pMSWebBrowser;
	spWebBrowser.CopyTo(ppMSWebBrowser);

	m_BrowserList.push_back(pMSWebBrowser);
	return S_OK;
}

STDMETHODIMP CXLWebBrowserManager::DestroyBrowser(IXLMSWebBrowser* pMSWebBrowser)
{
	// TODO: 在此添加实现代码
	ATLASSERT(pMSWebBrowser);
	if(pMSWebBrowser)
	{
		pMSWebBrowser->Destroy();
	}

	return S_OK;
}

STDMETHODIMP CXLWebBrowserManager::DestroyBrowser2(LONG dwProcessID, LONG dwThreadID)
{
	// TODO: 在此添加实现代码
 	std::list<CXLMSWebBrowser*>::iterator it = m_BrowserList.begin();
 	for(; it != m_BrowserList.end(); ++it)
 	{
 		if((*it)->GetBrowserProcessID() == dwProcessID && (*it)->GetBrowserThreadID() == dwThreadID)
 		{
 			(*it)->Destroy();
 			break;
 		}
 	}

	return S_OK;
}

void CXLWebBrowserManager::OnConnect()
{

}

void CXLWebBrowserManager::OnProcessCreated(DWORD dwProcessID)
{
	std::list<CXLMSWebBrowser*>::iterator it = m_BrowserList.begin();
	for(; it != m_BrowserList.end(); ++it)
	{
		//理论上是会找到多个processid的，如果存在单进程多个浏览器的话。
		//但是通常只有第一个创建进程的浏览器收到此事件，其他的直接在此进程创建的浏览器，不收到此事件...
		if((*it)->GetBrowserProcessID() == dwProcessID)
		{
			(*it)->OnProcessCreated();
			break;
		}
	}
}

void CXLWebBrowserManager::OnBrowserCreated(DWORD dwProcessID, DWORD dwThreadID, DWORD dwMark)
{
	std::list<CXLMSWebBrowser*>::iterator it = m_BrowserList.begin();
	for(; it != m_BrowserList.end(); ++it)
	{
		if((*it)->GetBrowserProcessID() == dwProcessID && (*it)->GetMarkCookie() == dwMark)
		{
			(*it)->OnBrowserCreated(dwThreadID);
			break;
		}
	}
}
