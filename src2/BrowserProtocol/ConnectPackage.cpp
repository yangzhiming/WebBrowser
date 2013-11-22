#include "StdAfx.h"
#include "ConnectPackage.h"
#include "./ByteStream.h"

ConnectPackage::ConnectPackage(void) : BasePackage(XBM_MSG_CONNECT)
{
	
}

ConnectPackage::~ConnectPackage(void)
{
}

size_t ConnectPackage::EncodeLogicBody(BYTE* pResult,size_t len)
{
	int nowpos = 0;
	nowpos += ByteStream::WriteDword(pResult+nowpos,(DWORD)hClientWnd);
	return nowpos;
}

size_t ConnectPackage::DecodeLogicBody(const BYTE* pBuffer,size_t len)
{
	int nowpos = 0;
	int readlen = 0;

	readlen = ByteStream::ReadDword(pBuffer+nowpos,(DWORD&)hClientWnd,len-nowpos);
	if(readlen <= 0)
	{
		return -1;
	}
	nowpos += readlen;

	return nowpos;
}

size_t ConnectPackage::GetLogicBodyLen()
{
	return sizeof(hClientWnd);
}