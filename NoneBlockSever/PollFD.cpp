#include "pch.h"
#include "PollFD.h"


// fdArray�� fdArrayLength�� ����Ű�� �迭�� ���� �� �ϳ� �̻��� �̺�Ʈ�� ����ų ������ ��ٸ��ϴ�.
// timeOutMs�� �ִ� ��� �ð��� �и��� ������ ��ٸ��� ���Դϴ�.
int Poll(PollFD* fdArray, int fdArrayLength, int timeOutMs)
{
	// �̰� ���� ���ϸ� PollFD�� virtual �Լ� �� �ٸ� ����� ���ٴ� ���̴�.
	//�̷��� ��� PollFD�κ��� ����Ƽ�� �迭���� ���縦 ���ִ� ���� ������ �����ؾ� �Ѵ�.
	static_assert(sizeof(fdArray[0]) == sizeof(fdArray[0].m_pollfd), "");

	return ::WSAPoll((WSAPOLLFD*)fdArray, fdArrayLength, timeOutMs);
}