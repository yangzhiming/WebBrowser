#pragma once

#include "BrowserComunication.h"
//浏览器应用程序类
class BrowserEventHandler : public IEventHandler
{
public:
	virtual void OnNavigate(DWORD dwToThreadID, LPCTSTR strUrl);
	virtual void OnCreateAndNavigate(HWND hParentWnd, LPCTSTR strUrl, DWORD dwMark);
};

class BrowserApp
{
public:
	static BrowserApp* Instance()
	{
		static BrowserApp instance;
		return &instance;
	}

	void InitInstance();
	void ExitInstance();
	void Run();

protected:
	BrowserApp(void);
	~BrowserApp(void);

	BrowserEventHandler m_BrowserHandler;
};
