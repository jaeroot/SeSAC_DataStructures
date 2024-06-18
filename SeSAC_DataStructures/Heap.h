#pragma once
#include "Array.h"

template <typename T>
class CHeap
{
public:
	CHeap()
	{

	}

	CHeap(bool (*Func)(const T&, const T&))
	{
		mSortFunc = Func;
	}

	~CHeap()
	{

	}

private:
	CArray<T> mArray;
	bool (*mSortFunc)(const T&, const T&) = nullptr;

public:
	void SetSortFunction(bool (*Func)(const T&, const T&))
	{
		mSortFunc = Func;
	}

public:
	void Insert(const T& Data)
	{
		if (!mSortFunc)
		{
			return;
		}

		mArray.push_back(Data);
		HeapInsert(mArray.size() / 2 - 1, mArray.size() - 1);
	}

	void Insert(const T* Data, int Count)
	{
		for (int i = 0; i < Count; ++i)
		{
			mArray.push_back(Data[i]);
			Insert(mArray.size() / 2 - 1, mArray.size() - 1);
		}
	}

	const T& front()
	{
		if (!Empty())
		{
			return mArray[0];
		}
	}

	void pop()
	{
		mArray[0] = mArray[mArray.size() - 1];

		mArray.pop_back();

		Erase(0);
	}

	int Size() const
	{
		return mArray.size();
	}

	bool Empty() const
	{
		return mArray.empty();
	}

private:
	void Insert(int ParentIndex, int CurrentIndex)
	{
		if (ParentIndex < 0)
		{
			return;
		}

		if (mSortFunc(mArray[ParentIndex], mArray[CurrentIndex]))
		{
			T Temp = mArray[ParentIndex];
			mArray[ParentIndex] = mArray[CurrentIndex];
			mArray[CurrentIndex] = Temp;

			Insert((ParentIndex + 1) / 2 - 1, ParentIndex);
		}
	}

	void Erase(int CurrentIndex)
	{
		int LeftChild = CurrentIndex * 2 + 1;

		if (LeftChild >= Size)
		{
			return;
		}

		// 최종 비교 인덱스
		int ChildIndex = LeftChild;

		int RightChild = LeftChild + 1;

		if (RightChild < mArray.size())
		{
			// 왼쪽 자식노드의 값과 오른쪽 자식노드의 값을 비교하여 둘 중 비교할 대상을 정함
			if (mSortFunc(mArray[LeftChild], mArray[RightChild]))
			{
				ChildIndex = RightChild;
			}
		}

		if (mSortFunc(mArray[CurrentIndex], mArray[ChildIndex]))
		{
			T Temp = mArray[ChildIndex];
			mArray[ChildIndex] = mArray[CurrentIndex];
			mArray[CurrentIndex] = mArray[ChildIndex];
		}

		Erase(ChildIndex);
	}
};

