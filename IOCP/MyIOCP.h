#pragma once

class Socket;
class IocpEvents;
class MyIOCP // I/O Completion Port ��ü.
{
public:
	MyIOCP(int threadCount);
	~MyIOCP();

	HANDLE m_hIocp;
	int m_threadCount; // IOCP ������ �� ���� �߰��� ��� ���Ǵ� ��������...
	void Wait(IocpEvents &output, int timeoutMs);
	void Add(Socket& socket, void* userPtr);

	// 1ȸ�� GetQueuedCompletionStatus�� �ִ��� ������ �� �ִ� ���� ����
	static const int MaxEventCount = 1000;
};

// IOCP�� GetQueuedCompletionStatus�� ���� I/O �Ϸ��ȣ��
class IocpEvents
{
public:
	// GetQueuedCompletionStatus���� ������ �̺�Ʈ��
	OVERLAPPED_ENTRY m_events[MyIOCP::MaxEventCount];
	int m_eventCount;
};
