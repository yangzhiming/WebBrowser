#ifndef _IPC_CONNECTION_H_
#define _IPC_CONNECTION_H_

#include "IPCSocket.h"

class IPCConnection : public IPCSocket
{
	friend class IPCListener;
public:
	IPCConnection(void);
	IPCConnection(HANDLE hFile);
	~IPCConnection(void);

	bool AssociateIOCP();

	virtual long IPCConnect(IPCAddress& addrHost, void* userdata, OnIPCConnect lpfnCallBack);
	virtual long IPCSend(const char* lpData, unsigned long len, void* userdata, OnIPCSend lpfnCallBack);
	virtual long IPCRecv(char* lpBuff, unsigned long len, void* userdata, OnIPCRecv lpfnCallBack);
	virtual long IPCClose();

	virtual void OnSend(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered);
	virtual void OnRecv(IPCOverlapped* lpOverlapped, DWORD dwByteTransfered);
	virtual void OnConnect(IPCOverlapped* lpOverlapped);
	virtual void OnAccept(IPCOverlapped* lpOverlapped);

private:
	HANDLE				m_hFile;
	LPVOID				m_lpOnRecvUserData;
	LPVOID				m_lpOnConnUserData;
	LPVOID				m_lpOnSendUserData;
	char*				m_lpBufferRecv;
	const char*			m_lpBufferSend;

	OnIPCRecv			m_lpfnOnRecv;
	OnIPCSend			m_lpfnOnSend;
	OnIPCConnect		m_lpfnOnConnect;
};

#endif //_IPC_CONNECTION_H_