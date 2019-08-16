#include "pch.h"
#include "MyIOCP.h"

MyIOCP::MyIOCP(int threadCount)
{
	m_hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, threadCount);
	m_threadCount = threadCount;
}

MyIOCP::~MyIOCP()
{
	CloseHandle(m_hIocp);
}

void MyIOCP::Wait(IocpEvents & output, int timeoutMs)
{
	BOOL r = GetQueuedCompletionStatusEx(m_hIocp, output.m_events, MaxEventCount, (ULONG*)&output.m_eventCount, timeoutMs, FALSE);

	if (!r)
		output.m_eventCount = 0;
}

// IOCP에 socket을 추가합니다.
void MyIOCP::Add(Socket & socket, void * userPtr)
{
	if (!CreateIoCompletionPort((HANDLE)socket.m_Socket, m_hIocp, (ULONG_PTR)userPtr, m_threadCount))
		throw Exception("IOCP add failed!");
}
