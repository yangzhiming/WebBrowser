#pragma once
//********************************************************************************************
//
//			ä¯ÀÀÆ÷µ¥Ôª
//
//
//
//
//*********************************************************************************************//
class BrowserWnd;
class BrowserThreadItem
{
public:
	BrowserThreadItem(void);
	~BrowserThreadItem(void);

	virtual bool Create(DWORD& dwThreadID, HWND hParent, LPCTSTR strUrl, DWORD dwMark);
	virtual bool Destroy();

	BrowserWnd* GetBrowserWnd() const { return m_pBrowserWnd; }

protected:
	static unsigned int WINAPI BrowserWorkerThread(LPVOID param);
private:
	BrowserWnd*			m_pBrowserWnd;
	HANDLE				m_hThread;
	CString				m_strToNavigate;
	HWND                m_hParentWnd;
	DWORD               m_dwMark;
};
