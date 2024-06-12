#include <iostream>
#include "LinkedList.h"
#include "Array.h"
#include "Stack.h"
#include "Queue.h"

int main()
{
	// List
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
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	// iterInt = iterInt + iterInt1;
	// iterInt ��ü�� ==(����) operator�� ȣ���ϴ� ��
	// ȣ���� �� ���ڷ� iterInt1�� �Ѱ��ִ� ��

	
	iter = ListInt.begin();
	++iter;
	++iter;

	iter = ListInt.erase(iter);

	for (auto l : ListInt)
	{
		std::cout << l * 10 << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	
	// Array
	CArray<int> IntArray;

	for (int i = 0; i < 10; i++)
	{
		IntArray.push_back(i * 100);
	}

	for (int i = 0; i < IntArray.size(); i++)
	{
		std::cout << IntArray[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;


	// Stack
	CStack<int> IntStack;

	for (int i = 0; i < 10; i++)
	{
		IntStack.push(i * 1000);
	}

	while (!IntStack.empty())
	{
		int Data = 0;
		IntStack.top(Data);
		std::cout << Data << " ";

		IntStack.pop();
	}
	std::cout << std::endl;
	std::cout << std::endl;


	// Queue
	CQueue<int> IntQueue;

	for (int i = 0; i < 10; i++)
	{
		IntQueue.push(i * 10000);
	}

	while (!IntQueue.empty())
	{
		int Data = 0;
		IntQueue.front(Data);
		std::cout << Data << " ";

		IntQueue.pop();
	}
	std::cout << std::endl;
	std::cout << std::endl;


	return 0;
}