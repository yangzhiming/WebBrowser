

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Tue Nov 26 11:29:12 2013
 */
/* Compiler settings for ..\XLWebBrowser\XLWebBrowser.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __TestXLWebBrowser_h__
#define __TestXLWebBrowser_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IXLMSWebBrowser_FWD_DEFINED__
#define __IXLMSWebBrowser_FWD_DEFINED__
typedef interface IXLMSWebBrowser IXLMSWebBrowser;
#endif 	/* __IXLMSWebBrowser_FWD_DEFINED__ */


#ifndef __IXLWebBrowserManager_FWD_DEFINED__
#define __IXLWebBrowserManager_FWD_DEFINED__
typedef interface IXLWebBrowserManager IXLWebBrowserManager;
#endif 	/* __IXLWebBrowserManager_FWD_DEFINED__ */


#ifndef __XLWebBrowserManager_FWD_DEFINED__
#define __XLWebBrowserManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class XLWebBrowserManager XLWebBrowserManager;
#else
typedef struct XLWebBrowserManager XLWebBrowserManager;
#endif /* __cplusplus */

#endif 	/* __XLWebBrowserManager_FWD_DEFINED__ */


#ifndef __XLMSWebBrowser_FWD_DEFINED__
#define __XLMSWebBrowser_FWD_DEFINED__

#ifdef __cplusplus
typedef class XLMSWebBrowser XLMSWebBrowser;
#else
typedef struct XLMSWebBrowser XLMSWebBrowser;
#endif /* __cplusplus */

#endif 	/* __XLMSWebBrowser_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IXLMSWebBrowser_INTERFACE_DEFINED__
#define __IXLMSWebBrowser_INTERFACE_DEFINED__

/* interface IXLMSWebBrowser */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IXLMSWebBrowser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B6F6F890-F5AD-4EF5-BBDB-0296451B19CA")
    IXLMSWebBrowser : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Navigate( 
            /* [in] */ BSTR url) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Destroy( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXLMSWebBrowserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXLMSWebBrowser * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXLMSWebBrowser * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXLMSWebBrowser * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXLMSWebBrowser * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXLMSWebBrowser * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXLMSWebBrowser * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXLMSWebBrowser * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Navigate )( 
            IXLMSWebBrowser * This,
            /* [in] */ BSTR url);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Destroy )( 
            IXLMSWebBrowser * This);
        
        END_INTERFACE
    } IXLMSWebBrowserVtbl;

    interface IXLMSWebBrowser
    {
        CONST_VTBL struct IXLMSWebBrowserVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXLMSWebBrowser_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IXLMSWebBrowser_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IXLMSWebBrowser_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IXLMSWebBrowser_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IXLMSWebBrowser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IXLMSWebBrowser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IXLMSWebBrowser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IXLMSWebBrowser_Navigate(This,url)	\
    ( (This)->lpVtbl -> Navigate(This,url) ) 

#define IXLMSWebBrowser_Destroy(This)	\
    ( (This)->lpVtbl -> Destroy(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IXLMSWebBrowser_INTERFACE_DEFINED__ */


#ifndef __IXLWebBrowserManager_INTERFACE_DEFINED__
#define __IXLWebBrowserManager_INTERFACE_DEFINED__

/* interface IXLWebBrowserManager */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IXLWebBrowserManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("117BEDB4-5D5F-473B-B62B-8626969C252C")
    IXLWebBrowserManager : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateBrowser( 
            /* [in] */ LONG dwProcessID,
            /* [in] */ LONG hParentWnd,
            /* [in] */ IXLMSWebBrowser **ppMSWebBrowser) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DestroyBrowser2( 
            /* [in] */ LONG dwProcessID,
            /* [in] */ LONG dwThreadID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DestroyBrowser( 
            /* [in] */ IXLMSWebBrowser *pMSWebBrowser) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXLWebBrowserManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IXLWebBrowserManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IXLWebBrowserManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IXLWebBrowserManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IXLWebBrowserManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IXLWebBrowserManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IXLWebBrowserManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IXLWebBrowserManager * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateBrowser )( 
            IXLWebBrowserManager * This,
            /* [in] */ LONG dwProcessID,
            /* [in] */ LONG hParentWnd,
            /* [in] */ IXLMSWebBrowser **ppMSWebBrowser);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DestroyBrowser2 )( 
            IXLWebBrowserManager * This,
            /* [in] */ LONG dwProcessID,
            /* [in] */ LONG dwThreadID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DestroyBrowser )( 
            IXLWebBrowserManager * This,
            /* [in] */ IXLMSWebBrowser *pMSWebBrowser);
        
        END_INTERFACE
    } IXLWebBrowserManagerVtbl;

    interface IXLWebBrowserManager
    {
        CONST_VTBL struct IXLWebBrowserManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXLWebBrowserManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IXLWebBrowserManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IXLWebBrowserManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IXLWebBrowserManager_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IXLWebBrowserManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IXLWebBrowserManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IXLWebBrowserManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IXLWebBrowserManager_CreateBrowser(This,dwProcessID,hParentWnd,ppMSWebBrowser)	\
    ( (This)->lpVtbl -> CreateBrowser(This,dwProcessID,hParentWnd,ppMSWebBrowser) ) 

#define IXLWebBrowserManager_DestroyBrowser2(This,dwProcessID,dwThreadID)	\
    ( (This)->lpVtbl -> DestroyBrowser2(This,dwProcessID,dwThreadID) ) 

#define IXLWebBrowserManager_DestroyBrowser(This,pMSWebBrowser)	\
    ( (This)->lpVtbl -> DestroyBrowser(This,pMSWebBrowser) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IXLWebBrowserManager_INTERFACE_DEFINED__ */



#ifndef __XLWebBrowserLib_LIBRARY_DEFINED__
#define __XLWebBrowserLib_LIBRARY_DEFINED__

/* library XLWebBrowserLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_XLWebBrowserLib;

EXTERN_C const CLSID CLSID_XLWebBrowserManager;

#ifdef __cplusplus

class DECLSPEC_UUID("6FBC42AA-D5FC-456E-B987-0ACFA3966342")
XLWebBrowserManager;
#endif

EXTERN_C const CLSID CLSID_XLMSWebBrowser;

#ifdef __cplusplus

class DECLSPEC_UUID("A70B5658-96B6-4B15-BD8C-F7FB2391BE51")
XLMSWebBrowser;
#endif
#endif /* __XLWebBrowserLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


