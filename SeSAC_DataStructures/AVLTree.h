#pragma once
#include <algorithm>
#include <iostream>
//#include <stdlib.h>

template <typename KEY, typename VALUE>
class CAVLTreeNode
{
	template <typename KEY, typename VALUE>
	friend class CAVLTree;

	template <typename KEY, typename VALUE>
	friend class CAVLTreeIterator;

private:
	CAVLTreeNode()
	{

	}

	~CAVLTreeNode()
	{

	}

public:
	KEY mKey;
	VALUE mValue;

private:
	CAVLTreeNode<KEY, VALUE>* mParent = nullptr;

	CAVLTreeNode<KEY, VALUE>* mLeft = nullptr;
	CAVLTreeNode<KEY, VALUE>* mRight = nullptr;

	CAVLTreeNode<KEY, VALUE>* mPrev = nullptr;
	CAVLTreeNode<KEY, VALUE>* mNext = nullptr;
};

template <typename KEY, typename VALUE>
class CAVLTreeIterator
{
	template <typename KEY, typename VALUE>
	friend class CAVLTree;

public:
	CAVLTreeIterator()
	{

	}

	~CAVLTreeIterator()
	{

	}

private:
	CAVLTreeNode<KEY, VALUE>* mNode = nullptr;

public:
	bool operator==(const CAVLTreeIterator<KEY, VALUE>& iter) const
	{
		return mNode == iter.mNode;
	}

	bool operator!=(const CAVLTreeIterator<KEY, VALUE>& iter) const
	{
		return mNode != iter.mNode;
	}

	void operator++()
	{
		mNode = mNode->mNext;
	}
	void operator++(int)
	{
		mNode = mNode->mNext;
	}

	void operator--()
	{
		mNode = mNode->mPrev;
	}
	void operator--(int)
	{
		mNode = mNode->mPrev;
	}

	// iter->를 하게 되면 mNode->를 한 것과 같음
	CAVLTreeNode<KEY, VALUE>* operator->()
	{
		return mNode;
	}
};

template <typename KEY, typename VALUE>
class CAVLTree
{
public:
	CAVLTree()
	{
		mBegin = new Node;
		mEnd = new Node;

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
	}

	~CAVLTree()
	{
		Node* DeleteNode = mBegin;

		while (DeleteNode != nullptr)
		{
			Node* Next = DeleteNode->mNext;
			delete DeleteNode;
			DeleteNode = Next;
		}
	}

private:
	using Node = CAVLTreeNode<KEY, VALUE>;

public:
	using iterator = CAVLTreeIterator<KEY, VALUE>;

private:
	Node* mRoot = nullptr;
	Node* mBegin = nullptr;
	Node* mEnd = nullptr;
	int mSize = 0;

public:
	// 모든 노드의 데이터, 왼쪽, 오른쪽, 부모의 데이터를 출력하는 테스트용 함수
	void OutputTree()
	{
		iterator iter = Begin();
		iterator iterEnd = End();

		for (; iter != iterEnd; ++iter)
		{
			std::cout << "Key : " << iter.mNode->mKey;
			std::cout << "\tData : " << iter.mNode->mValue;
			std::cout << "\tLeft : ";
			if (iter.mNode->mLeft)
			{
				std::cout << iter.mNode->mLeft->mValue;
			}
			else
			{
				std::cout << "없음";
			}
			std::cout << "\tRight : ";
			if (iter.mNode->mRight)
			{
				std::cout << iter.mNode->mRight->mValue;
			}
			else
			{
				std::cout << "없음";
			}
			std::cout << "\tParent : ";
			if (iter.mNode->mParent)
			{
				std::cout << iter.mNode->mParent->mValue;
			}
			else
			{
				std::cout << "없음";
			}
			std::cout << std::endl;
		}
	}

public:
	void Insert(const KEY& Key, const VALUE& Value)
	{
		if (mRoot == nullptr)
		{
			mRoot = new Node;
			mRoot->mKey = Key;
			mRoot->mValue = Value;

			mBegin->mNext = mRoot;
			mRoot->mPrev = mBegin;

			mRoot->mNext = mEnd;
			mEnd->mPrev = mRoot;

			++mSize;
		}
		else
		{
			Insert(Key, Value, mRoot);
		}
	}

