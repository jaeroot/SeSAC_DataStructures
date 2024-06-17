#pragma once

template <typename T>
class CSort
{
public:
	static void QuickSort(T* Data, int Size, bool (*Func)(const T&, const T&))
	{
		QuickSort(Data, 0, Size - 1, Func);
	}

private:
	static void QuickSort(T* Data, int Left, int Right, bool (*Func)(const T&, const T&))
	{
		if (Left < Right)
		{
			// 왼쪽과 오른쪽으로 분할
			int Pivot = Partition(Data, Left, Right, Func);

			// 왼쪽 분할
			QuickSort(Data, Left, Pivot - 1, Func);

			// 오른쪽 분할
			QuickSort(Data, Right, Pivot + 1, Func);
		}
	}

	static int Partition(T* Data, int Left, int Right, bool (*Func)(const T&, const T&))
	{
		int Low = Left;
		int High = Right + 1;
		int Pivot = Data[Left];

		do
		{
			do
			{
				++Low;
			} while (Low <= Right && Func(Pivot, Data[Low]));

			do
			{
				--High;
			} while (High >= Left && Func(Data[High], Pivot));

			if (Low < High)
			{
				T temp = Data[Low];
				Data[Low] = Data[High];
				Data[High] = temp;
			}
		} while (Low < High);

		T temp = Data[Left];
		Data[Left] = Data[High];
		Data[High] = temp;

		return High;
	}


private:
	static T* mMergeArray;

public:
	static void MergeSort(T* Data, int Size, bool (*Func)(const T&, const T&))
	{
		mMergeArray = new T[Size];

		MergeSort(Data, 0, Size - 1, Func);

		delete[] mMergeArray;
	}

private:
	static void MergeSort(T* Data, int Left, int Right, bool (*Func)(const T&, const T&))
	{
		if (Left < Right)
		{
			// 가운데를 구함
			int Mid = (Left + Right) / 2;

			MergeSort(Data, Left, Mid, Func);
			MergeSort(Data, Mid + 1, Right, Func);

			Merge(Data, Left, Mid, Right, Func);
		}
	}

	static void Merge(T* Data, int Left, int Mid, int Right, bool (*Func)(const T&, const T&))
	{
		int SrcLeft = Left;
		int SrcRight = Mid + 1;
		int Dest = Left;

		// 왼쪽, 오른쪽으로 분할된 배열을 합침
		while (SrcLeft <= Mid && SrcRight <= Right)
		{
			if (Func(Data[SrcLeft], Data[SrcRight]))
			{
				mMergeArray[Dest] = Data[SrcRight];
				++SrcRight;
				++Dest;
			}
			else
			{
				mMergeArray[Dest] = Data[SrcLeft];
				++SrcLeft;
				++Dest;
			}
		}

		// 왼쪽 배열이 남았을 경우
		if (SrcLeft <= Mid)
		{
			for (int i = SrcLeft; i <= Mid; ++i)
			{
				mMergeArray[Dest] = Data[i];
				++Dest;
			}
		}
		// 오른쪽 배열이 남았을 경우
		else
		{
			for (int i = SrcRight; i <= Right; ++i)
			{
				mMergeArray[Dest] = Data[i];
				++Dest;
			}
		}

		// 복사본 배열에 정렬된 데이터가 들어가 있기 때문에 이를 원본 배열에 복사해줌
		for (int i = Left; i <= Right; ++i)
		{
			Data[i] = mMergeArray[i];
		}
	}


public:
	static void HeapSort(T* Data, int Size, bool (*Func)(const T&, const T&))
	{
		mMergeArray = new T[Size];
		
		for (int i = 0; i < Size; ++i)
		{
			mMergeArray[i] = Data[i];
			HeapInsert((i + 1) / 2, i + 1, Func);
		}

		delete[] mMergeArray;
	}

private:
	static void HeapInsert(int ParentIndex, int Index, bool (*Func)(const T&, const T&))
	{

	}

};


template <typename T>
T* CSort<T>::mMergeArray = nullptr;