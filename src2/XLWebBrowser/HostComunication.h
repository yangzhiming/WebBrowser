#pragma once

#include "../MsgRoutine/MsgManager.h"
#include "../BrowserProtocol/BaseUserPackage.h"
#include "../BrowserProtocol/PackageFactory.h"
#include "../BrowserProtocol/PackageParser.h"

struct IEventHandler
{
	virtual void OnConnect() = 0;
	virtual void OnProcessCreated(DWORD dwProcessID) = 0;
	virtual void OnBrowserCreated(DWORD dwProcessID, DWORD dwThreadID, DWORD dwMark) = 0;
};

class HostComunication
{
public:
	static HostComunication* Instance()
	{
		static HostComunication instance;
		return &instance;
	}

	virtual bool Init();
	virtual bool Uninit();

	long NotifyBrowserNavigate(DWORD dwProcessID, DWORD dwThreadID, LPCTSTR url);
	long NotifyBrowserCreateAndNavigate(DWORD dwProcessID, HWND hParentWnd, DWORD dwMark, LPCTSTR url);
	long NotifyBrowserDestroy(DWORD dwProcessID, DWORD dwThreadID);

	void AddEventHandler(IEventHandler* lpHandler);
	void RemoveEventHandler(IEventHandler* lpHandler);
	void Fire_ProcessCreated(DWORD dwProcessID);
	void Fire_Connected();
	void Fire_BrowserCreated(DWORD dwProcessID, DWORD dwThreadID, DWORD dwMark);

	bool HasConnection(DWORD dwProcessID);

protected:
	HostComunication(void);
	~HostComunication(void);

	static void OnCommunication(const char* lpData, unsigned long len, void* userdata);
	void OnCommunication(const char* lpData, unsigned long len);

	void InternalSendPackageToProcess(DWORD dwProcessID, BasePackage* lpPackage);
	virtual void OnRecvRespPackage(BasePackage* lpPackage);
protected:
	void OnConnect(BasePackage* lpPackage);
	void OnBrowserCreate(BasePackage* lpPackage);
	void OnProcessCreated(BasePackage* lpPackage);

private:
	MsgManager* m_lpMsgManager;
	UserPackageParser* m_lpParser;
	UserPackageFactory* m_lpFactory;
	std::map<DWORD, HWND> m_BrowserConnHwnds;
	CAtlFileMapping<char> m_fileMapping;
	std::list<IEventHandler*> m_HandlerList;
};
