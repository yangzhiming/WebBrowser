#include "StdAfx.h"
#include "BrowserWnd.h"
#include "BrowserComunication.h"

const UINT BrowserWnd::WM_BROWSER_QUIT = ::RegisterWindowMessage(L"WM_BROWSER_QUIT");

BrowserWnd::BrowserWnd(void)
{
	m_dwMark = 0;
}

BrowserWnd::~BrowserWnd(void)
{
}

void BrowserWnd::SetMark(DWORD dwMark)
{
	m_dwMark = dwMark;
}

HWND BrowserWnd::CreateBrowserWnd(HWND hOwner)
{
	CRect rect(200, 200, 800, 600);
	ATLASSERT(::IsWindow(hOwner));
	HWND hNewWnd = Create(hOwner, &rect, WebBrowser_CLSID, WS_CLIPSIBLINGS|WS_CHILD, WS_EX_TOOLWINDOW|WS_EX_NOACTIVATE);
	return hNewWnd;
}

void BrowserWnd::DestroyBrowserWnd()
{
	PostMessage(WM_BROWSER_QUIT, 0, 0);
}

HRESULT BrowserWnd::Navigate(LPCTSTR pstrUrl,int nFlag ,LPCTSTR pTargetName,LPCTSTR pPostData,LPCTSTR pHeader)
{
	if (pstrUrl == NULL)
	{
		return S_FALSE;
	}

	CString strUrl = pstrUrl;
	CComPtr<IWebBrowser2> spWebBrowser2;
	HRESULT hRet = GetBrowser(&spWebBrowser2);
	if(SUCCEEDED(hRet) && spWebBrowser2)
	{
		CComVariant vtURL(strUrl);
		CComVariant vtFlag(nFlag);
		CComVariant vtTargetName;
		if(pTargetName != NULL)
		{
			vtTargetName = pTargetName;
		}
		CComVariant vtPostData;
		if(pPostData != NULL)
		{
			vtPostData = pPostData;
		}
		CComVariant vtHeader;
		if(pHeader != NULL)
		{
			vtHeader = pHeader;
		}

		hRet = spWebBrowser2->Navigate2(&vtURL, &vtFlag, &vtTargetName, &vtPostData, &vtHeader);
	}

	return hRet;
}

HRESULT BrowserWnd::GetBrowser(IWebBrowser2** ppWebBrowser)
{
	ATLASSERT( ppWebBrowser ); 
	if ( ppWebBrowser == NULL ) 
	{
		return E_POINTER; 
	}

	*ppWebBrowser = NULL;

	//CAxWindow wnd = m_hWnd;
	CComPtr<IWebBrowser2> spWebBrowser;
	HRESULT hRet = this->QueryControl(IID_IWebBrowser2, (void**)&spWebBrowser);
	ATLASSERT(SUCCEEDED(hRet));

	return spWebBrowser.CopyTo(ppWebBrowser);
}

LRESULT BrowserWnd::OnBrowserQuit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0);
	SetMsgHandled(TRUE);
	return 0L;
}

void BrowserWnd::OnDestroy()
{
	//::PostQuitMessage(0);
}

int BrowserWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//操！这条还是必须的
	SetMsgHandled(FALSE);

	BrowserComunication::Instance()->NotifyHostBrowserCreated(m_dwMark);

	SetTimer(12345, 50, NULL);
	return 0;
}

void BrowserWnd::OnTimer(UINT_PTR nIDEvent)
{
	RECT rc;
	CWindow& wnd = GetParent();
	if(::IsWindow(wnd))
	{
		wnd.GetClientRect(&rc);

		MoveWindow(&rc);
	}
	else
	{
		ATLASSERT(FALSE);
	}
}