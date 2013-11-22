#pragma once

#include "BaseUserPackage.h"
#include "PackageFactory.h"

class UserPackageParser
{
public:
	UserPackageParser(PackageFactory* pFactory);
	
public:
	//返回值: <0 出错 0 格式正确 
	int PushData(const BYTE* pBuffer,size_t len)
	{
		assert(pBuffer);
		assert(len >= sizeof(Header));

		if (len < sizeof(Header)) return -1;
		if (pBuffer == NULL) return -1;

		m_unparserData = pBuffer;
		m_unparserDataLen = len;
		return 0;
	}

	BasePackage* PopResultPackage()
	{
		assert(m_unparserData);
		assert(m_unparserDataLen >= sizeof(Header));

		if (m_unparserDataLen < sizeof(Header)) return NULL;
		if (m_unparserData == NULL) return NULL;

		BasePackage* package = CreatePackageFromHeader((Header*)m_unparserData);
		if (package)
		{
			package->Decode((BYTE*)m_unparserData, m_unparserDataLen);
		}

		return package;
	}
	
protected:
	BasePackage* CreatePackageFromHeader(const Header* pHeader)
	{
		return m_factory->CreatePackage(pHeader);
	}
	
protected:
	PackageFactory* m_factory;
	const BYTE* m_unparserData;
	size_t m_unparserDataLen;
};