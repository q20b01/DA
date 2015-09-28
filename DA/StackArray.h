
#include <malloc.h>

#define STACK_MIN_SIZE 8

template<typename T>
class StackArray
{
public:
	StackArray(unsigned int size = STACK_MIN_SIZE) :
		m_array(NULL),
		m_size(size > STACK_MIN_SIZE ? size : STACK_MIN_SIZE),
		m_sp(0)
	{
		m_array = (T*)malloc(m_size * sizeof(T));
	}

	~StackArray()
	{
		if(m_array)	free(m_array);
	}

	void push(T const& item)
	{
		m_array[m_sp++] = item;

		if(m_sp == m_size)	resizeArray(m_size * 2);
	}

	bool pop(T& item)
	{
		if(!m_sp)	return false;

		item = m_array[--m_sp];

		if(m_sp < (m_size / 4))	resizeArray(m_size / 2);

		return true;
	}

	bool isEmpty()
	{
		return m_sp ? true : false;
	}

private:
	void resizeArray(unsigned int size)
	{
		if(size < STACK_MIN_SIZE)	return;

#ifdef _QDEBUG
		printf("\n%s:%d %s m_sp: %u | m_size: %u | size: %u\n\n", __FILE__, __LINE__, __FUNCTION__, m_sp, m_size, size);
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
		printf("\n%s:%d %s m_sp: %u | m_size: %u \n\n", __FILE__, __LINE__, __FUNCTION__, m_sp, m_size);
#endif
	}

private:
	T* m_array;

	unsigned int m_size;
	unsigned int m_sp;

};
