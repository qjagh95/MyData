#include "pch.h"
#include <iostream>
//기존 winsock.h는 구식이고 최적화도 덜되있고 기능도 부족하다.
//그래서 WinSock2를 쓰도록하자
#include <WinSock2.h>

//Windows.h에 기본적으로 구식버전 winsock.h가 포함되어있다.
//WinSock2.h와 충돌하기때문에 Define해준다.
#define WIN32_LEAN_AMND_MEAN

#include <Windows.h>
using namespace std;

int main()
{
	//소켓 생성함수(SOCKET는 unsigned long long의 typedef일뿐이다)
	//1. IF_INET(IPV4), 순서와 전달이 보장되는 스트림, TCP프로토콜 사용(0이면 알아서맞춘다)
	SOCKET newSocket = socket(AF_INET, SOCK_STREAM, 0);


	//소켓을 닫을땐 잔여데이터 전부 전송이 끝나고 확인까지 받은 상태에서 끝내는것이 중요하다.
	//shutdown함수를 사용해서 닫기 전 모든데이터를 전송하는 플래그를 지정한다.
	shutdown(newSocket, SD_SEND);
	//소켓을 닫는다.
	closesocket(newSocket);
}