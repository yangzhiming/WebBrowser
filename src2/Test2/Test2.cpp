// Test2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../XLWebBrowser/HostComunication.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout<<"server start"<<std::endl;

	HostComunication::Instance()->Init();

	std::cout<<"server init Ok"<<std::endl;
	MSG msg;
	while(::GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	return 0;
}

