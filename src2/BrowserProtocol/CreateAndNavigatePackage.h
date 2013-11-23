#pragma once
#include "baseuserpackage.h"

//首次创建浏览器线程时发出。
//NavigatePackage则是在已经创建后再需要换url时候发出.
class CreateAndNavigatePackage : public BasePackage
{
public:
	CreateAndNavigatePackage(void);
	~CreateAndNavigatePackage(void);

	virtual size_t EncodeLogicBody(BYTE* pResult,size_t len);
	virtual size_t DecodeLogicBody(const BYTE* pBuffer,size_t len);
	virtual size_t GetLogicBodyLen();

public:
	std::string m_strUrl;
	HWND m_hParentWnd;
	DWORD m_dwMark;
};