	void Insert_Iteration(const KEY& Key, const VALUE& Value)
	{
		if (mRoot == nullptr)
		{
			mRoot = new Node;
			mRoot->mKey = Key;
			mRoot->mValue = Value;

			mBegin->mNext = mRoot;
			mRoot->mPrev = mBegin;

			mRoot->mNext = mEnd;
			mEnd->mPrev = mRoot;

			++mSize;
		}
		else
		{
			Node* CurrentNode = mRoot;

			while (CurrentNode != nullptr)
			{
				if (Key <= CurrentNode->mKey)
				{
					if (!CurrentNode->mLeft)
					{
						Node* NewNode = new Node;
						NewNode->mKey = Key;
						NewNode->mValue = Value;

						// 현재 노드의 왼쪽 자식 노드로 붙여줌
						CurrentNode->mLeft = NewNode;
						NewNode->mParent = CurrentNode;

						// CurrentNode와 CurrentNode의 이전 노드 사이에 새로 생성한 노드를 붙여줌
						Node* Prev = CurrentNode->mPrev;

						Prev->mNext = NewNode;
						NewNode->mPrev = Prev;

						NewNode->mNext = CurrentNode;
						CurrentNode->mPrev = NewNode;

						++mSize;

						break;
					}
					else
					{
						CurrentNode = CurrentNode->mLeft;
					}
				}
				else
				{
					if (!CurrentNode->mRight)
					{
						// 오른쪽에 노드가 없을 경우 오른쪽 노드로 붙여줌
						if (!CurrentNode->mRight)
						{
							Node* NewNode = new Node;
							NewNode->mKey = Key;
							NewNode->mValue = Value;

							// 현재 노드의 오른쪽 자식 노드로 붙여줌
							CurrentNode->mRight = NewNode;
							NewNode->mParent = CurrentNode;

							// CurrentNode와 CurrentNode의 다음 노드 사이에 새로 생성한 노드를 붙여줌
							Node* Next = CurrentNode->mNext;

							CurrentNode->mNext = NewNode;
							NewNode->mPrev = CurrentNode;

							NewNode->mNext = Next;
							Next->mPrev = NewNode;

							++mSize;

							break;
						}
						else
						{
							CurrentNode = CurrentNode->mRight;
						}
					}
				}
			}
		}
	}

	int Size() const
	{
		return mSize;
	}

	int Empty() const
	{
		return mSize == 0;
	}

	void Clear()
	{
		Node* DeleteNode = mBegin->mNext;

		while (DeleteNode != mEnd)
		{
			Node* Next = DeleteNode->mNext;
			delete DeleteNode;
			DeleteNode = Next;
		}

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
		mSize = 0;
	}

	iterator& Begin() const
	{
		static iterator iter;
		iter.mNode = mBegin->mNext;
		return iter;
	}

	iterator& End() const
	{
		static iterator iter;
		iter.mNode = mEnd;
		return iter;
	}

	iterator& Find(const KEY& Key) const
	{
		if (mSize == 0)
		{
			return End();
		}

		return Find(Key, mRoot);
	}

	iterator& Find_Iteration(const KEY& Key) const
	{
		if (Empty())
		{
			return End();
		}

		auto CurrentNode = mRoot;
		while (CurrentNode != nullptr)
		{
			if (CurrentNode->mKey == Key)
			{
				static iterator iter;
				iter.mNode = CurrentNode;
				return iter;
			}
			else if (Key < CurrentNode->mKey)
			{
				CurrentNode = CurrentNode->mLeft;
			}
			else
			{
				CurrentNode = CurrentNode->mRight;
			}
		}

		return End();
	}

	iterator erase(const KEY& Key)
	{
		iterator iter = Find(Key);
		if (iter == End())
		{
			return iter;
		}

		return erase(iter);
	}

