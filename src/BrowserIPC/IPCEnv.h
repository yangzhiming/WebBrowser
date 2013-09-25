#ifndef _IPC_ENV_H_
#define _IPC_ENV_H_

class IPCEnv
{
public:
	static IPCEnv* Instance()
	{
		static IPCEnv instance;
		return &instance;
	}

	long IPCStartup();
	long IPCCleanup();

	bool AssociateHandle(HANDLE hFile);

protected:
	IPCEnv(void);
	~IPCEnv(void);

	bool IsRunning() const;
	void OnIoComplete(LPOVERLAPPED lpOverlapped, DWORD dwByteTransfered);

	static DWORD WINAPI WorkerThread(LPVOID lpParam);
	DWORD WorkerProc();

private:
	HANDLE		m_hThread;
	HANDLE		m_hIOCP;
	bool		m_bRunning;
};

#endif //_IPC_ENV_H_