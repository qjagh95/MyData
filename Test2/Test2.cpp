#include "pch.h"
#include <iostream>
#include <vector>
using namespace std;

class A
{
public:
	void Print() { cout << "A 프린트" << endl; }
};

class AA
{
public:
	virtual void Print() { cout << "AA" << endl; }
	AA() { Print(); }

};
class BB : public AA
{
public:
	void Print() override { cout << "BB" << endl; }
	BB() { Print(); }

};
class CC : public BB
{
public:
	void Print() override { cout << "CC" << endl; }
	CC() { Print(); }
};

vector<int> solution(vector<vector<int> > v);
int main()
{
	//A* newA = nullptr;
	//실행됨(this콜 함수내에서 참조하는 변수가 없기때문에 실행가능)
	//newA->Print(); 

	//AA* newAA = new CC();
	////함수 뒤 this가 붙기때문에 AA BB CC CC실행

	//newAA->Print();

	//AA* getAA = dynamic_cast<CC*>(newAA);

	//CC* newCC = new CC();

	//AA* getCC = dynamic_cast<AA*>(newCC);

	//delete newAA;

	vector<vector<int>> b;
	vector<int> a;
	a.push_back(1);
	a.push_back(1);
	b.push_back(a);

	vector<int>asd;
	asd.push_back(1);
	asd.push_back(2);

	b.push_back(asd);

	vector<int> dsa;
	dsa.push_back(2);
	dsa.push_back(2);
	b.push_back(dsa);

	solution(b);
}

vector<int> solution(vector<vector<int> > v)
{
	vector<int> ans;

	vector<int> xVec;
	vector<int> yVec;

	for (size_t i = 0; i < v.size(); i++)
	{
		for (size_t j = 0; j < v[i].size(); j++)
		{
			if (j == 0)
				xVec.push_back(v[i][j]);
			else
				yVec.push_back(v[i][j]);
		}
	}

	for (size_t i = 0; i < xVec.size() - 1; i++)
	{
		if (xVec[i] == xVec[i + 1])
		{
			xVec.erase(xVec.begin() + i + 1);
			xVec.erase(xVec.begin() + i);
			break;
		}
	}

	for (size_t i = 0; i < yVec.size() - 1; i++)
	{
		if (yVec[i] == yVec[i + 1])
		{
			yVec.erase(yVec.begin() + i + 1);
			yVec.erase(yVec.begin() + i);
			break;
		}
	}

	ans.push_back(xVec[0]);
	ans.push_back(yVec[0]);

	return ans;
}