
#include <malloc.h>

#define HEAP_MIN_SIZE 8

template<typename T>
class BinaryHeap
{
public:
	BinaryHeap(unsigned int size = HEAP_MIN_SIZE) :
		m_array(NULL),
		m_size(size > HEAP_MIN_SIZE ? size : HEAP_MIN_SIZE),
		m_heapSize(0)
	{
		m_array = (T*)malloc(m_size * sizeof(T));

		// to silent errors checker
		m_array[0] = T();
	}

	~BinaryHeap()
	{
		if(m_array)	free(m_array);
	}

	void insert(T const& item)
	{
		m_array[++m_heapSize] = item;

		if(m_heapSize + 1 == m_size)	resizeArray(m_size * 2);

		swim(m_heapSize);
	}

	bool delMax(T& item)
	{
		if(m_heapSize < 1)	return false;

		item = m_array[1];

		m_array[1] = m_array[m_heapSize--];

		if(m_heapSize < (m_size / 4))	resizeArray(m_size / 2);

		sink(1);

		return true;
	}

	bool isEmpty()
	{
		return m_heapSize > 0 ? false : true;
	}

#ifdef _QDEBUG
	void debugPrint()
	{
		for(unsigned int i = 0; i <= m_heapSize; ++i) printf("%d ", m_array[i]);

		printf("\n");
	}
#endif

private:
	void sink(unsigned int pos)
	{
		while(pos * 2 <= m_heapSize)
		{
			unsigned int k = pos * 2;
			if(k < m_heapSize && m_array[k + 1] > m_array[k]) ++k;
			if(!(m_array[k] > m_array[pos])) break;

			exch(m_array[k], m_array[pos]);
			pos = k;
		}
	}

	void swim(unsigned int pos)
	{
		while(pos > 1 && m_array[pos / 2] < m_array[pos])
		{
			exch(m_array[pos], m_array[pos / 2]);
			pos /= 2;
		}
	}

	void exch(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	void resizeArray(unsigned int size)
	{
		if(size < HEAP_MIN_SIZE)	return;

#ifdef _QDEBUG
		printf("\n%s:%d %s m_size: %u \n\n", __FILE__, __LINE__, __FUNCTION__, m_size);
#endif

		T* tmp = (T*)realloc(m_array, size * sizeof(T));
		if(!tmp)
		{
#ifdef _QDEBUG
			printf("%s:%d %s MALLOC ERROR \n", __FILE__, __LINE__, __FUNCTION__);
#endif
			return ;
		}

		m_size = size;
		m_array = tmp;
#ifdef _QDEBUG
		printf("\n%s:%d %s m_size: %u \n\n", __FILE__, __LINE__, __FUNCTION__, m_size);
#endif
	}

private:
	T* m_array;

	unsigned int m_size;
	unsigned int m_heapSize;
};
