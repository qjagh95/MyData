#include "pch.h"
#include "EndPoint.h"

#ifdef _WIN32
#include <Ws2tcpip.h>
#else 
#include <netinet/in.h>
#include <netinet/ip.h>
#endif

EndPoint::EndPoint()
{
	ZeroMemory(&m_IPv4Endpoint, sizeof(m_IPv4Endpoint));
	m_IPv4Endpoint.sin_family = AF_INET;
}

EndPoint::EndPoint(const char * address, int port)
{
	ZeroMemory(&m_IPv4Endpoint, sizeof(m_IPv4Endpoint));
	m_IPv4Endpoint.sin_family = AF_INET;
	inet_pton(AF_INET, address, &m_IPv4Endpoint.sin_addr);
	m_IPv4Endpoint.sin_port = htons((uint16_t)port);
}

EndPoint::~EndPoint()
{
}

string EndPoint::ToString()
{
	char addrString[1000];
	addrString[0] = 0;
	inet_ntop(AF_INET, &m_IPv4Endpoint.sin_addr, addrString, sizeof(addrString) - 1);

	char finalString[1000];
	sprintf(finalString, "%s:%d", addrString, htons(m_IPv4Endpoint.sin_port));

	return finalString;
}
