#pragma once

#define WebBrowser_CLSID _T("{8856F961-340A-11D0-A96B-00C04FD705A2}")

class BrowserWnd : public CWindowImpl<BrowserWnd, CAxWindow>
{
public:
	BrowserWnd(void);
	virtual ~BrowserWnd(void);

	BEGIN_MSG_MAP(BrowserWnd)	
	END_MSG_MAP()

public:

	HWND CreateBrowserWnd(HWND hOwner);

	HRESULT Navigate(LPCTSTR pstrUrl,int nFlag = 0,LPCTSTR pTargetName = NULL,LPCTSTR pPostData = NULL,LPCTSTR pHeader = NULL);

private:

	HRESULT GetBrowser(IWebBrowser2** ppWebBrowser);
};
