#include "StdAfx.h"
#include "MsgHandler.h"

DefaultMsgHandler SingleMsgHandler::m_DefaultHandler;

SingleMsgHandler::SingleMsgHandler(void)
{

}

SingleMsgHandler::~SingleMsgHandler(void)
{

}

bool SingleMsgHandler::HandleMsg(DWORD dwMsgID, MsgStruct* pMsgStruct)
{
	return m_DefaultHandler.HandleMsg(dwMsgID, pMsgStruct);
}

CompositeMsgHandler::CompositeMsgHandler(void)
{

}

CompositeMsgHandler::~CompositeMsgHandler(void)
{

}

void CompositeMsgHandler::AddHandler(IMsgHandler* pHandler)
{
	std::list<IMsgHandler*>::iterator it = m_HandlerList.begin();
	for(; it != m_HandlerList.end(); it++)
	{
		if(*it == pHandler)
		{
			return;
		}
	}

	m_HandlerList.push_back(pHandler);
}

void CompositeMsgHandler::RemoveHandler(IMsgHandler* pHandler)
{
	std::list<IMsgHandler*>::iterator it = m_HandlerList.begin();
	for(; it != m_HandlerList.end(); it++)
	{
		if(*it == pHandler)
		{
			m_HandlerList.erase(it);
			break;
		}
	}
}

bool CompositeMsgHandler::HandleMsg(DWORD dwMsgID, MsgStruct* pMsgStruct)
{
	std::list<IMsgHandler*>::iterator it = m_HandlerList.begin();
	for(; it != m_HandlerList.end(); it++)
	{
		//一旦有为true的返回，表示中断消息路由
		if((*it)->HandleMsg(dwMsgID, pMsgStruct))
		{
			return true;
		}
	}

	return SingleMsgHandler::HandleMsg(dwMsgID, pMsgStruct);
}

DefaultMsgHandler::DefaultMsgHandler(void)
{

}

DefaultMsgHandler::~DefaultMsgHandler(void)
{

}

bool DefaultMsgHandler::HandleMsg(DWORD dwMsgID, MsgStruct* pMsgStruct)
{
	//
	return false;
}