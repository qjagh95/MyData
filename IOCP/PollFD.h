#pragma once

class PollFD
{
public:
	WSAPOLLFD m_pollfd;
};

int Poll(PollFD* fdArray, int fdArrayLength, int timeOutMs);