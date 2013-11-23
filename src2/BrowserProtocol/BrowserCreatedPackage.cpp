#include "StdAfx.h"
#include "BrowserCreatedPackage.h"
#include "ByteStream.h"

BrowserCreatedPackage::BrowserCreatedPackage() : BasePackage(XBM_MSG_BROWSERCREATED)
{
	
}

BrowserCreatedPackage::~BrowserCreatedPackage(void)
{
}

size_t BrowserCreatedPackage::EncodeLogicBody(BYTE* pResult,size_t len)
{
	int nowpos = 0;
	nowpos += ByteStream::WriteDword(pResult+nowpos, m_dwBrowserThreadID);
	nowpos += ByteStream::WriteDword(pResult+nowpos, m_dwMark);
	return nowpos;
}

size_t BrowserCreatedPackage::DecodeLogicBody(const BYTE* pBuffer,size_t len)
{
	int nowpos = 0;
	int readlen = 0;

	readlen = ByteStream::ReadDword(pBuffer+nowpos,m_dwBrowserThreadID,len-nowpos-sizeof(DWORD));
	if(readlen <= 0)
	{
		return -1;
	}
	nowpos += readlen;

	readlen = ByteStream::ReadDword(pBuffer+nowpos,m_dwMark,sizeof(DWORD));
	if(readlen <= 0)
	{
		return -1;
	}
	nowpos += readlen;

	return nowpos;
}

size_t BrowserCreatedPackage::GetLogicBodyLen()
{
	return sizeof(m_dwBrowserThreadID) + sizeof(DWORD);
}
