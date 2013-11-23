#include "StdAfx.h"
#include "BrowserThreadManager.h"
#include "BrowserItem.h"
#include "BrowserComunication.h"
#include "BrowserWnd.h"

BrowserThreadManager::BrowserThreadManager(void)
{
}

BrowserThreadManager::~BrowserThreadManager(void)
{
}

DWORD BrowserThreadManager::CreateBrowserThread(HWND hParent, LPCTSTR strUrl, DWORD dwMark)
{
	DWORD dwThreadID;
	BrowserThreadItem* lpBrowserThreadItem = new BrowserThreadItem();
	if(lpBrowserThreadItem->Create(dwThreadID, hParent, strUrl, dwMark))
	{
		m_BrowserThreadItems.insert(std::make_pair(dwThreadID, lpBrowserThreadItem));
		return dwThreadID;
	}

	return 0;
}

void BrowserThreadManager::DestroyBrowserThread(DWORD dwThreadID)
{
	std::map<DWORD, BrowserThreadItem*>::iterator it = m_BrowserThreadItems.find(dwThreadID);
	if(it != m_BrowserThreadItems.end())
	{
		it->second->Destroy();
		m_BrowserThreadItems.erase(it);
	}
}

BrowserThreadItem* BrowserThreadManager::FindBrowserItem(DWORD dwThreadID)
{
	std::map<DWORD, BrowserThreadItem*>::iterator it = m_BrowserThreadItems.find(dwThreadID);
	if(it != m_BrowserThreadItems.end())
	{
		return it->second;
	}

	return NULL;
}	