	iterator erase(const iterator& iter)
	{
		if (iter == End())
		{
			return iter;
		}

		// 리프노드인지 판단
		if (!iter.mNode->mLeft && !iter.mNode->mRight)
		{
			// 지울 노드의 부모노드가 없을 수도 있음
			// 이 경우 루트노드인데, 이 if문 안은 이미 리프노드일 때 들어오는 조건이므로
			// 루트인데 리프노드라면 마지막 1개 남은 노드를 제거하는 것이 좋음
			if (!iter.mNode->mParent)
			{
				mRoot = nullptr;
			}
			// 지울 노드가 부모노드의 왼쪽 자식인지, 오른쪽 자식인지를 판단하여 해당 주소를 nullptr로 변경
			else if (iter.mNode->mParent->mLeft == iter.mNode)
			{
				iter.mNode->mParent->mLeft = nullptr;
			}
			else
			{
				iter.mNode->mParent->mRight = nullptr;
			}
			Node* Prev = iter.mNode->mPrev;
			Node* Next = iter.mNode->mNext;

			Prev->mNext = Next;
			Next->mPrev = Prev;

			ReBalance(iter.mNode->mParent);

			delete iter.mNode;
			--mSize;

			iterator result;
			result.mNode = Next;
			return result;
		}
		else if (iter.mNode->mLeft)
		{
			Node* DeleteNode = FindMax(iter.mNode->mLeft);

			// 노드의 Key와 Value를 지울노드의 Key와 Value로 대체
			iter.mNode->mKey = DeleteNode->mKey;
			iter.mNode->mValue = DeleteNode->mValue;

			// 찾아온 노드의 왼쪽 자식이 있을 경우 왼쪽 자식노드를 지울노드의 자리로 옮겨줌 
			if (DeleteNode->mLeft)
			{
				if (DeleteNode->mParent->mLeft == DeleteNode)
				{
					DeleteNode->mParent->mLeft = DeleteNode->mLeft;
				}
				else
				{
					DeleteNode->mParent->mRight = DeleteNode->mLeft;
				}

				DeleteNode->mLeft->mParent = DeleteNode->mParent;
			}
			else
			{
				if (DeleteNode->mParent->mLeft == DeleteNode)
				{
					DeleteNode->mParent->mLeft = nullptr;
				}
				else
				{
					DeleteNode->mParent->mRight = nullptr;
				}
			}

			Node* Prev = DeleteNode->mPrev;
			Node* Next = DeleteNode->mNext;

			Prev->mNext = Next;
			Next->mPrev = Prev;

			ReBalance(DeleteNode->mParent);

			delete DeleteNode;
			--mSize;

			iterator result;
			result.mNode = Next;
			return result;
		}
		else
		{
			Node* DeleteNode = FindMin(iter.mNode->mRight);

			// 노드의 Key와 Value를 지울노드의 Key와 Value로 대체
			iter.mNode->mKey = DeleteNode->mKey;
			iter.mNode->mValue = DeleteNode->mValue;

			// 찾아온 노드의 오른쪽 자식이 있을 경우 오른쪽 자식노드를 지울노드의 자리로 옮겨줌 
			if (DeleteNode->mRight)
			{
				if (DeleteNode->mParent->mLeft == DeleteNode)
				{
					DeleteNode->mParent->mLeft = DeleteNode->mRight;
				}
				else
				{
					DeleteNode->mParent->mRight = DeleteNode->mRight;
				}

				DeleteNode->mRight->mParent = DeleteNode->mParent;
			}
			else
			{
				if (DeleteNode->mParent->mLeft == DeleteNode)
				{
					DeleteNode->mParent->mLeft = nullptr;
				}
				else
				{
					DeleteNode->mParent->mRight = nullptr;
				}
			}

			Node* Prev = DeleteNode->mPrev;
			Node* Next = DeleteNode->mNext;

			Prev->mNext = Next;
			Next->mPrev = Prev;

			ReBalance(DeleteNode->mParent);

			delete DeleteNode;
			--mSize;

			iterator result;
			result.mNode = Next;
			return result;
		}
	}

	//T& operator[](const KEY& Key) const
	//{
	//	iterator iter = Find(Key);
	//	if (iter == End())
	//	{
	//		Insert()
	//	}

	//	return iter.mNode->mValue;
	//}

	void Preorder()
	{
		std::cout << "preorder : ";
		Preorder(mRoot);

		std::cout << std::endl;
	}

	void Inorder()
	{
		std::cout << "inorder : ";

		Inorder(mRoot);

		std::cout << std::endl;
	}

