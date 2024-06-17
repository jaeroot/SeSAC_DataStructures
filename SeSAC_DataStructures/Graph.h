#pragma once
#include "Array.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>

template <typename T>
class CGraphEdge
{
	template <typename T>
	friend class CGraph;

	template <typename T>
	friend class CGraphNode;

private:
	CGraphEdge()
	{

	}

	~CGraphEdge()
	{

	}

private:
	CGraphNode<T>* mNode = nullptr;
};

template <typename T>
class CGraphNode
{
	template <typename T>
	friend class CGraph;

private:
	CGraphNode()
	{

	}

	~CGraphNode()
	{
		// mEdgeArray에는 CGraphEdge 클래스를 동적할당하고 그 메모리 주소를 저장해놓은 배열임
		// 그러므로, 그래프가 제거될 때 반드시 메모리 해제를 해주어야 함
		int Size = mEdgeArray.size();

		for (int i = 0; i < Size; ++i)
		{
			delete mEdgeArray[i];
		}
	}

private:
	T mData;
	bool mVisit = false;
	CArray<CGraphEdge<T>*> mEdgeArray;

public:
	void AddEdge(CGraphNode<T>* Node)
	{
		CGraphEdge<T>* Edge = new CGraphEdge<T>;

		Edge->mNode = Node;

		mEdgeArray.push_back(Edge);
	}

	void AddLinkNode(CQueue<CGraphNode<T>*>& Queue)
	{
		int Size = mEdgeArray.size();
		for (int i = 0; i < Size; ++i)
		{
			// 방문 상태가 아닌 노드를 Queue에 넣어줌
			if (!mEdgeArray[i]->mNode->mVisit)
			{
				mEdgeArray[i]->mNode->mVisit = true;
				Queue.push(mEdgeArray[i]->mNode);
			}
		}
	}

	void AddLinkNode(CStack<CGraphNode<T>*>& Stack)
	{
		int Size = mEdgeArray.size();
		for (int i = 0; i < Size; ++i)
		{
			// 방문 상태가 아닌 노드를 Stack에 넣어줌
			if (!mEdgeArray[i]->mNode->mVisit)
			{
				mEdgeArray[i]->mNode->mVisit = true;
				Stack.push(mEdgeArray[i]->mNode);
			}
		}
	}
};

template <typename T>
class CGraph
{
public:
	CGraph()
	{

	}

	~CGraph()
	{
		int Size = mNodeArray.size();

		for (int i = 0; i < Size; ++i)
		{
			delete mNodeArray[i];
		}
	}

private:
	CArray<CGraphNode<T>*> mNodeArray;

public:
	void CreateNode(const T& Data)
	{
		CGraphNode<T>* Node = new CGraphNode<T>;
		Node->mData = Data;

		mNodeArray.push_back(Node);
	}

	void CreateNodeLink(const T& Data1, const T& Data2)
	{
		CGraphNode<T>* Node1 = nullptr;
		CGraphNode<T>* Node2 = nullptr;

		int Size = mNodeArray.size();
		for (int i = 0; i < Size; ++i)
		{
			if (mNodeArray[i]->mData == Data1)
			{
				Node1 = mNodeArray[i];
			}
			else if (mNodeArray[i]->mData == Data2)
			{
				Node2 = mNodeArray[i];
			}
			
			if (Node1 && Node2)
			{
				break;
			}
		}

		if (!Node1 || !Node2)
		{
			return;
		}

		Node1->AddEdge(Node2);
		Node2->AddEdge(Node1);
	}

	// 너비 우선 탐색
	void BFS(const T& Data)
	{
		CGraphNode<T>* Node = nullptr;

		int Size = mNodeArray.size();
		for (int i = 0; i < Size; ++i)
		{
			if (mNodeArray[i]->mData == Data)
			{
				Node = mNodeArray[i];
			}

			mNodeArray[i]->mVisit = false;
		}

		if (!Node)
		{
			return;
		}

		CQueue<CGraphNode<T>*> VisitQueue;

		Node->mVisit = true;
		VisitQueue.push(Node);

		while (!VisitQueue.empty())
		{
			VisitQueue.front(Node);
			VisitQueue.pop();

			std::cout << Node->mData << " ";

			// 꺼내온 노드에서 연결된 모든 노드를 Queue에 추가
			
			Node->AddLinkNode(VisitQueue);
		}

	}

	// 깊이 우선 탐색
	void DFS(const T& Data)
	{
		CGraphNode<T>* Node = nullptr;

		int Size = mNodeArray.size();
		for (int i = 0; i < Size; ++i)
		{
			if (mNodeArray[i]->mData == Data)
			{
				Node = mNodeArray[i];
			}

			mNodeArray[i]->mVisit = false;
		}

		if (!Node)
		{
			return;
		}

		CStack<CGraphNode<T>*> VisitStack;

		Node->mVisit = true;
		VisitStack.push(Node);

		while (!VisitStack.empty())
		{
			VisitStack.top(Node);
			VisitStack.pop();

			std::cout << Node->mData << " ";

			// 꺼내온 노드에서 연결된 모든 노드를 Queue에 추가

			Node->AddLinkNode(VisitStack);
		}
	}
};
