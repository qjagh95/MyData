﻿#include "pch.h"
#include <iostream>
//기존 winsock.h는 구식이고 최적화도 덜되있고 기능도 부족하다.
//그래서 WinSock2를 쓰도록하자
#include <WinSock2.h>

//주소변환기능을 사용하기위한 헤더
#include <WS2tcpip.h>

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

	//소켓을 활성화하는 함수
	WSAData newInfo = {};
	//1. 주 버전 번호 2. 정보값 세팅
	int Check = WSAStartup(MAKEWORD(2,2), &newInfo);
	//Check값이 0이면 성공 나머지는 에러코드

	//에러코드를 반환한다.
	Check = WSAGetLastError();

	//전송계층 패킷에는 발신지 주소와 목적지 주소가 필요하다
	//발신지포트와 목적지 포트까지 필요하기때문에 정의해줘야한다.
	//IPV4를 할땐 이 형식으로 사용해야한다.
	sockaddr_in SockAddr;
	//sin_family = 주소의 종류를 나타내는 상수값 정의(AF_INET)
	//sin_port = 포트값
	//sin_addr = IPV4주소
	//sin_zero[8] = 패딩을위한것으로 별도로 사용하지않는다.
	

	//소켓 주소구조체에서 여러바이트로 된 숫자를 호스트 순서가아닌 네트워크 순서로 바꿔야한다.
	//그때 쓰는 함수 두가지
	//부호없는 16비트 정수를 받는다
	htons(); 
	//32비트 정수 처리
	htonl();

	//네트워크바이트 -> 윈도우바이트 (부호없는 16비트)
	ntohs();
	//네트워크바이트 -> 윈도우바이트 (32비트)
	ntohl();


	//WSAStartUp함수를 호출한만큼 해줘야한다. (래퍼런스 카운트방식)
	WSACleanup();

	//소켓을 닫을땐 잔여데이터 전부 전송이 끝나고 확인까지 받은 상태에서 끝내는것이 중요하다.
	//shutdown함수를 사용해서 닫기 전 모든데이터를 전송하는 플래그를 지정한다.
	shutdown(newSocket, SD_SEND);
	//소켓을 닫는다.
	closesocket(newSocket);
}