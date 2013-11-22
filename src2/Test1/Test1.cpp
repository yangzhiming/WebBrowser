// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../XLGameBrowser/BrowserComunication.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout<<"client start"<<std::endl;
	BrowserComunication::Instance()->Init();
	std::cout<<"client init Ok"<<std::endl;

	MSG msg;
	while(::GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return 0;
}

