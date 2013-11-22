#pragma once

class MsgWindow : public CWindowImpl<MsgWindow>
{
public:
	MsgWindow(void);
	~MsgWindow(void);

	void SetOwner(void* pOwner) { m_lpOwner = pOwner; }

protected:
	virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
		LRESULT& lResult, DWORD dwMsgMapID);

private:
	void* m_lpOwner;
};
