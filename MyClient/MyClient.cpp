#include "pch.h"
using namespace std;

int main()
{
	Socket newSocket(SocketType::Tcp);
	newSocket.Bind(EndPoint::Any);		
	cout << "Connecting to server...\n";

	newSocket.Connect(EndPoint("192.168.1.172", 5000)); // 3 <===여기다가 실제 원하는 주소를 넣으십시오.

	cout << "Sending data...\n";
	const char* text = "hello";
	// 보낼 문자열의 sz도 포함해서 전송해야 하므로 +1 합니다.
	newSocket.Send(text, strlen(text) + 1);

	// 위 송신 함수가 성공하더라도 이것은 소켓에 송신 데이터를 넣은 것일 뿐,
	// 아직 서버에 도착했다는 뜻은 아닙니다.
	// 이 상태에서 바로 소켓 닫기를 해 버리면 서버는 데이터를 받지 못하는 가능성도 있습니다.
	// 따라서 의도적으로 서버가 받을 수 있는 충분한 시간을 기다립니다.
	// 실전에서 이렇게 만드실 일은 별로 없을 것입니다.
	std::this_thread::sleep_for(1s);

	cout << "Closing socket...\n";
	newSocket.Close();
}
