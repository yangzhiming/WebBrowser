// XLWebBrowserManager.h : Declaration of the CXLWebBrowserManager

#pragma once
#include "resource.h"       // main symbols

#include "XLWebBrowser_i.h"
#include "XLMSWebBrowser.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

#include "HostComunication.h"

// CXLWebBrowserManager

class ATL_NO_VTABLE CXLWebBrowserManager :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CXLWebBrowserManager, &CLSID_XLWebBrowserManager>,
	public IDispatchImpl<IXLWebBrowserManager, &IID_IXLWebBrowserManager, &LIBID_XLWebBrowserLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IEventHandler
{
public:
	CXLWebBrowserManager();

DECLARE_REGISTRY_RESOURCEID(IDR_XLWEBBROWSERMANAGER)


BEGIN_COM_MAP(CXLWebBrowserManager)
	COM_INTERFACE_ENTRY(IXLWebBrowserManager)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

public:

	STDMETHOD(CreateBrowser)(LONG dwProcessID, LONG hParentWnd, IXLMSWebBrowser** ppMSWebBrowser);
	STDMETHOD(DestroyBrowser)(IXLMSWebBrowser* pMSWebBrowser);
	//这个方法估计没法用。。。外部不关心processid和threadid
	STDMETHOD(DestroyBrowser2)(LONG dwProcessID, LONG dwThreadID);

protected:
	virtual void OnConnect();
	virtual void OnProcessCreated(DWORD dwProcessID);
	virtual void OnBrowserCreated(DWORD dwProcessID, DWORD dwThreadID, DWORD dwMark);

private:
	std::list<CXLMSWebBrowser*> m_BrowserList;
};

OBJECT_ENTRY_AUTO(__uuidof(XLWebBrowserManager), CXLWebBrowserManager)
