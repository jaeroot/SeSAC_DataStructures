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
	int mSize = 0;		// 실제 추가된 수
	int mCapacity;	// 할단된 배열의 수

public:
	void push_back(const T& Data)
	{
		// 꽉 찼을 경우
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

		// 복사해 주어야 하는데 memcpy를 쓰면 업캐스팅된 객체 복사할 때 vfptr이 깨지는 경우가 있음
		// 포인터는 ㄱㅊ, 상속된 객체는 문제
		memcpy(Array, mArray, sizeof(T) * mSize);

		// 기존 배열 제거
		delete[] mArray;

		// 새로 만든 배열의 주소를 멤버변수에 저장
		mArray = Array;
	}
};

