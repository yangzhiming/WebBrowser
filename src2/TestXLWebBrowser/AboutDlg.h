// aboutdlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../XLWebBrowser/XLWebBrowser_i.h"
#include "../XLWebBrowser/XLWebBrowser_i.c"
#include <atlstr.h>
#include "resource.h"

IXLWebBrowserManager * g_pObject = NULL;
class CAboutDlg : public CDialogImpl<CAboutDlg>
{
public:
	CAboutDlg(DWORD dwProcessID)
	{
		m_dwProcessID = dwProcessID;
	}
	enum { IDD = IDD_ABOUTBOX };

	BEGIN_MSG_MAP(CAboutDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
		COMMAND_HANDLER(IDC_BUTTON1, BN_CLICKED, OnBnClickedButton1)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CenterWindow(GetParent());
 
 		g_pObject->CreateBrowser(m_dwProcessID, (LONG)m_hWnd, &m_pMSWebBrowser);
 		CComBSTR strUrl(L"www.baidu.com");
 		m_pMSWebBrowser->Navigate(strUrl);

		return TRUE;
	}

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		g_pObject->DestroyBrowser(m_pMSWebBrowser);

		EndDialog(wID);
		return 0;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 0L;
	}

private:
	IXLMSWebBrowser* m_pMSWebBrowser;
	DWORD m_dwProcessID;
public:
	LRESULT OnBnClickedButton1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CString strUrl;
		GetDlgItemText(IDC_EDIT1, strUrl);
		CComBSTR bstr = strUrl;
		m_pMSWebBrowser->Navigate(bstr);

		return 0L;
	}
};
