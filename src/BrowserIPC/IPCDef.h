#ifndef _IPC_DEF_H_
#define _IPC_DEF_H_

typedef void* HIPCSOCKET;

struct IPCAddress
{
	unsigned long uPid;
	unsigned long uPort;
};

typedef void (*OnIPCAccept)(HIPCSOCKET hListener, HIPCSOCKET hConn, IPCAddress* lpAddrClient, void* userdata);
typedef void (*OnIPCSend)(HIPCSOCKET hConn, const char* lpData, unsigned long len, void* userdata);
typedef void (*OnIPCRecv)(HIPCSOCKET hConn, const char* lpData, unsigned long len, void* userdata);
typedef void (*OnIPCConnect)(HIPCSOCKET hConn, IPCAddress* lpAddrHost, void* userdata);

#endif //_IPC_DEF_H_