#pragma once

/*
��ȯŸ�� operator ������ (����)
{
}
*/

template <typename T>
class CListNode
{
	// CLinkedList Ŭ���������� �� Ŭ������ private�̳� protected�� ������ �� �ְ� �Ѵ�.
	template <typename T>
	friend class CLinkedList;

	template <typename T>
	friend class CListIterator;

private:
	CListNode()
	{

	}

	~CListNode()
	{

	}

private:
	T mData;
	CListNode<T>* mNext = nullptr;	// ���� ����� �ּҸ� �����ϱ� ���� ����
	CListNode<T>* mPrev = nullptr;	// ���� ����� �ּҸ� �����ϱ� ���� ����
};

template <typename T>
class CListIterator
{
	template <typename T>
	friend class CLinkedList;
public:
	CListIterator()
	{

	}

	~CListIterator()
	{

	}

private:
	CListNode<T>* mNode = nullptr;

public:
	bool operator==(const CListIterator<T>& iter) const
	{
		return mNode == iter.mNode;
	}

	bool operator!=(const CListIterator<T>& iter) const
	{
		return mNode != iter.mNode;
	}

	// ���� ����
	void operator++()
	{
		mNode = mNode->mNext;
	}

	// ���� ����
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

	// ���ڰ� ������ ������ ������
	T& operator*()
	{
		return mNode->mData;
	}

	//// ������
	//operator CListNode<T>* ()
	//{
	//	return mNode;
	//}
	// CListNode<int>* Node = iterInt;

	//void* operator new (size_t Size)
	//{
	//	return nullptr;
	//}

	//void operator delete (void* Addr)
	//{
	//}
};

template <typename T>
class CLinkedList
{
public:
	CLinkedList()
	{
		mBegin = new Node;
		mEnd = new Node;

		// Begin�� End�� ����
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;

		mSize = 0;
	}

	~CLinkedList()
	{
		Node* DeleteNode = mBegin;

		while (nullptr != DeleteNode)
		{
			// ���� ���� ����� ���� ��� ����
			// �Ʒ����� ��� ���� ��, ���� ����� �޸� �ּҸ� ������ �� ���� ����
			Node* NextNode = DeleteNode->mNext;

			delete DeleteNode;

			DeleteNode = NextNode;
		}
	}

private:
	// typedef : Ÿ���� �������Ѵ�. 
	// CListNode<T> ��ſ� Node��� �ۼ��ص� CListNode<T> Ÿ���� ������ ����
	// typedef CListNode<T> Node;
	using Node = CListNode<T>;

public:
	using iterator = CListIterator<T>;

private:
	Node* mBegin;	// ����Ʈ�� ó���� ��Ÿ���� ���
	Node* mEnd;		// ����Ʈ�� ���� ��Ÿ���� ���
	int mSize;		// ���� �߰��� �������� ��

public:
	void push_back(const T& data)
	{
		Node* NewNode = new Node;

		NewNode->mData = data;

		// End���� End�� ���� ��� ���̿� ���� ������ ��� �߰�
		Node* Prev = mEnd->mPrev;
		Prev->mNext = NewNode;
		NewNode->mPrev = Prev;

		NewNode->mNext = mEnd;
		mEnd->mPrev = NewNode;

		++mSize;
	}

	void push_front(const T& data)
	{
		Node* NewNode = new Node;

		NewNode->mData = data;

		// End���� End�� ���� ��� ���̿� ���� ������ ��� �߰�
		Node* Next = mBegin->mNext;
		Next->mPrev = NewNode;
		NewNode->mNext = Next;

		NewNode->mPrev = mBegin;
		mBegin->mNext = NewNode;

		++mSize;
	}

	void pop_back()
	{
		if (mSize == 0)
		{
			return;
		}

		// ���� ��� ����
		Node* DeleteNode = mEnd->mPrev;

		// ���� ����� ���� ����� ���� ���� End ����
		// End�� ���� ���� ���� ����� ���� ��带 ����
		Node* Prev = DeleteNode->mPrev;

		Prev->mNext = mEnd;
		mEnd->mPrev = Prev;

		delete DeleteNode;

		--mSize;
	}

	void pop_front()
	{
		if (mSize == 0)
		{
			return;
		}

		// ���� ��� ����
		Node* DeleteNode = mBegin->mNext;

		// ���� ����� ���� ����� ���� ���� Begin ����
		// Begin�� ���� ���� ���� ����� ���� ��带 ����
		Node* Next = DeleteNode->mNext;

		Next->mPrev = mBegin;
		mBegin->mNext = Next;

		delete DeleteNode;

		--mSize;
	}

	bool front(T& data) const
	{
		if (mSize == 0)
		{
			return false;
		}

		data = mBegin->mNext->mData;

		return true;
	}

	bool back(T& data) const
	{
		if (mSize == 0)
		{
			return false;
		}

		data = mEnd->mPrev->mData;

		return true;
	}

	int size() const
	{
		return mSize;
	}

	bool empty() const
	{
		return mSize == 0;
	}

	void clear()
	{
		Node* DeleteNode = mBegin->mNext;

		while (DeleteNode != mEnd)
		{
			Node* Next = DeleteNode->mNext;

			delete DeleteNode;

			DeleteNode = Next;
		}

		// Begin�� End�� �����ϰ� Size�� 0���� �ʱ�ȭ
		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;

		mSize = 0;
	}

	// iterator�� �����ϰ�, iterator�� begin����� ���� ��带 ������ �ְ� �Ͽ� ��ȯ
	iterator& begin() const
	{
		static iterator iter;
		iter.mNode = mBegin->mNext;
		return iter;
	}

	iterator& end() const
	{
		static iterator iter;
		iter.mNode = mEnd;
		return iter;
	}

	// ���� ����� ���� ��带 ������ �ִ� iterator�� ��ȯ
	iterator erase(const T& Data)
	{
		iterator iter = begin();
		iterator iterEnd = end();

		for (; iter != iterEnd; ++iter)
		{
			if (*iter == Data)
			{
				break;
			}
		}

		if (iter == iterEnd)
		{
			return iterEnd;
		}

		return erase(iter);
	}

	iterator erase(iterator& iter)
	{
		Node* Prev = iter.mNode->mPrev;
		Node* Next = iter.mNode->mNext;

		Prev->mNext = Next;
		Next->mPrev = Prev;

		delete iter.mNode;

		iter.mNode = Next;

		return iter;
	}
};

