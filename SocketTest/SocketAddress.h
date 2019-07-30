#pragma once
class string;
class SocketAddress
{
public:
	SocketAddress(uint32_t Address, uint16_t Port)
	{
		GetSocketAddress()->sin_family = AF_INET;
		GetSocketAddress()->sin_addr.S_un.S_addr = htonl(Address);
		GetSocketAddress()->sin_port = htons(Port);
	}
	SocketAddress(const string& Address, uint16_t Port)
	{

	}

	SocketAddress(const sockaddr& CopyData)
	{
		memcpy(&m_SocketAddress, &CopyData, sizeof(SocketAddress));
	}

	~SocketAddress() {}

	sockaddr_in* GetSocketAddress() { return reinterpret_cast<sockaddr_in*>(&m_SocketAddress); }

private:
	sockaddr m_SocketAddress;
};

