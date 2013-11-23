#pragma once
#include "baseuserpackage.h"

/*
浏览器已创建的package
*/

class BrowserCreatedPackage : public BasePackage
{
public:
	BrowserCreatedPackage();
	virtual ~BrowserCreatedPackage(void);

	virtual size_t EncodeLogicBody(BYTE* pResult,size_t len);
	virtual size_t DecodeLogicBody(const BYTE* pBuffer,size_t len);
	virtual size_t GetLogicBodyLen();

public:
	DWORD m_dwBrowserThreadID;
	DWORD m_dwMark;
};
