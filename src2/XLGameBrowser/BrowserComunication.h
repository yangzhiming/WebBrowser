#pragma once
//********************************************************************************************
//
//			浏览器通信实现部分
//
//
//
//
//*********************************************************************************************//
#include "../MsgRoutine/MsgManager.h"
#include "../BrowserProtocol/BaseUserPackage.h"
#include "../BrowserProtocol/PackageFactory.h"
#include "../BrowserProtocol/PackageParser.h"

struct IEventHandler
{
	virtual void OnNavigate(DWORD dwToThreadID, LPCTSTR strUrl) = 0;
	virtual void OnCreateAndNavigate(HWND hParentWnd, LPCTSTR strUrl, DWORD dwMark) = 0;
};

class BrowserComunication
{
public:
	static BrowserComunication* Instance()
	{
		static BrowserComunication instace;
		return &instace;
	}

	bool Init();
	bool Uninit();

	void AddEventHandler(IEventHandler* lpHandler);
	void RemoveEventHandler(IEventHandler* lpHandler);
	void Fire_OnNavigate(DWORD dwToThreadID, LPCTSTR strUrl);
	void Fire_OnCreateAndNavigate(HWND hParentWnd, LPCTSTR strUrl, DWORD dwMark);

	long ConnectHostComunity();
	long NotifyHostProcessCreated();
	long NotifyHostBrowserCreated(DWORD dwMark);

protected:
	BrowserComunication(void);
	~BrowserComunication(void);

	static void OnCommunication(const char* lpData, unsigned long len, void* userdata);
	void OnCommunication(const char* lpData, unsigned long len);

	void InternalSendPackage(BasePackage* lpPacakge);

	virtual void OnRecvRespPackage(BasePackage* lpPackage);

	void OnNavigate(BasePackage* lpPackage);
	void OnCreateAndNavigate(BasePackage* lpPackage);

private:
	MsgManager*		m_lpMsgManager;
	UserPackageParser* m_lpParser;
	UserPackageFactory* m_lpFactory;
	HWND			m_hHostCommunWnd;
	CAtlFileMapping<char> m_fileMapping;
	std::list<IEventHandler*> m_HandlerList;
};
