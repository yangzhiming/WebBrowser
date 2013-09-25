#ifndef _IPC_SOCKET_H_
#define _IPC_SOCKET_H_

#include "./IPCDef.h"
#include "./IPCInternalDef.h"

enum IPC_State
{
	State_Ready,
	State_Connected,
	State_Closed
};

class IPCSocket : public CWindowImpl<IPCSocket>
{
public:
	IPCSocket(void);
	virtual ~IPCSocket(void);

	BEGIN_MSG_MAP(IPCSocket)
		MESSAGE_HANDLER(UM_IPC_EVENT, OnIPCEvent)
	END_MSG_MAP()

	LRESULT OnIPCEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	virtual long IPCBind(IPCAddress& addr);
	virtual long IPCConnect(IPCAddress& addrHost, void* userdata, OnIPCConnect lpfnCallBack);
	virtual long IPCListen(int nMax);
	virtual long IPCAccept(IPCAddress& addrClient, void* userdata, OnIPCAccept lpfnCallBack);
	virtual long IPCSend(const char* lpData, unsigned long len, void* userdata, OnIPCSend lpfnCallBack);
	virtual long IPCRecv(char* lpBuff, unsigned long len, void* userdata, OnIPCRecv lpfnCallBack);
	virtual long IPCClose();

 	virtual void OnSend(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered);
 	virtual void OnRecv(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered);
	virtual void OnConnect(IPCOverlapped* lpOverlapped);
	virtual void OnAccept(IPCOverlapped* lpOverlapped);

	void SetState(int state);

protected:
	DWORD				m_dwState;
	IPCOverlapped		m_overlapped;
	IPCAddress			m_addrLocal;
	IPCAddress			m_addrRemote;
};

#endif //_IPC_SOCKET_H_
