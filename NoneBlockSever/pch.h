#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <WinSock2.h>
#include <mswsock.h>
#include <Windows.h>
#include <string>
#include <sstream>
#include <exception>
#include <thread>
#include <queue>
#include <mutex>
#include "EndPoint.h"
#include "Socket.h"
#include "SockInit.h"
#include "Exception.h"
#include "SemaPhore.h"
#include "PollFD.h"
#include <signal.h>
#include <memory>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

#endif //PCH_H
