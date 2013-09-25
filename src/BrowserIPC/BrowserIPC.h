#ifndef _BROWSER_IPC_H_
#define _BROWSER_IPC_H_

#include "./IPCDef.h"

long		__stdcall IPCStartup();
long		__stdcall IPCCleanup();

HIPCSOCKET	__stdcall IPCNewListener();
long		__stdcall IPCBind(HIPCSOCKET hListener, IPCAddress& addrLocal);
long		__stdcall IPCListen(HIPCSOCKET hListener, int nMax);

long	    __stdcall IPCAccept(HIPCSOCKET hListener, 
								IPCAddress& addrClient, 
								void* userdata, 
								OnIPCAccept lpfnCallBack);

HIPCSOCKET  __stdcall IPCNewConnection();
long		__stdcall IPCConnect(HIPCSOCKET hConn, 
								 IPCAddress& addrHost,
								 void* userdata,
								 OnIPCConnect lpfnCallBack);

long		__stdcall IPCSend(HIPCSOCKET hConn, 
							  const char* lpData, 
							  unsigned long len,
							  void* userdata,
							  OnIPCSend lpfnCallBack);

long		__stdcall IPCRecv(HIPCSOCKET hConn, 
							  char* lpBuff, 
							  unsigned long len,
							  void* userdata,
							  OnIPCRecv lpfnCallBack);

long		__stdcall IPCClose(HIPCSOCKET hSocket);

#endif //_BROWSER_IPC_H_