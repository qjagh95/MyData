#include "stdafx.h"
#include "MyMap.h"

void main()
{
	//map<int, int> StlMap;
	//StlMap.insert(map<int, int>::value_type(50, 100));
	//StlMap.insert(map<int, int>::value_type(15, 100));
	//StlMap.insert(map<int, int>::value_type(10, 100));
	//StlMap.insert(map<int, int>::value_type(25, 100));
	//StlMap.insert(map<int, int>::value_type(20, 100));
	//StlMap.insert(map<int, int>::value_type(30, 100));
	//StlMap.insert(map<int, int>::value_type(60, 100));
	//StlMap.insert(map<int, int>::value_type(80, 100));
	//StlMap.insert(map<int, int>::value_type(75, 100));

	//map<int, int>::iterator iter = StlMap.find(50);
	////end가 NULL이 아니라는건 찾았다는 얘기
	//if (iter != StlMap.end())
	//	iter = StlMap.erase(iter);

	//map<int, int>::iterator StartIter = StlMap.begin();
	//map<int, int>::iterator EndIter = StlMap.end();

	//cout << "STL Map" << endl;
	//for (; StartIter != EndIter; StartIter++)
	//	cout << StartIter->first << endl;

	//cout << endl;

	//MyMap<int, int> myMap;

	//myMap.Insert(50, 100);
	//myMap.Insert(15, 100);
	//myMap.Insert(10, 100);
	//myMap.Insert(25, 100);
	//myMap.Insert(20, 100);
	//myMap.Insert(30, 100);
	//myMap.Insert(60, 100);
	//myMap.Insert(80, 100);
	//myMap.Insert(75, 100);

	//cout << "MyMap" << endl;
	//MyMap<int, int>::Iter StIter = myMap.Begin();
	//MyMap<int, int>::Iter enIter = myMap.End();

	//for (; StIter != enIter; StIter++)
	//{
	//	cout << StIter.GetKey() << endl;
	//}
	//cout << endl;

	//cout << "전위순회" << endl;
	//myMap.FirstOrder();
	//cout << endl;
	//cout << "중위순회" << endl;
	//myMap.MidOrder();
	//cout << endl;
	//cout << "Revers중위순회" << endl;
	//myMap.ReversMid();
	//cout << endl;
	//cout << "후위순회" << endl;
	//myMap.LastOrder();
	//cout << endl;

	//MyMap<int, int>::Iter sIter = myMap.Begin();
	//MyMap<int, int>::Iter eIter = myMap.End();

	//cout << "이터레이터++" << endl;
	//for (; sIter != eIter; sIter++)
	//{
	//	cout << sIter.GetKey() << endl;
	//}

	//cout << endl;
	//cout << "Delete" << endl;

	//MyMap<int, int>::Iter fIter = myMap.Find(15);
	//myMap.Delete(fIter);

	//MyMap<int, int>::Iter SttIter = myMap.Begin();
	//MyMap<int, int>::Iter ennIter = myMap.End();
	//
	//for (; SttIter != enIter; SttIter++)
	//{
	//	cout << SttIter.GetKey() << endl;
	//}

	MyMap<int, int> myMap;

	myMap.Insert(10, 1);
	myMap.Insert(6, 1);
	myMap.Insert(11, 1);
	myMap.Insert(4, 1);
	myMap.Insert(7, 1);
	myMap.Insert(3, 1);
	myMap.Insert(5, 1);
	myMap.Insert(8, 1);
	myMap.Insert(13, 1);
	myMap.Insert(17, 1);

	myMap.MidOrder();

	//cout << "MyMap" << endl;
	//MyMap<int, int>::Iter StIter = myMap.Begin();
	//MyMap<int, int>::Iter enIter = myMap.End();

	//for (; StIter != enIter; StIter++)
	//{
	//	cout << StIter.GetKey() << endl;
	//}
	//cout << endl;
}

