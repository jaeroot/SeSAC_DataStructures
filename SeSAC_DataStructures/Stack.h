#pragma once

template <typename T>
class CStackNode
{
	template <typename T>
	friend class CStack;

public:
	CStackNode()
	{

	}

	~CStackNode()
	{

	}

private:
	T mData;
	CStackNode<T>* mNext = nullptr;
};

template <typename T>
class CStack
{
public:
	CStack()
	{

	}

	~CStack()
	{
		while (mNode != nullptr)
		{
			Node* Next = mNode->mNext;

			delete mNode;

			mNode = Next;
		}
	}

private:
	using Node = CStackNode<T>;

private:
	Node* mNode = nullptr;
	int mSize = 0;

public:
	void push(const T& Data)
	{
		Node* NewNode = new Node;
		NewNode->mData = Data;
		
		NewNode->mNext = mNode;
		mNode = NewNode;

		++mSize;
	}

	void pop()
	{
		if (mSize == 0)
		{
			return;
		}

		Node* Next = mNode->mNext;
		delete mNode;

		mNode = Next;

		--mSize;
	}

	bool top(T& Data) const
	{
		if (mSize == 0)
		{
			return false;
		}

		Data = mNode->mData;

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
		while (mNode != nullptr)
		{
			Node* Next = mNode->mNext;

			delete mNode;

			mNode = Next;
		}

		mSize = 0;
	}
};

