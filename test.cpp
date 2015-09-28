/*
 * test.cpp
 *
 *  Created on: 15 wrz 2015
 *      Author: qbit
 */

#include <time.h>
#include <stdlib.h>

#include "DA/StackArray.h"
#include "DA/QueueArray.h"

void testStack()
{
	StackArray<int>	array;

	for(unsigned int i = 0; i < 128; ++i)
	{
		array.push(i);
	}


	int val;
	for(unsigned int i = 0; i < 128; ++i)
	{
		if(array.pop(val))	printf("%d ", val);
	}
	printf("\n");

	for(unsigned int i = 0; i < 10; ++i)
	{
		if(array.pop(val))	printf("val: %d \n", val);
		else 	printf("empty\n");
	}
}

void testQueue()
{
	QueueArray<int>	queue;

	for(unsigned int i = 0; i < 128; ++i)
	{
		queue.enqueue(i);
	}

	int val;
	for(unsigned int i = 0; i < 128; ++i)
	{
		if(queue.dequeue(val))	printf("%d ", val);
	}

	printf("\n");

	for(unsigned int i = 0; i < 10; ++i)
	{
		if(queue.dequeue(val))	printf("%d ", val);
		else	printf("empty\n");
	}

	for(unsigned int i = 0; i < 20; ++i)
	{
		queue.enqueue(i);
	}
}

void testRandomStack()
{
	StackArray<int> stack;
	int tmp, r;
	for(unsigned int i = 0; i < 10000; ++i)
	{
		r = rand();
		if(r % 2)
		{
			stack.push(i);
		}
		else
		{
			stack.pop(tmp);
		}
	}
}

void testRandomQueue()
{
	QueueArray<int> queue;
	int tmp, r;
	for(unsigned int i = 0; i < 10000; ++i)
	{
		r = rand();
		if(r % 2)
		{
			queue.enqueue(i);
		}
		else
		{
			queue.dequeue(tmp);
		}
	}
}

int main()
{
	srand(time(NULL));
	testStack();
	testQueue();

	testRandomStack();
	testRandomQueue();

	return 0;
}
