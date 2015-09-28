
#include <stdio.h>

int fib (int n)
{
  if (n <= 1) {
	  return 1;
  } else {
    int x = fib(n-1);
    int y = fib(n-2);
    return x + y;
  }
}

int main()
{
	int i, result;
	puts("Enter a positive number: ");
	scanf("%d", &i);
	
	result = fib(i);
	
	printf("\nElement %d of the Fibbionacci Sequence is %d.\n", i, result);
	
	return 0;
}
