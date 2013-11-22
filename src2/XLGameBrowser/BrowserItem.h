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

	virtual bool Create(DWORD& dwThreadID, LPCTSTR strUrl);
	virtual bool Destroy();

protected:
	static unsigned int WINAPI BrowserWorkerThread(LPVOID param);
private:
	BrowserWnd*			m_pBrowserWnd;
	HANDLE				m_hThread;
	CString				m_strToNavigate;
};
