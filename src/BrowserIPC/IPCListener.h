#ifndef _IPC_LISTENER_H_
#define _IPC_LISTENER_H_

#include "IPCSocket.h"

class IPCConnection;
class IPCListener : public IPCSocket
{
public:
	IPCListener(void);
	~IPCListener(void);

	virtual long IPCBind(IPCAddress& addr);
	virtual long IPCListen(int nMax);
	virtual long IPCAccept(IPCAddress& addrClient, void* userdata, OnIPCAccept lpfnCallBack);
	virtual long IPCClose();

	virtual void OnSend(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered);
	virtual void OnRecv(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered);
	virtual void OnConnect(IPCOverlapped* lpOverlapped);
	virtual void OnAccept(IPCOverlapped* lpOverlapped);

private:
	std::list<IPCConnection*>   m_connList;
	OnIPCAccept					m_lpfnOnAccept;
	LPVOID						m_lpUserData;
};

#endif //_IPC_LISTENER_H_
