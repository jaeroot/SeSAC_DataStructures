#pragma once

template <typename KEY, typename VALUE>
class CBinaryTreeNode
{
	template <typename KEY, typename VALUE>
	friend class CBinaryTree;

	template <typename KEY, typename VALUE>
	friend class CBinaryTreeIterator;

private:
	CBinaryTreeNode()
	{

	}

	~CBinaryTreeNode()
	{

	}

public:
	KEY mKey;
	VALUE mValue;

private:
	CBinaryTreeNode<KEY, VALUE>* mParent = nullptr;

	CBinaryTreeNode<KEY, VALUE>* mLeft = nullptr;
	CBinaryTreeNode<KEY, VALUE>* mRight = nullptr;

	CBinaryTreeNode<KEY, VALUE>* mPrev = nullptr;
	CBinaryTreeNode<KEY, VALUE>* mNext = nullptr;
};

template <typename KEY, typename VALUE>
class CBinaryTreeIterator
{
	template <typename KEY, typename VALUE>
	friend class CBinaryTree;

public:
	CBinaryTreeIterator()
	{

	}

	~CBinaryTreeIterator()
	{

	}

private:
	CBinaryTreeNode<KEY, VALUE>* mNode = nullptr;

public:
	bool operator==(const CBinaryTreeIterator<KEY, VALUE>& iter) const
	{
		return mNode == iter.mNode;
	}

	bool operator!=(const CBinaryTreeIterator<KEY, VALUE>& iter) const
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
	CBinaryTreeNode<KEY, VALUE>* operator->()
	{
		return mNode;
	}
};

template <typename KEY, typename VALUE>
class CBinaryTree
{
public:
	CBinaryTree()
	{
		mBegin = new Node;
		mEnd = new Node;

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
	}

	~CBinaryTree()
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
	using Node = CBinaryTreeNode<KEY, VALUE>;

public:
	using iterator = CBinaryTreeIterator<KEY, VALUE>;

private:
	Node* mRoot = nullptr;
	Node* mBegin = nullptr;
	Node* mEnd = nullptr;
	int mSize = 0;

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

			Node* Prev = iter.mNode->mPrev;
			Node* Next = iter.mNode->mNext;

			Prev->mNext = Next;
			Next->mPrev = Prev;

			delete iter.mNode;
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

			Node* Prev = iter.mNode->mPrev;
			Node* Next = iter.mNode->mNext;

			Prev->mNext = Next;
			Next->mPrev = Prev;

			delete iter.mNode;
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
};