	void Postorder()
	{
		std::cout << "postorder : ";

		Postorder(mRoot);

		std::cout << std::endl;
	}

private:
	void Insert(const KEY& Key, const VALUE& Value, Node* CurrentNode)
	{
		if (!CurrentNode)
		{
			return;
		}

		// 왼쪽
		if (Key <= CurrentNode->mKey)
		{
			// 왼쪽에 노드가 없을 경우 왼쪽 노드로 붙여줌
			if (!CurrentNode->mLeft)
			{
				Node* NewNode = new Node;
				NewNode->mKey = Key;
				NewNode->mValue = Value;

				// 현재 노드의 왼쪽 자식 노드로 붙여줌
				CurrentNode->mLeft = NewNode;
				NewNode->mParent = CurrentNode;

				// CurrentNode와 CurrentNode의 이전 노드 사이에 새로 생성한 노드를 붙여줌
				Node* Prev = CurrentNode->mPrev;

				Prev->mNext = NewNode;
				NewNode->mPrev = Prev;

				NewNode->mNext = CurrentNode;
				CurrentNode->mPrev = NewNode;

				++mSize;

				// 새로 추가된 노드는 균형이 무너질 가능성이 없음
				// 그러므로 새로 추가된 노드부터 균형이 무너질 가능성이 있는 것은 부모노드의 부모노드임
				ReBalance(CurrentNode->mParent);

				return;
			}
			else	// 왼쪽에 노드가 있을 경우 왼쪽 노드를 CurrentNode로 넣어주면서 검사 다시 시작
			{
				Insert(Key, Value, CurrentNode->mLeft);
			}
		}
		else		// 오른쪽
		{
			// 오른쪽에 노드가 없을 경우 오른쪽 노드로 붙여줌
			if (!CurrentNode->mRight)
			{
				Node* NewNode = new Node;
				NewNode->mKey = Key;
				NewNode->mValue = Value;

				// 현재 노드의 오른쪽 자식 노드로 붙여줌
				CurrentNode->mRight = NewNode;
				NewNode->mParent = CurrentNode;

				// CurrentNode와 CurrentNode의 다음 노드 사이에 새로 생성한 노드를 붙여줌
				Node* Next = CurrentNode->mNext;

				CurrentNode->mNext = NewNode;
				NewNode->mPrev = CurrentNode;

				NewNode->mNext = Next;
				Next->mPrev = NewNode;

				++mSize;
				
				// 새로 추가된 노드는 균형이 무너질 가능성이 없음
				// 그러므로 새로 추가된 노드부터 균형이 무너질 가능성이 있는 것은 부모노드의 부모노드임
				ReBalance(CurrentNode->mParent);

				return;
			}
			else	// 오른쪽에 노드가 있을 경우 오른쪽 노드를 CurrentNode로 넣어주면서 검사 다시 시작
			{
				Insert(Key, Value, CurrentNode->mRight);
			}
		}
	}

	iterator& Find(const KEY& Key, Node* CurrentNode) const
	{
		if (!CurrentNode)
		{
			return End();
		}

		if (Key == CurrentNode->mKey)
		{
			static iterator iter;
			iter.mNode = CurrentNode;
			return iter;
		}
		else if (Key < CurrentNode->mKey)
		{
			return Find(Key, CurrentNode->mLeft);
		}

		return Find(Key, CurrentNode->mRight);
	}

	Node* FindMax(Node* CurrentNode) const
	{
		while (CurrentNode->mRight)
		{
			CurrentNode = CurrentNode->mRight;
		}

		return CurrentNode;
	}

	Node* FindMin(Node* CurrentNode) const
	{
		while (CurrentNode->mLeft)
		{
			CurrentNode = CurrentNode->mLeft;
		}

		return CurrentNode;
	}

	Node* RotationLeft(Node* CurrentNode)
	{
		// 현재 노드의 오른쪽 자식 노드를 얻어옴
		Node* RChild = CurrentNode->mRight;

		// 위에서 얻어온 오른쪽 자식노드의 왼쪽 자식 노드를 얻어옴
		Node* RLChild = RChild->mLeft;

		// 현재 노드의 부모노드를 얻어옴
		Node* Parent = CurrentNode->mParent;

		//부모 노드가 있을 경우
		if (Parent)
		{
			// 현재 노드가 부모노드의 왼쪽인지 오른쪽인지 판단
			if (Parent->mLeft == CurrentNode)
			{
				Parent->mLeft =  RChild;
			}
			else
			{
				Parent->mRight = RChild;
			}

			RChild->mParent = Parent;
		}
		// 부모 노드가 없을 경우
		else
		{
			mRoot = RChild;
			RChild->mParent = nullptr;
		}

		// CurrentNode와 RightChild Swap
		RChild->mLeft = CurrentNode;
		CurrentNode->mParent = RChild;

		// RLChild를 CurrentNode의 mRight로 Swap
		CurrentNode->mRight = RLChild;
		if (RLChild)
		{
			RLChild->mParent = CurrentNode;
		}

		return RChild;
	}

