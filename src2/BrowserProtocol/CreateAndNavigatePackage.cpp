#include "StdAfx.h"
#include "CreateAndNavigatePackage.h"
#include "ByteStream.h"

CreateAndNavigatePackage::CreateAndNavigatePackage() : BasePackage(XBM_MSG_CREATEANDNAVIGATE)
{

}

CreateAndNavigatePackage::~CreateAndNavigatePackage(void)
{
}

size_t CreateAndNavigatePackage::EncodeLogicBody(BYTE* pResult,size_t len)
{
	int nowpos = 0;
	nowpos += ByteStream::WriteString(pResult+nowpos, m_strUrl);
	nowpos += ByteStream::WriteDword(pResult+nowpos, (DWORD)m_hParentWnd);
	nowpos += ByteStream::WriteDword(pResult+nowpos, (DWORD)m_dwMark);
	return nowpos;
}

size_t CreateAndNavigatePackage::DecodeLogicBody(const BYTE* pBuffer,size_t len)
{
	int nowpos = 0;
	int readlen = 0;

	readlen = ByteStream::ReadString(pBuffer+nowpos,m_strUrl,len-nowpos-2*sizeof(DWORD));
	if(readlen < 0)
	{
		return -1;
	}
	nowpos += readlen;

	readlen = ByteStream::ReadDword(pBuffer+nowpos, (DWORD&)m_hParentWnd,sizeof(DWORD));
	if(readlen < 0)
	{
		return -1;
	}
	nowpos += readlen;

	readlen = ByteStream::ReadDword(pBuffer+nowpos, (DWORD&)m_dwMark,sizeof(DWORD));
	if(readlen < 0)
	{
		return -1;
	}
	nowpos += readlen;

	return nowpos;
}

size_t CreateAndNavigatePackage::GetLogicBodyLen()
{
	return ByteStream::SizeOfString(m_strUrl) + sizeof(m_hParentWnd) + sizeof(m_dwMark);
}
