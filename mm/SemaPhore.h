#pragma once
#include "pch.h"
class SemaPhore
{
public:
	SemaPhore(int count_ = 0) : m_count(count_) {}

	inline void Notify()
	{
		using namespace std;
		unique_lock<mutex> lock(m_mtx);
		m_count++;
		m_cv.notify_one();
	}

	inline void Wait()
	{
		using namespace std;
		unique_lock<mutex> lock(m_mtx);

		while (m_count == 0)
			m_cv.wait(lock);

		m_count--;
	}

private:
	std::mutex m_mtx;
	std::condition_variable m_cv;
	int m_count;
};

