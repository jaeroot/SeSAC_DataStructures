#include <iostream>
#include "LinkedList.h"
#include <list>

int main()
{
	CLinkedList<int> ListInt;

	for (int i = 0; i < 10; i++)
	{
		ListInt.push_back(i);
	}

	//CListIterator<int> iterInt;
	//CLinkedList<int>::iterator iterInt1;

	CLinkedList<int>::iterator iter;
	CLinkedList<int>::iterator iterEnd = ListInt.end();
	// for문의 판별식에 != iter.end()를 계속 호출해서 iterEnd를 미리 지정해 반복 호출 막음
	for (iter = ListInt.begin(); iter != iterEnd; ++iter)
	{
		std::cout << *iter << std::endl;
	}

	// iterInt = iterInt + iterInt1;
	// iterInt 객체의 ==(같다) operator를 호출하는 것
	// 호출할 때 인자로 iterInt1을 넘겨주는 것

	
	iter = ListInt.begin();
	++iter;
	++iter;

	iter = ListInt.erase(iter);

	for (auto l : ListInt)
	{
		std::cout << l << std::endl;
	}

	std::cout << sizeof(std::list<int>::iterator) << std::endl;


	return 0;
}