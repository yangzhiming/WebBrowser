// dllmain.h : Declaration of module class.

class CXLWebBrowserModule : public CAtlDllModuleT< CXLWebBrowserModule >
{
public :
	DECLARE_LIBID(LIBID_XLWebBrowserLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_XLWEBBROWSER, "{53A37E7F-368A-4CA5-A4D5-59F3843AA155}")
};

extern class CXLWebBrowserModule _AtlModule;
