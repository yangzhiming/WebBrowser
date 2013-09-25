#include "StdAfx.h"
#include "BrowserWnd.h"

BrowserWnd::BrowserWnd(void)
{
}

BrowserWnd::~BrowserWnd(void)
{
}

HWND BrowserWnd::CreateBrowserWnd(HWND hOwner)
{
	CRect rect(200, 200, 800, 600);
	HWND hNewWnd = Create(hOwner, &rect, WebBrowser_CLSID, WS_CLIPSIBLINGS|WS_POPUP, WS_EX_TOOLWINDOW|WS_EX_NOACTIVATE);

	return hNewWnd;
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

	CAxWindow wnd = m_hWnd;
	CComPtr<IWebBrowser2> spWebBrowser;
	HRESULT hRet = wnd.QueryControl(IID_IWebBrowser2, (void**)&spWebBrowser);
	ATLASSERT(SUCCEEDED(hRet));

	return spWebBrowser.CopyTo(ppWebBrowser);
}