
#include <stdio.h>
#include <time.h>

template<typename T>
inline void exch(T& pos1, T& pos2)
{
	T tmp = pos1;
	pos1 = pos2;
	pos2 = tmp;
}

template<typename T>
void insertSort(T* tab, int unsigned begin, unsigned int end)
{
	for(unsigned int i = begin + 1; i < end; ++i)
	{
		int j = i;
		while (j > begin && tab[j] < tab[j-1])
		{
			exch(tab[j], tab[j-1]);
			--j;
		}
	}
}

template<typename T>
void uniformShuffle(T* tab, unsigned int size)
{
	srand(time(NULL));

	unsigned int r, tmp;
	for(unsigned int i = 1; i < size; ++i)
	{
		r = rand() % (i + 1);
		if(r != i) 	exch(tab[i], tab[r]);
	}
}

namespace hiddenMergeSort
{
	template<typename T>
	void merge(T* tab, T* temp, unsigned int start, unsigned int middle, unsigned int end)
	{
		memcpy(temp + start, tab + start, (end - start + 1) * sizeof(T));

		int p1 = start, p2 = middle + 1;
		int tracer = start;
		while(tracer <= end)
		{
			if(p1 > middle)				tab[tracer++] = temp[p2++];
			else if(p2 > end)			tab[tracer++] = temp[p1++];
			else if(temp[p1] > temp[p2])tab[tracer++] = temp[p2++];
			else 						tab[tracer++] = temp[p1++];
		}
	}

	template<typename T>
	void ClassicMergeSort(T* tab, T* temp, unsigned int start, unsigned int end)
	{
		if(end - start < 7)
		{
			insertSort(tab, start, end+1);
			return ;
		}

		int middle = (end + start) / 2;
		mergeSort(tab, temp, start, middle);
		mergeSort(tab, temp, middle+1, end);
		if(tab[middle] > tab[middle+1])		merge(tab, temp, start, middle, end);
	}

	template<typename T>
	void BUmergeSort(T* tab, T* temp, unsigned int start, unsigned int end)
	{
		++end;
		for(unsigned int h = 2; h < (end + end); h += h)
		{
			for(unsigned int i = 0; i < end; i+=h)
			{
				int e = (i + h) <= end ? (i+h) : end;
				int middle = ((i + i + h) / 2) - 1;
				if(middle < end-1)
				{
					if(tab[middle] > tab[middle+1])	merge(tab, temp, i, middle, e-1);
				}
			}
		}
	}
}

namespace hiddenQuickSort
{
	template<typename T>
	unsigned int partition(T* tab, unsigned int start, unsigned int end)
	{
		unsigned int partitionElem = start;
		unsigned int p = start + 1, f = end;

		T tmp;
		while(f >= p)
		{
			while(f > p && tab[p] < tab[partitionElem])
			{
				exch(tab[p], tab[partitionElem]);
				++p; ++partitionElem;
			}
			bool flag = false;
			while(f > p && tab[p] == tab[partitionElem]){
				++p;
				flag = true;
			}
			if(flag) continue;
			if(p < f)	exch(tab[p], tab[f]);
			else if(tab[f] < tab[partitionElem])
			{
				exch(tab[f], tab[partitionElem]);
				++partitionElem;
			}

			--f;
		}

		return partitionElem;
	}

	template<typename T>
	void quickSort(T* tab, unsigned int start, unsigned int end)
	{
		if(start >= end) return;

		int res = partition(tab, start, end);
		unsigned int tmp;

		if(res != 0)
		{
			tmp = res - 1;
			while(tmp && tab[res] == tab[tmp])	--tmp;
			if(tmp && start != tmp) quickSort(tab, start, tmp);
		}

		if(res != end && res < end)
		{
			tmp = res + 1;
			while(tmp < end && tab[res] == tab[tmp]) ++tmp;
			if(tmp != end) quickSort(tab, tmp, end);
		}
	}
}

template<typename T>
void mergeSort(T* tab, unsigned int start, unsigned int end)
{
	if(end - start < 1) return;
	int size = end - start;
	int* temp = (int*)malloc(size*sizeof(T));

	hiddenMergeSort::BUmergeSort(tab, temp, start, end-1);

	free(temp);
}

template<typename T>
void quickSort(T* tab, unsigned int tabSize)
{
	hiddenQuickSort::quickSort(tab, 0, tabSize-1);
}

template<typename T>
void findNumOfBiggest(T* tab, unsigned int tabSize, unsigned int resultSize, bool shuffle = true)
{
	if(resultSize >= tabSize)	return;

	if(shuffle)	uniformShuffle(tab, tabSize);

	int pocz = 0;
	int end = tabSize -1;

	while(1)
	{
		unsigned int pos = hiddenQuickSort::partition(tab, pocz, end);

		if(tabSize - resultSize == pos) break;
		else if(tabSize - resultSize > pos)	pocz = ++pos;
		else	end = --pos;
	}
}






