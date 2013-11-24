#pragma once
#include "baseuserpackage.h"
#include "ByteStream.h"

//通常性的仅MsgID不同的发送到不同线程的package。。
template <DWORD dwMsgID>
class ThreadPackageT : public BasePackage
{
public:
	ThreadPackageT(void) : BasePackage(dwMsgID)
	{

	}
	virtual ~ThreadPackageT(void)
	{

	}

	size_t EncodeLogicBody(BYTE* pResult,size_t len)
	{
		int nowpos = 0;
		nowpos += ByteStream::WriteDword(pResult+nowpos,(DWORD)m_dwThreadID);
		return nowpos;
	}

	size_t DecodeLogicBody(const BYTE* pBuffer,size_t len)
	{
		int nowpos = 0;
		int readlen = 0;

		readlen = ByteStream::ReadDword(pBuffer+nowpos,(DWORD&)m_dwThreadID,len-nowpos);
		if(readlen <= 0)
		{
			return -1;
		}
		nowpos += readlen;

		return nowpos;
	}

	size_t GetLogicBodyLen()
	{
		return sizeof(m_dwThreadID);
	}
public:
	DWORD m_dwThreadID;
};

typedef ThreadPackageT<XBM_MSG_DESTROY> DestroyPackage;