// XLMSWebBrowser.h : Declaration of the CXLMSWebBrowser

#pragma once
#include "resource.h"       // main symbols

#include "XLWebBrowser_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CXLMSWebBrowser

class ATL_NO_VTABLE CXLMSWebBrowser :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CXLMSWebBrowser, &CLSID_XLMSWebBrowser>,
	public IDispatchImpl<IXLMSWebBrowser, &IID_IXLMSWebBrowser, &LIBID_XLWebBrowserLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
	enum BrowserState
	{
		UnCreated,
		ProcessCreated,
		BrowserCreated,
	};
public:
	CXLMSWebBrowser();

DECLARE_REGISTRY_RESOURCEID(IDR_XLMSWEBBROWSER)


BEGIN_COM_MAP(CXLMSWebBrowser)
	COM_INTERFACE_ENTRY(IXLMSWebBrowser)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

public:
	DWORD GetBrowserProcessID() const;
	DWORD GetBrowserThreadID() const;
	DWORD GetMarkCookie() const;

	virtual BOOL Create(LONG dwProcessID, HWND hParentWnd);
	virtual void OnProcessCreated();
	virtual void OnBrowserCreated(DWORD dwThreadID);

private:
	BOOL CreateNewBrowserProcess(HWND hParentWnd);
	BOOL CreateBrowserInProcess(LONG dwProcessID, HWND hParentWnd);

	static long GetNextMarkCookie();

public:
	STDMETHOD(Navigate)(BSTR url);
	STDMETHOD(Destroy)(void);

private:
	HWND m_hParentWnd;
	DWORD m_dwProcessID;
	DWORD m_dwThreadID;
	BrowserState m_dwState;
	BOOL m_bDelayNavigate;
	CString m_strToNavigate;
	DWORD m_dwMark;
	static unsigned long	m_nextTaskCookie;
};

OBJECT_ENTRY_AUTO(__uuidof(XLMSWebBrowser), CXLMSWebBrowser)

typedef CComObject<CXLMSWebBrowser> XLMSWebBrowserObjType;
typedef CComPtr<CXLMSWebBrowser> XLMSWebBrowserPtrType;
