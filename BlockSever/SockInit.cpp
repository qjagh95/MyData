#include "pch.h"
#include "SockInit.h"
SocketInit g_socketInit;

SocketInit::SocketInit()
{
#ifdef _WIN32
	// Windows������ WSAStartup, WSACleanup�� ���ʿ� ���Ŀ� �� �ѹ� �־�� �մϴ�.
	WSADATA Temp;
	WSAStartup(MAKEWORD(2, 2), &Temp);
#endif

}

void SocketInit::Touch()
{
}
