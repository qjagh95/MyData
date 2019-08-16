#pragma once

enum class SocketType
{
	Tcp,
	Udp,
};
#ifndef _WIN32
// SOCKET은 64bit 환경에서 64bit이다. 반면 linux에서는 여전히 32bit이다. 이 차이를 위함.
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
	SOCKET m_Socket; // 소켓 핸들
	// AcceptEx 함수 포인터 AccpetEx함수를 대체한다.
	LPFN_ACCEPTEX m_AcceptEx = NULL;

	// Overlapped I/O나 IOCP를 쓸 때에만 사용됩니다. 현재 overlapped I/O 중이면 true입니다.
	bool m_isReadOverlapped = false;
	// Overlapped receive or accept을 할 때 사용되는 overlapped 객체입니다. 
	WSAOVERLAPPED m_ReadOverlappedStruct;
	WSAOVERLAPPED m_SendOverlappedStruct;
	// Receive나 ReceiveOverlapped에 의해 수신되는 데이터가 채워지는 곳입니다.
	char m_receiveBuffer[MaxReceiveLength];
	// overlapped 수신을 하는 동안 여기에 recv의 flags에 준하는 값이 채워집니다. overlapped I/O가 진행되는 동안 이 값을 건드리지 마세요.
	DWORD m_readFlags = 0;
};

