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

	// iter->�� �ϰ� �Ǹ� mNode->�� �� �Ͱ� ����
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

						// ���� ����� ���� �ڽ� ���� �ٿ���
						CurrentNode->mLeft = NewNode;
						NewNode->mParent = CurrentNode;

						// CurrentNode�� CurrentNode�� ���� ��� ���̿� ���� ������ ��带 �ٿ���
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
						// �����ʿ� ��尡 ���� ��� ������ ���� �ٿ���
						if (!CurrentNode->mRight)
						{
							Node* NewNode = new Node;
							NewNode->mKey = Key;
							NewNode->mValue = Value;

							// ���� ����� ������ �ڽ� ���� �ٿ���
							CurrentNode->mRight = NewNode;
							NewNode->mParent = CurrentNode;

							// CurrentNode�� CurrentNode�� ���� ��� ���̿� ���� ������ ��带 �ٿ���
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

		// ����������� �Ǵ�
		if (!iter.mNode->mLeft && !iter.mNode->mRight)
		{
			// ���� ����� �θ��尡 ���� ���� ����
			// �� ��� ��Ʈ����ε�, �� if�� ���� �̹� ��������� �� ������ �����̹Ƿ�
			// ��Ʈ�ε� ��������� ������ 1�� ���� ��带 �����ϴ� ���� ����
			if (!iter.mNode->mParent)
			{
				mRoot = nullptr;
			}
			// ���� ��尡 �θ����� ���� �ڽ�����, ������ �ڽ������� �Ǵ��Ͽ� �ش� �ּҸ� nullptr�� ����
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

			// ����� Key�� Value�� �������� Key�� Value�� ��ü
			iter.mNode->mKey = DeleteNode->mKey;
			iter.mNode->mValue = DeleteNode->mValue;

			// ã�ƿ� ����� ���� �ڽ��� ���� ��� ���� �ڽĳ�带 �������� �ڸ��� �Ű��� 
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

			// ����� Key�� Value�� �������� Key�� Value�� ��ü
			iter.mNode->mKey = DeleteNode->mKey;
			iter.mNode->mValue = DeleteNode->mValue;

			// ã�ƿ� ����� ������ �ڽ��� ���� ��� ������ �ڽĳ�带 �������� �ڸ��� �Ű��� 
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

		// ����
		if (Key <= CurrentNode->mKey)
		{
			// ���ʿ� ��尡 ���� ��� ���� ���� �ٿ���
			if (!CurrentNode->mLeft)
			{
				Node* NewNode = new Node;
				NewNode->mKey = Key;
				NewNode->mValue = Value;

				// ���� ����� ���� �ڽ� ���� �ٿ���
				CurrentNode->mLeft = NewNode;
				NewNode->mParent = CurrentNode;

				// CurrentNode�� CurrentNode�� ���� ��� ���̿� ���� ������ ��带 �ٿ���
				Node* Prev = CurrentNode->mPrev;

				Prev->mNext = NewNode;
				NewNode->mPrev = Prev;

				NewNode->mNext = CurrentNode;
				CurrentNode->mPrev = NewNode;

				++mSize;

				return;
			}
			else	// ���ʿ� ��尡 ���� ��� ���� ��带 CurrentNode�� �־��ָ鼭 �˻� �ٽ� ����
			{
				Insert(Key, Value, CurrentNode->mLeft);
			}
		}
		else		// ������
		{
			// �����ʿ� ��尡 ���� ��� ������ ���� �ٿ���
			if (!CurrentNode->mRight)
			{
				Node* NewNode = new Node;
				NewNode->mKey = Key;
				NewNode->mValue = Value;

				// ���� ����� ������ �ڽ� ���� �ٿ���
				CurrentNode->mRight = NewNode;
				NewNode->mParent = CurrentNode;

				// CurrentNode�� CurrentNode�� ���� ��� ���̿� ���� ������ ��带 �ٿ���
				Node* Next = CurrentNode->mNext;

				CurrentNode->mNext = NewNode;
				NewNode->mPrev = CurrentNode;

				NewNode->mNext = Next;
				Next->mPrev = NewNode;

				++mSize;

				return;
			}
			else	// �����ʿ� ��尡 ���� ��� ������ ��带 CurrentNode�� �־��ָ鼭 �˻� �ٽ� ����
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