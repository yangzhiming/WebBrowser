#pragma once
#include "baseuserpackage.h"

/*
通常性的只是msgid不同的package
*/

template <DWORD dwMsgID>
class CommonPackageT : public BasePackage
{
public:
	CommonPackageT(void) : BasePackage(dwMsgID)
	{

	}
	virtual ~CommonPackageT(void)
	{

	}

	virtual size_t EncodeLogicBody(BYTE* pResult,size_t len)
	{
		return 0;
	}
	virtual size_t DecodeLogicBody(const BYTE* pBuffer,size_t len)
	{
		return 0;
	}
	virtual size_t GetLogicBodyLen()
	{
		return 0;
	}
};

typedef CommonPackageT<XBM_MSG_PROCESSCREATED> ProcessCreatedPackage;
typedef CommonPackageT<XBM_MSG_HOSTWNDSIZE> HostWndSizeChangePackage;