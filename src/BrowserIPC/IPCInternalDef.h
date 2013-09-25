#ifndef _IPC_INTERNAL_DEF_H_
#define _IPC_INTERNAL_DEF_H_

#define POOLSIZE	  (512*1024)		//»º³åÇø´óÐ¡ 

#define UM_IPC_EVENT  WM_USER+1  

enum IPC_OP_CODE
{
	OP_ACCEPT,
	OP_CONNECT,
	OP_RECV,
	OP_SEND,
};

class IPCSocket;
struct IPCOverlapped
{
	OVERLAPPED m_ol;
	HWND	   m_hWnd;
	DWORD      m_dwOpCode;
	IPCSocket* m_lpOwner;
};

struct IPCHeader
{
	unsigned long nLength;
};

#endif //_IPC_INTERNAL_DEF_H_