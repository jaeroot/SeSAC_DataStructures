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
	// for���� �Ǻ��Ŀ� != iter.end()�� ��� ȣ���ؼ� iterEnd�� �̸� ������ �ݺ� ȣ�� ����
	for (iter = ListInt.begin(); iter != iterEnd; ++iter)
	{
		std::cout << *iter << std::endl;
	}

	// iterInt = iterInt + iterInt1;
	// iterInt ��ü�� ==(����) operator�� ȣ���ϴ� ��
	// ȣ���� �� ���ڷ� iterInt1�� �Ѱ��ִ� ��

	
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