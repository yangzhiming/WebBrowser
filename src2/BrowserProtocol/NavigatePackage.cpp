#include "StdAfx.h"
#include "NavigatePackage.h"
#include "ByteStream.h"

NavigatePackage::NavigatePackage() : BasePackage(XBM_MSG_NAVIGATE)
{

}

NavigatePackage::~NavigatePackage(void)
{
}

size_t NavigatePackage::EncodeLogicBody(BYTE* pResult,size_t len)
{
	int nowpos = 0;
	nowpos += ByteStream::WriteString(pResult+nowpos, m_strUrl);
	nowpos += ByteStream::WriteDword(pResult+nowpos, (DWORD)m_hParentWnd);
	return nowpos;
}

size_t NavigatePackage::DecodeLogicBody(const BYTE* pBuffer,size_t len)
{
	int nowpos = 0;
	int readlen = 0;

	readlen = ByteStream::ReadString(pBuffer+nowpos,m_strUrl,len-nowpos-sizeof(DWORD));
	if(readlen <= 0)
	{
		return -1;
	}
	nowpos += readlen;

	readlen = ByteStream::ReadDword(pBuffer+nowpos, (DWORD&)m_hParentWnd,sizeof(DWORD));
	if(readlen <= 0)
	{
		return -1;
	}
	nowpos += readlen;

	return nowpos;
}

size_t NavigatePackage::GetLogicBodyLen()
{
	return ByteStream::SizeOfString(m_strUrl) + sizeof(HWND);
}
