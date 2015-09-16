/*
 * test.cpp
 *
 *  Created on: 15 wrz 2015
 *      Author: qbit
 */

#include "StackArray.h"

int main()
{
	StackArray<int>	array;


	for(unsigned int i = 0; i < 128; ++i)
	{
		array.push(i);
	}


	int val;
	for(unsigned int i = 0; i < 128; ++i)
	{
		if(array.pop(val))	printf("val: %d \n", val);
	}

	for(unsigned int i = 0; i < 50; ++i)
	{
		if(array.pop(val))	printf("val: %d \n", val);
		else printf("empty\n");
	}

	return 0;
}
