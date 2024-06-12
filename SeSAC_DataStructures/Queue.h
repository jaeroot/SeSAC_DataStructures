#pragma once

template <typename T>
class CQueueNode
{
	template <typename T>
	friend class CQueue;

public:
	CQueueNode()
	{

	}

	~CQueueNode()
	{

	}

private:
	T mData;
	CQueueNode<T>* mNext = nullptr;
};

template <typename T>
class CQueue
{
public:
	CQueue()
	{

	}

	~CQueue()
	{
		while (mFirst != nullptr)
		{
			Node* Next = mFirst->mNext;

			delete mFirst;

			mFirst = Next;
		}
	}

private:
	using Node = CQueueNode<T>;

private:
	Node* mFirst = nullptr;
	Node* mLast = nullptr;

	int mSize = 0;

public:
	void push(const T& Data)
	{
		Node* NewNode = new Node;

		NewNode->mData = Data;

		if (mSize == 0)
		{
			mFirst = NewNode;
		}
		else
		{
			mLast->mNext = NewNode;
		}
		mLast = NewNode;

		++mSize;
	}

	void pop()
	{
		if (mSize == 0)
		{
			return;
		}

		Node* Next = mFirst->mNext;
		delete mFirst;

		mFirst = Next;

		--mSize;
	}

	bool front(T& Data) const
	{
		if (mSize == 0)
		{
			return false;
		}

		Data = mFirst->mData;

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
		while (mFirst != nullptr)
		{
			Node* Next = mFirst->mNext;

			delete mFirst;

			mFirst = Next;
		}

		mLast = nullptr;
		mSize = 0;
	}
};

