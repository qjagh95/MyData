#pragma once
class EndPoint
{
public:
	sockaddr_in m_IPv4Endpoint;
	static EndPoint Any;
	std::string ToString();

public:
	EndPoint();
	EndPoint(const char* address, int port);
	~EndPoint();


};
	
