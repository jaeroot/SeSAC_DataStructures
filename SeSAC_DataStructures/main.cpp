#include <iostream>
#include "LinkedList.h"
#include "Array.h"
#include "Stack.h"
#include "Queue.h"
#include "BinaryTree.h"
#include "AVLTree.h"

int main()
{
	//**************************************************************************
	// List
	std::cout << "===========================" << "List" << "===========================" << std::endl;
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
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	// iterInt = iterInt + iterInt1;
	// iterInt 객체의 ==(같다) operator를 호출하는 것
	// 호출할 때 인자로 iterInt1을 넘겨주는 것

	
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


	//**************************************************************************
	// Array
	std::cout << "===========================" << "Array" << "===========================" << std::endl;
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


	//**************************************************************************
	// Stack
	std::cout << "===========================" << "Stack" << "===========================" << std::endl;
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


	//**************************************************************************
	// Queue
	std::cout << "===========================" << "Queue" << "===========================" << std::endl;
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



	//**************************************************************************
	// Binary Tree
	std::cout << "===========================" << "Binary Tree" << "===========================" << std::endl;

	CBinaryTree<int, int> IntTree;

	IntTree.Insert(10, 10);
	IntTree.Insert(5, 5);
	IntTree.Insert(15, 15);
	IntTree.Insert(3, 3);
	IntTree.Insert(8, 8);
	IntTree.Insert(13, 13);
	IntTree.Insert(1, 1);
	IntTree.Insert(4, 4);
	IntTree.Insert(9, 9);
	IntTree.Insert(30, 30);
	IntTree.Insert(20, 20);
	IntTree.Insert(40, 40);

	auto Treeiter = IntTree.Begin();
	auto TreeiterEnd = IntTree.End();

	for (; Treeiter != TreeiterEnd ; ++Treeiter)
	{
		std::cout << "Key : " << Treeiter->mKey << ", Value : " << Treeiter->mValue << std::endl;
	}

	std::cout << "Find 5 : " << IntTree.Find(5)->mValue << std::endl;
	std::cout << "Find 10 : " << IntTree.Find_Iteration(10)->mValue << std::endl;
	
	
	std::cout << "Delete 5 : " << IntTree.erase(5)->mValue << std::endl;

	for (Treeiter = IntTree.Begin(); Treeiter != TreeiterEnd; ++Treeiter)
	{
		std::cout << "Key : " << Treeiter->mKey << ", Value : " << Treeiter->mValue << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;


	//**************************************************************************
	// AVL Tree
	std::cout << "===========================" << "AVL Tree" << "===========================" << std::endl;

	CAVLTree<int, int> AVLTree;

	for (int i = 0; i < 10; i++)
	{
		AVLTree.Insert(i, i);
	}
	AVLTree.OutputTree();
	std::cout << std::endl;
	std::cout << std::endl;

	AVLTree.erase(1);
	AVLTree.erase(0);
	AVLTree.OutputTree();
	std::cout << std::endl;
	std::cout << std::endl;


	AVLTree.Preorder();
	AVLTree.Inorder();
	AVLTree.Postorder();



	return 0;
}