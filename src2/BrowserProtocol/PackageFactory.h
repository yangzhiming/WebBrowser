#pragma once

#include "./BaseUserPackage.h"
#include "./ConnectPackage.h"
#include "./BrowserCreatedPackage.h"
#include "./NavigatePackage.h"
#include "./CommonPackageT.h"
#include "./CreateAndNavigatePackage.h"
#include "./ThreadPackageT.h"

class PackageFactory
{
public:
	virtual BasePackage* CreatePackage(const Header* pHeader) = 0;
};

class UserPackageFactory : public PackageFactory
{
public:
	virtual BasePackage* CreatePackage(const Header* pHeader)
	{
 		switch(pHeader->ulMsgID)
 		{
 			case XBM_MSG_CONNECT:
 				return new ConnectPackage();
 				break;
 			case XBM_MSG_BROWSERCREATED:
 				return new BrowserCreatedPackage();
 				break;
			case XBM_MSG_NAVIGATE:
				return new NavigatePackage();
				break;
			case XBM_MSG_PROCESSCREATED:
				return new ProcessCreatedPackage();
				break;
			case XBM_MSG_CREATEANDNAVIGATE:
				return new CreateAndNavigatePackage();
				break;
			case XBM_MSG_DESTROY:
				return new DestroyPackage();
				break;
			default:
				assert(false);
				break;
		}
		
		return NULL;
	}
};