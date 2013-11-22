#pragma once
//********************************************************************************************
//
//			ä¯ÀÀÆ÷Êµ´°¿Ú
//
//
//
//
//*********************************************************************************************//


#pragma once

#define WebBrowser_CLSID _T("{8856F961-340A-11D0-A96B-00C04FD705A2}")

class BrowserWnd : public CWindowImpl<BrowserWnd, CAxWindow>
{
public:
	BrowserWnd(void);
	virtual ~BrowserWnd(void);

	BEGIN_MSG_MAP(BrowserWnd)	
		MSG_WM_CREATE(OnCreate)
		MSG_WM_DESTROY(OnDestroy)
		MSG_WM_TIMER(OnTimer)
	END_MSG_MAP()

	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnDestroy();
	void OnTimer(UINT_PTR nIDEvent);

public:

	HWND CreateBrowserWnd(HWND hOwner);

	HRESULT Navigate(LPCTSTR pstrUrl,int nFlag = 0,LPCTSTR pTargetName = NULL,LPCTSTR pPostData = NULL,LPCTSTR pHeader = NULL);

private:

	HRESULT GetBrowser(IWebBrowser2** ppWebBrowser);
};
