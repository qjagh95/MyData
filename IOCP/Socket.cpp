#include "pch.h"
#include "Socket.h"

Socket::Socket()
{	
	static_assert(-1 == INVALID_SOCKET, "");
	m_Socket = -1;
	ZeroMemory(&m_ReadOverlappedStruct, sizeof(m_ReadOverlappedStruct));
}

Socket::Socket(SOCKET sock)
{
	m_Socket = sock;

#ifdef _WIN32
	ZeroMemory(&m_ReadOverlappedStruct, sizeof(m_ReadOverlappedStruct));
#endif
}

Socket::Socket(SocketType socketType)
{
	// overlapped I/O를 쓰려면 socket() 말고 WSASocket을 써야 합니다.
	if (socketType == SocketType::Tcp)
		m_Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	else
		m_Socket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	ZeroMemory(&m_ReadOverlappedStruct, sizeof(m_ReadOverlappedStruct));
}


Socket::~Socket()
{
	Close();
}

void Socket::Bind(const EndPoint & endpoint)
{
	if (bind(m_Socket, (sockaddr*)&endpoint.m_IPv4Endpoint, sizeof(endpoint.m_IPv4Endpoint)))
	{
		std::stringstream ss;
		ss << "bind failed:" << GetLastErrorAsString();
		throw Exception(ss.str().c_str());
	}
}

void Socket::Connect(const EndPoint & endpoint)
{
	// endpoint가 가리키는 주소로의 접속을 합니다.
	if (connect(m_Socket, (sockaddr*)&endpoint.m_IPv4Endpoint, sizeof(endpoint.m_IPv4Endpoint)) < 0)
	{
		std::stringstream ss;
		ss << "connect failed:" << GetLastErrorAsString();
		throw Exception(ss.str().c_str());
	}
}

// 송신을 합니다.
int Socket::Send(const char* data, int length)
{
	return send(m_Socket, data, length, 0);
}

void Socket::Close()
{
	closesocket(m_Socket);
}

void Socket::Listen()
{
	listen(m_Socket, 5000);
}

// 성공하면 0, 실패하면 다른 값을 리턴합니다.
// errorText에는 실패시 에러내용이 텍스트로  채워집니다.
// acceptedSocket에는 accept된 소켓 핸들이 들어갑니다.
int Socket::Accept(Socket & acceptedSocket, std::string & errorText)
{
	acceptedSocket.m_Socket = accept(m_Socket, nullptr, 0);
	if (acceptedSocket.m_Socket == -1)
	{
		errorText = GetLastErrorAsString();
		return -1;
	}
	else
		return 0;
}

// 성공하면 true, 실패하면 false를 리턴합니다.
// errorText에는 실패시 에러내용이 텍스트로  채워집니다.
// acceptCandidateSocket에는 이미 만들어진 소켓 핸들이 들어가며,
//accept이 되고 나면 이 소켓 핸들은 TCP 연결 객체로 변신합니다.
bool Socket::AcceptOverlapped(Socket & acceptCandidateSocket, std::string & errorText)
{
	if (m_AcceptEx == NULL)
	{
		DWORD bytes;
		// AcceptEx는 여타 소켓함수와 달리 직접 호출하는 것이 아니고,
		// 함수 포인터를 먼저 가져온 다음 호출할 수 있다. 그것을 여기서 한다.
		WSAIoctl(m_Socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &UUID(WSAID_ACCEPTEX), sizeof(UUID), &m_AcceptEx, sizeof(m_AcceptEx), &bytes, NULL, NULL);

		if (m_AcceptEx == NULL)
			throw Exception("Getting AcceptEx ptr failed.");
	}

	char ignored[200];
	DWORD ignored2 = 0;

	bool ret = AcceptEx(m_Socket, acceptCandidateSocket.m_Socket, &ignored, 0, 50, 50, &ignored2, &m_ReadOverlappedStruct) == TRUE;

	return ret;
}

// AcceptEx가 I/O 완료를 하더라도 아직 TCP 연결 받기 처리가 다 끝난 것이 아니다.
// 이 함수를 호출해주어야만 완료가 된다.
int Socket::UpdateAcceptContext(Socket & listenSocket)
{
	sockaddr_in ignore1;
	sockaddr_in ignore3;
	INT ignore2, ignore4;

	char ignore[1000];
	GetAcceptExSockaddrs(ignore, 0, 50, 50, (sockaddr**)&ignore1, &ignore2, (sockaddr**)&ignore3, &ignore4);

	//소켓옵션 조작함수
	return setsockopt(m_Socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,(char*)&listenSocket.m_Socket, sizeof(listenSocket.m_Socket));
}

EndPoint Socket::GetPeerAddr()
{
	EndPoint ret;
	size_t retLength = sizeof(ret.m_IPv4Endpoint);
	//연결된 호스트의 정보를 알아오는 함수
	if (::getpeername(m_Socket, (sockaddr*)&ret.m_IPv4Endpoint, reinterpret_cast<int*>(&retLength)) < 0)
	{
		std::stringstream ss;
		ss << "getPeerAddr failed:" << GetLastErrorAsString();
		throw Exception(ss.str().c_str());
	}
	if (retLength > sizeof(ret.m_IPv4Endpoint))
	{
		std::stringstream ss;
		ss << "getPeerAddr buffer overrun: " << retLength;
		throw Exception(ss.str().c_str());
	}

	return ret;
}

// 소켓 수신을 합니다. 
// 블로킹 소켓이면 1바이트라도 수신하거나 소켓 에러가 나거나 소켓 연결이 끊어질 때까지 기다립니다.
// 논블로킹 소켓이면 기다려야 하는 경우 즉시 리턴하고 EWOULDBLOCK이 errno나 GetLastError에서 나오게 됩니다.
// 리턴값: recv 리턴값 그대로입니다.
int Socket::Receive()
{
	return (int)recv(m_Socket, m_receiveBuffer, MaxReceiveLength, 0);
}

// overlapeed 수신을 겁니다. 즉 백그라운드로 수신 처리를 합니다.
// 수신되는 데이터는 m_receiveBuffer에 비동기로 채워집니다.
// 리턴값: WSARecv의 리턴값 그대로입니다.
int Socket::ReceiveOverlapped()
{
	WSABUF b;
	b.buf = m_receiveBuffer;
	b.len = MaxReceiveLength;

	// overlapped I/O가 진행되는 동안 여기 값이 채워집니다.
	m_readFlags = 0;

	return WSARecv(m_Socket, &b, 1, NULL, &m_readFlags, &m_ReadOverlappedStruct, NULL);
}

int Socket::SendOverlapped(const char* Data, int Length, Socket& sock)
{
	WSABUF buf;
	buf.buf = const_cast<char*>(Data);
	buf.len = Length;
	m_readFlags = 0;

	return WSASend(sock.m_Socket, &buf, 1, nullptr, m_readFlags, &m_SendOverlappedStruct, nullptr);
}

// 넌블럭 소켓으로 모드를 설정합니다.
void Socket::SetNonblocking()
{
	u_long val = 1;
	//논블로킹모드로 바꾸는 함수
	int ret = ioctlsocket(m_Socket, FIONBIO, &val);

	if (ret != 0)
	{
		std::stringstream ss;
		ss << "bind failed:" << GetLastErrorAsString();
		throw Exception(ss.str().c_str());
	}
}

std::string Socket::GetLastErrorAsString()
{
	return std::string();
}
