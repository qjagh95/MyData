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
	// overlapped I/O�� ������ socket() ���� WSASocket�� ��� �մϴ�.
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
	// endpoint�� ����Ű�� �ּҷ��� ������ �մϴ�.
	if (connect(m_Socket, (sockaddr*)&endpoint.m_IPv4Endpoint, sizeof(endpoint.m_IPv4Endpoint)) < 0)
	{
		std::stringstream ss;
		ss << "connect failed:" << GetLastErrorAsString();
		throw Exception(ss.str().c_str());
	}
}

// �۽��� �մϴ�.
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

// �����ϸ� 0, �����ϸ� �ٸ� ���� �����մϴ�.
// errorText���� ���н� ���������� �ؽ�Ʈ��  ä�����ϴ�.
// acceptedSocket���� accept�� ���� �ڵ��� ���ϴ�.
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

// �����ϸ� true, �����ϸ� false�� �����մϴ�.
// errorText���� ���н� ���������� �ؽ�Ʈ��  ä�����ϴ�.
// acceptCandidateSocket���� �̹� ������� ���� �ڵ��� ����,
//accept�� �ǰ� ���� �� ���� �ڵ��� TCP ���� ��ü�� �����մϴ�.
bool Socket::AcceptOverlapped(Socket & acceptCandidateSocket, std::string & errorText)
{
	if (m_AcceptEx == NULL)
	{
		DWORD bytes;
		// AcceptEx�� ��Ÿ �����Լ��� �޸� ���� ȣ���ϴ� ���� �ƴϰ�,
		// �Լ� �����͸� ���� ������ ���� ȣ���� �� �ִ�. �װ��� ���⼭ �Ѵ�.
		WSAIoctl(m_Socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &UUID(WSAID_ACCEPTEX), sizeof(UUID), &m_AcceptEx, sizeof(m_AcceptEx), &bytes, NULL, NULL);

		if (m_AcceptEx == NULL)
			throw Exception("Getting AcceptEx ptr failed.");
	}

	char ignored[200];
	DWORD ignored2 = 0;

	bool ret = AcceptEx(m_Socket, acceptCandidateSocket.m_Socket, &ignored, 0, 50, 50, &ignored2, &m_ReadOverlappedStruct) == TRUE;

	return ret;
}

// AcceptEx�� I/O �ϷḦ �ϴ��� ���� TCP ���� �ޱ� ó���� �� ���� ���� �ƴϴ�.
// �� �Լ��� ȣ�����־�߸� �Ϸᰡ �ȴ�.
int Socket::UpdateAcceptContext(Socket & listenSocket)
{
	sockaddr_in ignore1;
	sockaddr_in ignore3;
	INT ignore2, ignore4;

	char ignore[1000];
	GetAcceptExSockaddrs(ignore, 0, 50, 50, (sockaddr**)&ignore1, &ignore2, (sockaddr**)&ignore3, &ignore4);

	//���Ͽɼ� �����Լ�
	return setsockopt(m_Socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,(char*)&listenSocket.m_Socket, sizeof(listenSocket.m_Socket));
}

EndPoint Socket::GetPeerAddr()
{
	EndPoint ret;
	size_t retLength = sizeof(ret.m_IPv4Endpoint);
	//����� ȣ��Ʈ�� ������ �˾ƿ��� �Լ�
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

// ���� ������ �մϴ�. 
// ���ŷ �����̸� 1����Ʈ�� �����ϰų� ���� ������ ���ų� ���� ������ ������ ������ ��ٸ��ϴ�.
// ����ŷ �����̸� ��ٷ��� �ϴ� ��� ��� �����ϰ� EWOULDBLOCK�� errno�� GetLastError���� ������ �˴ϴ�.
// ���ϰ�: recv ���ϰ� �״���Դϴ�.
int Socket::Receive()
{
	return (int)recv(m_Socket, m_receiveBuffer, MaxReceiveLength, 0);
}

// overlapeed ������ �̴ϴ�. �� ��׶���� ���� ó���� �մϴ�.
// ���ŵǴ� �����ʹ� m_receiveBuffer�� �񵿱�� ä�����ϴ�.
// ���ϰ�: WSARecv�� ���ϰ� �״���Դϴ�.
int Socket::ReceiveOverlapped()
{
	WSABUF b;
	b.buf = m_receiveBuffer;
	b.len = MaxReceiveLength;

	// overlapped I/O�� ����Ǵ� ���� ���� ���� ä�����ϴ�.
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

// �ͺ� �������� ��带 �����մϴ�.
void Socket::SetNonblocking()
{
	u_long val = 1;
	//����ŷ���� �ٲٴ� �Լ�
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
