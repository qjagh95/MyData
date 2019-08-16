#pragma once

enum class SocketType
{
	Tcp,
	Udp,
};
#ifndef _WIN32
// SOCKET�� 64bit ȯ�濡�� 64bit�̴�. �ݸ� linux������ ������ 32bit�̴�. �� ���̸� ����.
typedef int SOCKET;
#endif

class EndPoint;
class Socket
{
public:
	void Bind(const EndPoint& endpoint);
	void Connect(const EndPoint& endpoint);
	int Send(const char* data, int length);
	void Close();
	void Listen();
	int Accept(Socket& acceptedSocket, std::string& errorText);

	bool AcceptOverlapped(Socket& acceptCandidateSocket, std::string& errorText);
	int UpdateAcceptContext(Socket& listenSocket);
	EndPoint GetPeerAddr();
	int Receive();
	int ReceiveOverlapped();
	int SendOverlapped(const char* Data, int Length, Socket& sock);
	void SetNonblocking();
	std::string GetLastErrorAsString();
		
public:
	Socket();
	Socket(SOCKET sock);
	Socket(SocketType socketType);
	~Socket();

public:
	static const int MaxReceiveLength = 8192;
	SOCKET m_Socket; // ���� �ڵ�
	// AcceptEx �Լ� ������ AccpetEx�Լ��� ��ü�Ѵ�.
	LPFN_ACCEPTEX m_AcceptEx = NULL;

	// Overlapped I/O�� IOCP�� �� ������ ���˴ϴ�. ���� overlapped I/O ���̸� true�Դϴ�.
	bool m_isReadOverlapped = false;
	// Overlapped receive or accept�� �� �� ���Ǵ� overlapped ��ü�Դϴ�. 
	WSAOVERLAPPED m_ReadOverlappedStruct;
	WSAOVERLAPPED m_SendOverlappedStruct;
	// Receive�� ReceiveOverlapped�� ���� ���ŵǴ� �����Ͱ� ä������ ���Դϴ�.
	char m_receiveBuffer[MaxReceiveLength];
	// overlapped ������ �ϴ� ���� ���⿡ recv�� flags�� ���ϴ� ���� ä�����ϴ�. overlapped I/O�� ����Ǵ� ���� �� ���� �ǵ帮�� ������.
	DWORD m_readFlags = 0;
};

