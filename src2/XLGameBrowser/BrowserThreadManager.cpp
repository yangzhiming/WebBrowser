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

DWORD BrowserThreadManager::CreateBrowserThread(LPCTSTR strUrl)
{
	DWORD dwThreadID;
	BrowserThreadItem* lpBrowserThreadItem = new BrowserThreadItem();
	if(lpBrowserThreadItem->Create(dwThreadID, strUrl))
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
