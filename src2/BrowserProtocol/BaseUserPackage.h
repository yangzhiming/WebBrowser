#pragma once

struct Header
{
	unsigned long ulMsgID;		//msg id
	unsigned long ulProcessID;  //process id
	unsigned long ulResevered;  //Ô¤Áô×Ö¶Î
};

class BasePackage
{
public:
	BasePackage(DWORD dwMsgID);
	virtual ~BasePackage();
	
public:
	Header PackageHeader;

public:
	DWORD GetMessageID()
	{
		return PackageHeader.ulMsgID;
	}

	DWORD GetProcessID()
	{
		return PackageHeader.ulProcessID;
	}

	size_t GetEncodeLen()
	{
		return sizeof(Header) + GetLogicBodyLen();
	}
	
	//±àÂë
	size_t Encode(BYTE* pResult,size_t len)
	{
		Header* pHeader = (Header*) pResult;
		*pHeader = PackageHeader;
		
		size_t bodylen = EncodeLogicBody(pResult + sizeof(Header),len - sizeof(Header));
		return bodylen + sizeof(Header);
	}
	
	//½âÂë
	size_t Decode(BYTE* pResult,size_t len)
	{
		Header* pHeader = (Header*) pResult;
		PackageHeader = *pHeader;

		size_t bodylen = DecodeLogicBody(pResult + sizeof(Header), len - sizeof(Header));
		return bodylen + sizeof(Header);
	}
public:
	virtual size_t GetLogicBodyLen() = 0;
	virtual size_t EncodeLogicBody(BYTE* pResult,size_t len) = 0;
	virtual size_t DecodeLogicBody(const BYTE* pBuffer,size_t len) = 0;
};