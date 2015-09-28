#include "array_stack.h"

using namespace std;


int main()
{
	array_stack arr_stk;
	int num;
	
	init(arr_stk);
	
	for (unsigned int i = 0; i < 10; ++i)
	{
		cout << "Enter a number to push: ";
		cin >> num;
		push(arr_stk, num);
		print(arr_stk);
	}
	
	for (unsigned int i = 0; i < 10; ++i)
	{
		pop(arr_stk);
		print(arr_stk);
	}
	
	destr(arr_stk);
}

