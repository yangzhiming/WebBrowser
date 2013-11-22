#include "stdafx.h"
#include "BaseUserPackage.h"

BasePackage::BasePackage(DWORD dwMsgID)
{
	RtlZeroMemory(&PackageHeader, sizeof(Header));
	PackageHeader.ulMsgID = dwMsgID;
	PackageHeader.ulProcessID = ::GetCurrentProcessId();
}

BasePackage::~BasePackage(void)
{

}