#include "pch.h"
#include "SockInit.h"
SocketInit g_socketInit;

SocketInit::SocketInit()
{
#ifdef _WIN32
	// Windows에서는 WSAStartup, WSACleanup이 최초와 최후에 딱 한번 있어야 합니다.
	WSADATA Temp;
	WSAStartup(MAKEWORD(2, 2), &Temp);
#endif

}

void SocketInit::Touch()
{
}
