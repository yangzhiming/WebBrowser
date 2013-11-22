#pragma once
#include "./BaseUserPackage.h"

/*
连接宿主通信端的package
*/

class ConnectPackage : public BasePackage
{
public:
	ConnectPackage();
	virtual ~ConnectPackage(void);

	virtual size_t EncodeLogicBody(BYTE* pResult,size_t len);
	virtual size_t DecodeLogicBody(const BYTE* pBuffer,size_t len);
	virtual size_t GetLogicBodyLen();

public:
	HWND hClientWnd;
};
