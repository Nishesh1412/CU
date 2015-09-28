#include <ctime>
#include "array_stack.h"

using namespace std;


int main()
{
	array_stack arr_stk;
	init(arr_stk);
	srand(time(nullptr));


	for (unsigned int i = 0; i < 50; ++i)
	{
		push(arr_stk, rand() % 100 + 1);
		print(arr_stk);
	}
	while (empty(arr_stk) == false)
	{
		pop(arr_stk);
		print(arr_stk);
	}
	for (unsigned int i = 0; i < 50; ++i)
	{
		if (rand() % 2)
			pop(arr_stk);
		if (rand() % 3)
			push(arr_stk, rand() % 100 + 1);
		print(arr_stk);
	}		
	print(arr_stk);	
	destr(arr_stk);
}
