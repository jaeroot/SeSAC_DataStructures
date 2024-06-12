#pragma once

template <typename T>
class CArray
{
public:
	CArray()
	{
		mCapacity = 4;

		mArray = new T[mCapacity];
	}

	~CArray()
	{
		delete[] mArray;
	}

private:
	T* mArray;
	int mSize = 0;		// ���� �߰��� ��
	int mCapacity;	// �Ҵܵ� �迭�� ��

public:
	void push_back(const T& Data)
	{
		// �� á�� ���
		if (mSize == mCapacity)
		{
			ReAlloc();
		}

		mArray[mSize] = Data;
		++mSize; 
	}

	void pop_back()
	{
		if (empty())
		{
			return;
		}

		--mSize;
	}

	int size() const
	{
		return mSize;
	}

	int capacity() const
	{
		return mCapacity;
	}

	bool empty()
	{
		return mSize == 0;
	}

	void clear()
	{
		mSize = 0;
	}

	void reserve(int Capacity)
	{
		mCapacity = Capacity;

		T* Array = new T[mCapacity];

		delete[] mArray;

		mArray = Array;

		mSize = 0;
	}

	void resize(int Size)
	{
		mCapacity = Size;

		T* Array = new T[mCapacity];

		delete[] mArray;

		mArray = Array;

		mSize = Size;
	}

	T& operator[] (int Index) const
	{
		return mArray[Index];
	}

private:
	void ReAlloc()
	{
		mCapacity *= 2;

		T* Array = new T[mCapacity];

		// ������ �־�� �ϴµ� memcpy�� ���� ��ĳ���õ� ��ü ������ �� vfptr�� ������ ��찡 ����
		// �����ʹ� ����, ��ӵ� ��ü�� ����
		memcpy(Array, mArray, sizeof(T) * mSize);

		// ���� �迭 ����
		delete[] mArray;

		// ���� ���� �迭�� �ּҸ� ��������� ����
		mArray = Array;
	}
};