	Node* RotationRight(Node* CurrentNode)
	{
		// 현재 노드의 왼쪽 자식 노드를 얻어옴
		Node* LChild = CurrentNode->mLeft;
		
		// 위에서 얻어온 왼쪽 자식노드의 오른쪽 자식 노드를 얻어옴
		Node* LRChild = LChild->mRight;

		// 현재 노드의 부모노드를 얻어옴
		Node* Parent = CurrentNode->mParent;

		//부모 노드가 있을 경우
		if (Parent)
		{
			// 현재 노드가 부모노드의 왼쪽인지 오른쪽인지 판단
			if (Parent->mLeft == CurrentNode)
			{
				Parent->mLeft = LChild;
			}
			else
			{
				Parent->mRight = LChild;
			}

			LChild->mParent = Parent;			
		}
		// 부모 노드가 없을 경우
		else
		{
			mRoot = LChild;
			LChild->mParent = nullptr;
		}

		// CurrentNode와 LeftChild Swap
		LChild->mRight = CurrentNode;
		CurrentNode->mParent = LChild;

		// LRChild를 CurrentNode의 mLeft로 Swap
		CurrentNode->mLeft = LRChild;
		if (LRChild)
		{
			LRChild->mParent = CurrentNode;
		}

		return LChild;
	}

	int GetHeight(Node* CurrentNode) const
	{
		if (!CurrentNode)
		{
			return -1;
		}

		// 왼쪽과 오른쪽 자식 노드를 검사하여 높이가 더 큰 높이로 지정
		int LeftHeight = GetHeight(CurrentNode->mLeft);
		int RightHeight = GetHeight(CurrentNode->mRight);

		return std::max(LeftHeight, RightHeight) + 1;
		//return LeftHeight < RightHeight ? RightHeight + 1 : LeftHeight + 1;
	}

	int BalanceFactor(Node* CurrentNode) const
	{
		if (!CurrentNode)
		{
			return 0;
		}

		// 왼쪽과 오른쪽의 차이를 구하여 반환
		return GetHeight(CurrentNode->mLeft) - GetHeight(CurrentNode->mRight);
	}

	Node* Balance(Node* CurrentNode)
	{
		int Factor = BalanceFactor(CurrentNode);
		
		// abs : 절대값을 구해줌
		if (std::abs(Factor) < 2)
		{
			return CurrentNode;
		}

		// 왼쪽 방향으로 균형이 무너졌을 경우 양수가 나오고
		// 오른쪽 방향으로 균형이 무너졌을 경우 음수가 나옴
		if (Factor > 0)
		{
			if (BalanceFactor(CurrentNode->mLeft) < 0)
			{
				RotationLeft(CurrentNode->mLeft);
			}
			CurrentNode = RotationRight(CurrentNode);

			//// 왼쪽, 왼쪽으로 균형이 무너졌는지 판단
			//if (BalanceFactor(CurrentNode->mLeft) > 0)
			//{
			//	CurrentNode = RotationRight(CurrentNode);
			//}
			//// 왼쪽, 오른쪽으로 균형이 무너진 경우
			//else
			//{
			//	RotationLeft(CurrentNode->mLeft);
			//	CurrentNode = RotationRight(CurrentNode);
			//}
		}
		else
		{
			if (BalanceFactor(CurrentNode->mRight) > 0)
			{
				RotationRight(CurrentNode->mRight);
			}
			CurrentNode = RotationLeft(CurrentNode);
		}

		return CurrentNode;
	}

	void ReBalance(Node* CurrentNode)
	{
		while (CurrentNode)
		{
			Balance(CurrentNode);

			CurrentNode = CurrentNode->mParent;
		}

		// 재귀
		//if (!CurrentNode)
		//{
		//	return;
		//}

		//Balance(CurrentNode);

		//ReBalance(CurrentNode->mParent);
	}

	void Preorder(Node* CurrentNode)
	{
		if (CurrentNode == nullptr)
		{
			return;
		}

		std::cout << CurrentNode->mKey << " ";
		Preorder(CurrentNode->mLeft);
		Preorder(CurrentNode->mRight);
	}

	void Inorder(Node* CurrentNode)
	{
		if (CurrentNode == nullptr)
		{
			return;
		}

		Inorder(CurrentNode->mLeft);
		std::cout << CurrentNode->mKey << " ";
		Inorder(CurrentNode->mRight);
	}

	void Postorder(Node* CurrentNode)
	{
		if (CurrentNode == nullptr)
		{
			return;
		}

		Postorder(CurrentNode->mLeft);
		Postorder(CurrentNode->mRight);
		std::cout << CurrentNode->mKey << " ";
	}
};