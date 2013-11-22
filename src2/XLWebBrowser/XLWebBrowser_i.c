

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Fri Nov 22 16:18:02 2013
 */
/* Compiler settings for .\XLWebBrowser.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IXLMSWebBrowser,0xB6F6F890,0xF5AD,0x4EF5,0xBB,0xDB,0x02,0x96,0x45,0x1B,0x19,0xCA);


MIDL_DEFINE_GUID(IID, IID_IXLWebBrowserManager,0x117BEDB4,0x5D5F,0x473B,0xB6,0x2B,0x86,0x26,0x96,0x9C,0x25,0x2C);


MIDL_DEFINE_GUID(IID, LIBID_XLWebBrowserLib,0x73D0FE0C,0xD823,0x4246,0x93,0x2E,0xC3,0x8F,0x8E,0x84,0x5C,0x70);


MIDL_DEFINE_GUID(CLSID, CLSID_XLWebBrowserManager,0x6FBC42AA,0xD5FC,0x456E,0xB9,0x87,0x0A,0xCF,0xA3,0x96,0x63,0x42);


MIDL_DEFINE_GUID(CLSID, CLSID_XLMSWebBrowser,0xA70B5658,0x96B6,0x4B15,0xBD,0x8C,0xF7,0xFB,0x23,0x91,0xBE,0x51);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



