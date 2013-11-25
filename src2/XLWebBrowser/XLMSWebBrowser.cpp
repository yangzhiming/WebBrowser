// XLMSWebBrowser.cpp : Implementation of CXLMSWebBrowser

#include "stdafx.h"
#include "XLMSWebBrowser.h"
#include "HostComunication.h"

unsigned long CXLMSWebBrowser::m_nextTaskCookie = 1;
// CXLMSWebBrowser
CXLMSWebBrowser::CXLMSWebBrowser()
{
	m_hParentWnd = NULL;
	m_dwThreadID = 0;
	m_dwProcessID = 0;
	m_dwState = UnCreated;
	m_bWaitForProcessCreate = FALSE;
	m_bWaitForBrowserCreate = FALSE;
}

HRESULT CXLMSWebBrowser::FinalConstruct()
{
	return S_OK;
}

void CXLMSWebBrowser::FinalRelease()
{

}

long CXLMSWebBrowser::GetNextMarkCookie()
{
	if (m_nextTaskCookie == (std::numeric_limits<unsigned long>::max)())
	{
		m_nextTaskCookie = 1;
	}

	return m_nextTaskCookie++;
}

BOOL CXLMSWebBrowser::Create(LONG dwProcessID, HWND hParentWnd)
{
	BOOL bHasConnection = HostComunication::Instance()->HasConnection(dwProcessID);
	if(!bHasConnection)
	{
		CreateNewBrowserProcess(hParentWnd);
	}
	else
	{
		CreateBrowserInProcess(dwProcessID, hParentWnd);
	}

	return TRUE;
}

BOOL CXLMSWebBrowser::CreateNewBrowserProcess(HWND hParentWnd)
{
	int nErr = 0;
	TCHAR szImgFilePath[MAX_PATH] = {0};
	if ( !GetModuleFileName( NULL, szImgFilePath, MAX_PATH ) )
	{
		nErr = GetLastError();
		return 1;
	}

	//缓存一下吧。。navaigate的时候再发过去
	m_hParentWnd = hParentWnd;
	
	TCHAR modulePath[MAX_PATH];
	GetModuleFileName( NULL, modulePath, MAX_PATH );
	CString strAppName(modulePath);
	int nPos = strAppName.ReverseFind(L'\\');
	strAppName = strAppName.Left(nPos);
	strAppName += "\\XLGameBrowser.exe";
	
	STARTUPINFO si;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	ZeroMemory( &pi, sizeof(pi) );

	// Start the child process. 
	if( !CreateProcess(strAppName.GetBuffer(), // No module name (use command line). 
		NULL,
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		NULL,             // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi )             // Pointer to PROCESS_INFORMATION structure.
		) 
	{
		strAppName.ReleaseBuffer();
		nErr = GetLastError();
		return FALSE;
	}

	m_dwProcessID = pi.dwProcessId;
	strAppName.ReleaseBuffer();
	return TRUE;
}

BOOL CXLMSWebBrowser::CreateBrowserInProcess(LONG dwProcessID, HWND hParentWnd)
{
	m_dwState = ProcessCreated;
	m_dwProcessID = dwProcessID;
	m_hParentWnd = hParentWnd;
	m_dwMark = GetNextMarkCookie();
	HostComunication::Instance()->NotifyBrowserCreateAndNavigate(m_dwProcessID, m_hParentWnd, m_dwMark, m_strToNavigate);

	return TRUE;
}

STDMETHODIMP CXLMSWebBrowser::Destroy(void)
{
	// TODO: 在此添加实现代码
	HostComunication::Instance()->NotifyBrowserDestroy(m_dwProcessID, m_dwThreadID);

	return S_OK;
}

STDMETHODIMP CXLMSWebBrowser::Navigate(BSTR url)
{
	// TODO: Add your implementation code here
	m_strToNavigate = url;
	switch(m_dwState)
	{
	case UnCreated:
		{
			m_bWaitForProcessCreate = TRUE;
		}
		break;
	case ProcessCreated:
		{
			//此处可能threadid尚未返回，需继续写代码保证
			m_bWaitForBrowserCreate = TRUE;
		}
		break;
	case BrowserCreated:
		{
			CString strUrl(url);
			HostComunication::Instance()->NotifyBrowserNavigate(m_dwProcessID, m_dwThreadID, strUrl);
		}
		break;
	default:
		assert(false);
		break;
	}
	
	return S_OK;
}

DWORD CXLMSWebBrowser::GetBrowserProcessID() const
{
	return m_dwProcessID;
}

DWORD CXLMSWebBrowser::GetBrowserThreadID() const
{
	return m_dwThreadID;
}

DWORD CXLMSWebBrowser::GetMarkCookie() const
{
	return m_dwMark;
}

void CXLMSWebBrowser::OnProcessCreated()
{
	m_dwState = ProcessCreated;

	if(m_bWaitForProcessCreate)
	{
		m_dwMark = GetNextMarkCookie();
		HostComunication::Instance()->NotifyBrowserCreateAndNavigate(m_dwProcessID, m_hParentWnd, m_dwMark, m_strToNavigate);
		m_bWaitForProcessCreate = FALSE;
	}
}

void CXLMSWebBrowser::OnBrowserCreated(DWORD dwThreadID)
{
	m_dwThreadID = dwThreadID;
	m_dwState = BrowserCreated;

	if(m_bWaitForBrowserCreate)
	{
		HostComunication::Instance()->NotifyBrowserNavigate(m_dwProcessID, m_dwThreadID, m_strToNavigate);
		m_bWaitForBrowserCreate = FALSE;
	}
}
