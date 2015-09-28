
#include <malloc.h>
#include <string.h>

#include <iostream>

#define QUEUE_MIN_SIZE 8

template<typename T>
class QueueArray
{
public:
	QueueArray(unsigned int size = QUEUE_MIN_SIZE) :
		m_array(NULL),
		m_first(0),
		m_last(0),
		m_size(size > QUEUE_MIN_SIZE ? size : QUEUE_MIN_SIZE)
	{
		m_array = (T*)malloc(size * sizeof(T));
	}

	~QueueArray()
	{
		if(m_array)	free(m_array);
	}

	void enqueue(T const& item)
	{
		m_array[m_last++] = item;

		if(m_last == m_size)
		{
			if(m_first)	reorganizeArray();

			if(m_last > (m_size / 4) + (m_size / 2))	resizeArray(m_size * 2);
		}
	}

	bool dequeue(T& item)
	{
		if(m_last == m_first)	return false;

		item = m_array[m_first++];

		if((m_last - m_first) < (m_size / 4))
		{
			if(m_first)	reorganizeArray();

			resizeArray(m_size / 2);
		}

		return true;
	}

	bool isEmpty()
	{
		return m_last == m_first ? true : false;
	}

	unsigned int size()
	{
		return m_last - m_first;
	}

private:
	void resizeArray(unsigned int size)
	{
		if(size < QUEUE_MIN_SIZE)	return;

#ifdef _QDEBUG
		printf("\n%s:%d %s m_first: %u | m_last: %u | m_size: %u | size: %u\n\n", __FILE__, __LINE__, __FUNCTION__, m_first, m_last, m_size, size);
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
	}

	void reorganizeArray()
	{
		if(m_size == QUEUE_MIN_SIZE && m_last < (m_size /2))	return ;
#ifdef _QDEBUG
		printf("\nreorganizeArray before\n");
		for(unsigned int i = m_first; i < m_last; ++i)
		{
			std::cout << m_array[i] << " ";
		}
		std::cout << std::endl;
#endif

		memmove(m_array, m_array + m_first, (m_last - m_first) * sizeof(T));
		m_last = m_last - m_first;
		m_first = 0;
#ifdef _QDEBUG
		printf("\nreorganizeArray after\n");
		for(unsigned int i = 0; i < m_last; ++i)
		{
			std::cout << m_array[i] << " ";
		}
		std::cout << std::endl;
#endif
	}

private:
	T*	m_array;

	unsigned int m_first;
	unsigned int m_last;

	unsigned int m_size;
};
