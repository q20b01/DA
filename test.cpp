/*
 * test.cpp
 *
 *  Created on: 15 wrz 2015
 *      Author: qbit
 */

#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include "DA/StackArray.h"
#include "DA/QueueArray.h"
#include "DA/BinaryHeap.h"
#include "Sort/Sort.h"

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

void sortTest()
{
	int size = 20;
	int* tab = (int*)malloc(size * sizeof(int));

	for(unsigned int i = 0; i < size; ++i)	tab[i] = rand() % 100;

	for(unsigned int i = 0; i < size; ++i)	printf("%d ", tab[i]);

	printf("\n");

	mergeSort(tab, 0, size);

	printf("result \n");
	for(unsigned int i = 0; i < size; ++i)
	{
		printf("%d ", tab[i]);
	}

	printf("\n");

	free(tab);
}

int comp(const void* a, const void* b)
{
	if(*(int*)a > *(int*)b)	return 1;
	if(*(int*)a == *(int*)b)	return 0;
	return -1;
}

void partition()
{
	int size = 1000;
	int num = 3;
	int* tab1 = (int*) malloc(size * sizeof(int));
	int* tab2 = (int*) malloc(size * sizeof(int));
	int* tab3 = (int*) malloc(size * sizeof(int));
	for(unsigned int i = 0; i < size; ++i){
		int r = rand() % 100;
		tab1[i] = r;
		tab2[i] = r;
		tab3[i] = r;
	}

//	for(unsigned int i = 0; i < size; ++i)	printf("%d ", tab[i]);
//	printf("\n");

//	partition(tab, size, num);
	quickSort(tab1, size);
	mergeSort(tab3, 0, size);

	qsort(tab2, size, sizeof(int), comp);

	for(unsigned int i = 0; i < size; ++i)
	{
		if(tab1[i] != tab2[i] || tab2[i] != tab3[i]){
			printf("ERRRRROR\n");
			break;
		}
	}

//	for(unsigned int i = 0; i < size; ++i)	printf("%d ", tab[i]);
//	printf("\n");
	printf("koniec\n");
	free(tab1);
	free(tab2);
	free(tab3);
}

void testBinaryHeap()
{
	BinaryHeap<int>	bh;

	for(unsigned int i = 0; i < 50; ++i)
	{
		int r = rand() % 100;
		printf("insert: %d \n", r);
		bh.insert(r);

#ifdef _QDEBUG
		bh.debugPrint();
#endif
	}

	int p = 100;
	while(!bh.isEmpty())
	{
		int r;
		bh.delMax(r);
		if(p < r)
		{
			printf("ERRRRRRRRRRRRRRRORRR");
			exit(1);
		}

		printf("max: %d \n", r);
		p = r;
	}
}

int main()
{
	srand(time(NULL));
//	testStack();
//	testQueue();

//	testRandomStack();
//	testRandomQueue();

//	sortTest();

//	partition();

	testBinaryHeap();

	return 0;
}
