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

	// iter->�� �ϰ� �Ǹ� mNode->�� �� �Ͱ� ����
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
	// ��� ����� ������, ����, ������, �θ��� �����͸� ����ϴ� �׽�Ʈ�� �Լ�
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
				std::cout << "����";
			}
			std::cout << "\tRight : ";
			if (iter.mNode->mRight)
			{
				std::cout << iter.mNode->mRight->mValue;
			}
			else
			{
				std::cout << "����";
			}
			std::cout << "\tParent : ";
			if (iter.mNode->mParent)
			{
				std::cout << iter.mNode->mParent->mValue;
			}
			else
			{
				std::cout << "����";
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

				// ���� �߰��� ���� ������ ������ ���ɼ��� ����
				// �׷��Ƿ� ���� �߰��� ������ ������ ������ ���ɼ��� �ִ� ���� �θ����� �θ�����
				ReBalance(CurrentNode->mParent);

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
				
				// ���� �߰��� ���� ������ ������ ���ɼ��� ����
				// �׷��Ƿ� ���� �߰��� ������ ������ ������ ���ɼ��� �ִ� ���� �θ����� �θ�����
				ReBalance(CurrentNode->mParent);

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

	Node* RotationLeft(Node* CurrentNode)
	{
		// ���� ����� ������ �ڽ� ��带 ����
		Node* RChild = CurrentNode->mRight;

		// ������ ���� ������ �ڽĳ���� ���� �ڽ� ��带 ����
		Node* RLChild = RChild->mLeft;

		// ���� ����� �θ��带 ����
		Node* Parent = CurrentNode->mParent;

		//�θ� ��尡 ���� ���
		if (Parent)
		{
			// ���� ��尡 �θ����� �������� ���������� �Ǵ�
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
		// �θ� ��尡 ���� ���
		else
		{
			mRoot = RChild;
			RChild->mParent = nullptr;
		}

		// CurrentNode�� RightChild Swap
		RChild->mLeft = CurrentNode;
		CurrentNode->mParent = RChild;

		// RLChild�� CurrentNode�� mRight�� Swap
		CurrentNode->mRight = RLChild;
		if (RLChild)
		{
			RLChild->mParent = CurrentNode;
		}

		return RChild;
	}

	Node* RotationRight(Node* CurrentNode)
	{
		// ���� ����� ���� �ڽ� ��带 ����
		Node* LChild = CurrentNode->mLeft;
		
		// ������ ���� ���� �ڽĳ���� ������ �ڽ� ��带 ����
		Node* LRChild = LChild->mRight;

		// ���� ����� �θ��带 ����
		Node* Parent = CurrentNode->mParent;

		//�θ� ��尡 ���� ���
		if (Parent)
		{
			// ���� ��尡 �θ����� �������� ���������� �Ǵ�
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
		// �θ� ��尡 ���� ���
		else
		{
			mRoot = LChild;
			LChild->mParent = nullptr;
		}

		// CurrentNode�� LeftChild Swap
		LChild->mRight = CurrentNode;
		CurrentNode->mParent = LChild;

		// LRChild�� CurrentNode�� mLeft�� Swap
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

		// ���ʰ� ������ �ڽ� ��带 �˻��Ͽ� ���̰� �� ū ���̷� ����
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

		// ���ʰ� �������� ���̸� ���Ͽ� ��ȯ
		return GetHeight(CurrentNode->mLeft) - GetHeight(CurrentNode->mRight);
	}

	Node* Balance(Node* CurrentNode)
	{
		int Factor = BalanceFactor(CurrentNode);
		
		// abs : ���밪�� ������
		if (std::abs(Factor) < 2)
		{
			return CurrentNode;
		}

		// ���� �������� ������ �������� ��� ����� ������
		// ������ �������� ������ �������� ��� ������ ����
		if (Factor > 0)
		{
			if (BalanceFactor(CurrentNode->mLeft) < 0)
			{
				RotationLeft(CurrentNode->mLeft);
			}
			CurrentNode = RotationRight(CurrentNode);

			//// ����, �������� ������ ���������� �Ǵ�
			//if (BalanceFactor(CurrentNode->mLeft) > 0)
			//{
			//	CurrentNode = RotationRight(CurrentNode);
			//}
			//// ����, ���������� ������ ������ ���
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

		// ���
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