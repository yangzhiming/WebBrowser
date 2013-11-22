#pragma once
#include "baseuserpackage.h"

class NavigatePackage : public BasePackage
{
public:
	NavigatePackage();
	virtual ~NavigatePackage(void);

	virtual size_t EncodeLogicBody(BYTE* pResult,size_t len);
	virtual size_t DecodeLogicBody(const BYTE* pBuffer,size_t len);
	virtual size_t GetLogicBodyLen();

public:
	std::string m_strUrl;
	HWND m_hParentWnd;
};
