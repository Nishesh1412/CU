#include <stdio.h>
#include <sys/syscall.h>

int main (int argc, char* argv[])

{
	syscall(318);
	return 0;
}
