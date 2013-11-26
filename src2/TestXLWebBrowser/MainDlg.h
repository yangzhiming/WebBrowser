// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AboutDlg.h"

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler
{
public:
	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_CLOSE, OnClose)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
//		MESSAGE_HANDLER(WM_SIZE, OnSize)
COMMAND_HANDLER(IDC_BUTTON1, BN_CLICKED, OnBnClickedButton1)
COMMAND_HANDLER(IDC_BUTTON2, BN_CLICKED, OnBnClickedButton2)
COMMAND_HANDLER(IDC_BUTTON3, BN_CLICKED, OnBnClickedButton3)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
			IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
		SetIcon(hIconSmall, FALSE);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		UIAddChildWindowContainer(m_hWnd);

		HRESULT hr;

 		hr = CoCreateInstance(CLSID_XLWebBrowserManager, NULL, CLSCTX_INPROC_SERVER, IID_IXLWebBrowserManager, (LPVOID*)&g_pObject);
 		if(FAILED(hr))
 		{
 			ATLASSERT(FALSE);
 		}
 
 		g_pObject->CreateBrowser(0, (LONG)m_hWnd, &m_pMSWebBrowser);
 		
		CComBSTR strUrl(L"www.baidu.com");
		m_pMSWebBrowser->Navigate(strUrl);

//		SetTimer(23232, 15000, NULL);

		return TRUE;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// unregister message filtering and idle updates	
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

		return 0;
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int dwProcessID;
		dwProcessID = GetDlgItemInt(IDC_EDIT2);
		CAboutDlg dlg(dwProcessID);
		dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add validation code 
		CloseDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CloseDialog(wID);
		return 0;
	}

	void CloseDialog(int nVal)
	{
		if(m_pMSWebBrowser)
		{
			g_pObject->DestroyBrowser(m_pMSWebBrowser);
			m_pMSWebBrowser = NULL;
		}

		g_pObject->Release();

		DestroyWindow();
		::PostQuitMessage(nVal);
	}
// 	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
// 	{
// 		return 0;
// 	}
	LRESULT OnBnClickedButton1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		int dwProcessID;
		dwProcessID = GetDlgItemInt(IDC_EDIT2);
		CAboutDlg dlg(dwProcessID);
		dlg.DoModal();
		return 0L;
	}

	LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
// 		if(m_pMSWebBrowser)
// 		{
// 			g_pObject->DestroyBrowser(m_pMSWebBrowser);
// 			m_pMSWebBrowser = NULL;
// 		}

		return 0L;
	}

	LRESULT OnBnClickedButton2(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
 		if(m_pMSWebBrowser)
 		{
 			g_pObject->DestroyBrowser(m_pMSWebBrowser);
 			m_pMSWebBrowser = NULL;
 		}

		g_pObject->Release();

		DestroyWindow();
		::PostQuitMessage(0);
		return 0L;
	}

	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
//  		if(m_pMSWebBrowser)
//  		{
//  			g_pObject->DestroyBrowser(m_pMSWebBrowser);
//  			m_pMSWebBrowser = NULL;
//  		}

		bHandled = FALSE;

		return 0L;
	}

	LRESULT OnBnClickedButton3(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		if(m_pMSWebBrowser)
		{
			CString strUrl;
			GetDlgItemText(IDC_EDIT1, strUrl);
			CComBSTR strBstr = strUrl;
			m_pMSWebBrowser->Navigate(strBstr);
		}
		return 0L;
	}

private:
	IXLMSWebBrowser* m_pMSWebBrowser;
};
