#include "pch.h"
using namespace std;

// true가 되면 프로그램을 종료합니다.
volatile bool stopWorking = false;
void ProcessSignalAction(int sig_number)
{
	if (sig_number == SIGINT)
		stopWorking = true;
}
// TCP 연결 각각의 객체.
struct RemoteClient
{
	Socket tcpConnection;		// accept한 TCP 연결
};
unordered_map<RemoteClient*, shared_ptr<RemoteClient>> remoteClients;

int main()
{
	// 사용자가 ctl-c를 누르면 메인루프를 종료하게 만듭니다.
	signal(SIGINT, ProcessSignalAction);

	// 논블록 소켓으로 많은 수의 클라이언트를 받아 처리한다.
	// 많은 수의 클라가 tcp 5555로 연결 들어오고,
	// 그들은 hello world를 열심히 보낼 것이다.
	// 그것을 그냥 에코해주도록 하자.
	// 서버에서는 총 처리한 바이트수를 지속적으로 출럭만 하자.

	// TCP 연결을 받는 소켓
	Socket listenSocket(SocketType::Tcp);
	listenSocket.Bind(EndPoint("192.168.1.172", 5000));
	listenSocket.SetNonblocking();
	listenSocket.Listen();

	cout << "서버가 시작되었습니다.\n";
	cout << "CTL-C키를 누르면 프로그램을 종료합니다.\n";

	// 리슨 소켓과 TCP 연결 소켓 모두에 대해서 I/O 가능(avail) 이벤트가 있을 때까지 기다린다. 
	// 그리고 나서 I/O 가능 소켓에 대해서 일을 한다.
	// 여기에 넣은 소켓 핸들에 대해서 select나 poll을 한다.
	// 다만, receive나 accept에 대해서만 처리한다.
	vector<PollFD> readFds;

	// 어느 소켓이 어느 RemoteClient에 대한 것인지를 가리킵니다.
	vector<RemoteClient*> readFdsToRemoteClients;

	while (stopWorking == false)
	{
		readFds.reserve(remoteClients.size() + 1);
		readFds.clear();
		readFdsToRemoteClients.reserve(remoteClients.size() + 1);
		readFdsToRemoteClients.clear();

		for (auto i : remoteClients)
		{
			PollFD item;
			item.m_pollfd.events = POLLRDNORM;
			item.m_pollfd.fd = i.second->tcpConnection.m_Socket;
			item.m_pollfd.revents = 0;
			readFds.push_back(item);
			readFdsToRemoteClients.push_back(i.first);
		}

		// 마지막 항목은 리슨소켓입니다.
		PollFD item2;
		item2.m_pollfd.events = POLLRDNORM;
		item2.m_pollfd.fd = listenSocket.m_Socket;
		item2.m_pollfd.revents = 0;
		readFds.push_back(item2);

		// I/O 가능 이벤트가 있을 때까지 기다립니다.
		Poll(readFds.data(), (int)readFds.size(), 100);

		// readFds를 수색해서 필요한 처리를 합니다.
		int num = 0;
		for (auto readFd : readFds)
		{
			if (readFd.m_pollfd.revents != 0)
			{
				if (num == readFds.size() - 1) // 리슨소켓이면
				{			
					// accept을 처리한다.
					auto remoteClient = make_shared<RemoteClient>();

					// 이미 "클라이언트 연결이 들어왔음" 이벤트가 온 상태이므로 그냥 이것을 호출해도 된다.
					string ignore;
					listenSocket.Accept(remoteClient->tcpConnection, ignore);
					remoteClient->tcpConnection.SetNonblocking();

					// 새 클라이언트를 목록에 추가.
					remoteClients.insert(make_pair(remoteClient.get(), remoteClient));

					cout << "Client joined. There are " << remoteClients.size() << " connections.\n";
				}
				else  // TCP 연결 소켓이면
				{
					// 받은 데이터를 그대로 회신한다.
					RemoteClient* remoteClient = readFdsToRemoteClients[num];

					int ec = remoteClient->tcpConnection.Receive();
					if (ec <= 0)
					{
						// 에러 혹은 소켓 종료이다.
						// 해당 소켓은 제거해버리자. 
						remoteClient->tcpConnection.Close();
						remoteClients.erase(remoteClient);

						cout << "Client left. There are " << remoteClients.size() << " connections.\n";
					}
					else
					{
						// 받은 데이터 그대로 송신한다.

						// 원칙대로라면 TCP 스트림 특성상 일부만 송신하고 리턴하는 경우도 고려해야 하나,
						// 지금은 독자의 이해가 우선이므로, 생략하도록 한다.
						remoteClient->tcpConnection.Send(remoteClient->tcpConnection.m_receiveBuffer, ec);
					}
				}
			}
		}
	}

}