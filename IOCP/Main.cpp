#include "pch.h"
#include "WriteMemoryStream.h"

using namespace std;
// true�� �Ǹ� ���α׷��� �����մϴ�.
volatile bool stopWorking = false;

void ProcessSignalAction(int sig_number)
{
	if (sig_number == SIGINT)
		stopWorking = true;
}
// TCP ���� ������ ��ü.
class RemoteClient
{
public:
	shared_ptr<thread> thread; // Ŭ���̾�Ʈ ó���� �ϴ� ������ 1��
	Socket tcpConnection;		// accept�� TCP ����

	RemoteClient() {}
	RemoteClient(SocketType socketType) :tcpConnection(socketType) {}
};

unordered_map<RemoteClient*, shared_ptr<RemoteClient>> remoteClients;

void ProcessClientLeave(shared_ptr<RemoteClient> remoteClient)
{
	// ���� Ȥ�� ���� �����̴�.
	// �ش� ������ �����ع�����. 
	remoteClient->tcpConnection.Close();
	remoteClients.erase(remoteClient.get());

	cout << "Client left. There are " << remoteClients.size() << " connections.\n";
}

void main()
{
	// ����ڰ� ctl-c�� ������ ���η����� �����ϰ� ����ϴ�.
	signal(SIGINT, ProcessSignalAction);


	MyIOCP iocp(8); // �� ������ �����带 �� �ϳ��� ����. ���� ���⵵ 1�� ����.
	// TCP ������ �޴� ����
	Socket listenSocket(SocketType::Tcp);
	listenSocket.Bind(EndPoint("192.168.1.172", 5000));
	listenSocket.Listen();

	iocp.Add(listenSocket, nullptr);

	// overlapped accept�� �ɾ�д�. 
	auto remoteClientCandidate = make_shared<RemoteClient>(SocketType::Tcp);

	string errorText;
	if (listenSocket.AcceptOverlapped(remoteClientCandidate->tcpConnection, errorText) != 0 && WSAGetLastError() != ERROR_IO_PENDING)
		throw Exception("Overlapped AcceptEx failed.");

	cout << "������ ���۵Ǿ����ϴ�.\n";
	cout << "CTL-CŰ�� ������ ���α׷��� �����մϴ�.\n";

	listenSocket.m_isReadOverlapped = true;

	// ���� ���ϰ� TCP ���� ���� ��ο� ���ؼ� I/O ����(avail) �̺�Ʈ�� ���� ������ ��ٸ���. 
	// �׸��� ���� I/O ���� ���Ͽ� ���ؼ� ���� �Ѵ�.
	while (stopWorking == false)
	{			
		// I/O �Ϸ� �̺�Ʈ�� ���� ������ ��ٸ��ϴ�.
		IocpEvents readEvents;
		iocp.Wait(readEvents, 100);

		// ���� �̺�Ʈ ������ ó���մϴ�.
		for (int i = 0; i < readEvents.m_eventCount; i++)
		{
			auto& readEvent = readEvents.m_events[i];

			if (readEvent.lpCompletionKey == 0) // ���������̸�
			{
				listenSocket.m_isReadOverlapped = false;
				// �̹� accept�� �Ϸ�Ǿ���. ��������, Win32 AcceptEx ������ ������ ������ �۾��� ����. 
				//���������� �ݾҴ��� �ϸ� ���⼭ �������Ŵ�. �׷��� �������� �Ҵɻ��·� ������.
				if (remoteClientCandidate->tcpConnection.UpdateAcceptContext(listenSocket) != 0)
					listenSocket.Close();

				else // �� ó����
				{
					shared_ptr<RemoteClient> remoteClient = remoteClientCandidate;

					// �� TCP ���ϵ� IOCP�� �߰��Ѵ�.
					iocp.Add(remoteClient->tcpConnection, remoteClient.get());

					// overlapped ������ ���� �� �־�� �ϹǷ� ���⼭ I/O ���� ��û�� �ɾ�д�.
					// ����. ������ ��������. �׸��� �׳� ������.
					if (remoteClient->tcpConnection.ReceiveOverlapped() != 0 && WSAGetLastError() != ERROR_IO_PENDING)
						remoteClient->tcpConnection.Close();
					else
					{
						// I/O�� �ɾ���. �ϷḦ ����ϴ� �� ���·� �ٲ���.
						remoteClient->tcpConnection.m_isReadOverlapped = true;

						// �� Ŭ���̾�Ʈ�� ��Ͽ� �߰�.
						remoteClients.insert(make_pair(remoteClient.get(), remoteClient));
						cout << "Client joined. There are " << remoteClients.size() << " connections.\n";
					}

					// ����ؼ� ���� �ޱ⸦ �ؾ� �ϹǷ� �������ϵ� overlapped I/O�� ����.
					remoteClientCandidate = make_shared<RemoteClient>(SocketType::Tcp);

					// �������� �������� �Ҵ� ���·� ������. 
					string errorText;
					if (listenSocket.AcceptOverlapped(remoteClientCandidate->tcpConnection, errorText) == false && WSAGetLastError() != ERROR_IO_PENDING)
						listenSocket.Close();

					else // ���������� ������ ������ ��ٸ��� ���°� �Ǿ���.
						listenSocket.m_isReadOverlapped = true;
				}
			}
			else  // TCP ���� �����̸�
			{
				// ���� �����͸� �״�� ȸ���Ѵ�.
				shared_ptr<RemoteClient> remoteClient = remoteClients[(RemoteClient*)readEvent.lpCompletionKey];

				if (readEvent.dwNumberOfBytesTransferred <= 0)
					int a = 0;

				if (remoteClient)
				{
					// �̹� ���ŵ� �����̴�. ���� �Ϸ�� ���� �׳� ���� ����.
					remoteClient->tcpConnection.m_isReadOverlapped = false;
					int ec = readEvent.dwNumberOfBytesTransferred;

					if (ec <= 0)
					{
						// ���� ����� 0 �� TCP ������ ������...
						// Ȥ�� ���� �� ���� ������ �� �����̴�...
						ProcessClientLeave(remoteClient);
					}
					else
					{	// �̹� ���ŵ� �����̴�. ���� �Ϸ�� ���� �׳� ���� ����.
						char* echoData = remoteClient->tcpConnection.m_receiveBuffer;
						int echoDataLength = ec;

						cout << echoData << endl;

						// ��Ģ��ζ�� TCP ��Ʈ�� Ư���� �Ϻθ� �۽��ϰ� �����ϴ� ��쵵 ����ؾ� �ϳ�,
						// ������ ������ ���ذ� �켱�̹Ƿ�, �����ϵ��� �Ѵ�.
						// ��Ģ��ζ�� ���⼭ overlapped �۽��� �ؾ� ������ 
						// ������ ���ظ� ���ؼ� �׳� ���ŷ �۽��� �Ѵ�.
						remoteClient->tcpConnection.SendOverlapped(echoData, echoDataLength, remoteClient->tcpConnection);

						// �ٽ� ������ �������� overlapped I/O�� �ɾ�� �Ѵ�.
						if (remoteClient->tcpConnection.ReceiveOverlapped() != 0 && WSAGetLastError() != ERROR_IO_PENDING)
							ProcessClientLeave(remoteClient);
						else	// I/O�� �ɾ���. �ϷḦ ����ϴ� �� ���·� �ٲ���.
							remoteClient->tcpConnection.m_isReadOverlapped = true;
					}
				}
			}
		}
	}


	// ����ڰ� CTL-C�� ������ ������ ������. ��� ���Ḧ ����.
	// �׷��� overlapped I/O�� ��� �Ϸ�Ǳ� ������ �׳� ������ ������ �ȵȴ�. �ü���� ��׶���� overlapped I/O�� �������̱� �����̴�.
	// �ϷḦ ��� üũ�ϰ� �������� ����.
	listenSocket.Close();

	for (auto i : remoteClients)
		i.second->tcpConnection.Close();

	cout << "������ �����ϰ� �ֽ��ϴ�...\n";

	while (remoteClients.size() > 0 || listenSocket.m_isReadOverlapped)
	{
		// I/O completion�� ���� ������ RemoteClient�� �����Ѵ�.
		for (auto i = remoteClients.begin(); i != remoteClients.end();)
		{
			if (i->second->tcpConnection.m_isReadOverlapped == false)
				i = remoteClients.erase(i);
			else
				i++; // �� �� ��ٷ�����.
		}

		// I/O completion�� �߻��ϸ� �� �̻� Overlapped I/O�� ���� ���� '���� �����ص� ��...'�� �÷����Ѵ�.
		IocpEvents readEvents;
		iocp.Wait(readEvents, 100);

		// ���� �̺�Ʈ ������ ó���մϴ�.
		for (int i = 0; i < readEvents.m_eventCount; i++)
		{
			auto& readEvent = readEvents.m_events[i];

			if (readEvent.lpCompletionKey == 0) // ���������̸�
				listenSocket.m_isReadOverlapped = false;
			else
			{
				shared_ptr<RemoteClient> remoteClient = remoteClients[(RemoteClient*)readEvent.lpCompletionKey];

				if (remoteClient)
					remoteClient->tcpConnection.m_isReadOverlapped = false;
			}
		}
	}
}