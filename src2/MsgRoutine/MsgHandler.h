#pragma once


class DefaultMsgHandler : public IMsgHandler
{
public:
	DefaultMsgHandler(void);
	virtual ~DefaultMsgHandler(void);

	virtual bool HandleMsg(DWORD dwMsgID, MsgStruct* pMsgStruct);
};

class SingleMsgHandler : public IMsgHandler
{
public:
	SingleMsgHandler(void);
	virtual ~SingleMsgHandler(void);

	virtual bool HandleMsg(DWORD dwMsgID, MsgStruct* pMsgStruct);

private:
	static DefaultMsgHandler m_DefaultHandler;
};

//组合消息路由类,负责消息的分发
class CompositeMsgHandler : public SingleMsgHandler
{
public:
	CompositeMsgHandler(void);
	virtual ~CompositeMsgHandler(void);

	virtual void AddHandler(IMsgHandler* pHandler);
	virtual void RemoveHandler(IMsgHandler* pHandler);
	virtual bool HandleMsg(DWORD dwMsgID, MsgStruct* pMsgStruct);

protected:
	std::list<IMsgHandler*>		m_HandlerList;
};