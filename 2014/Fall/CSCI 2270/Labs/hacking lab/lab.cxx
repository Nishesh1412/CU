#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cstdlib>


using namespace std;


void PrintOverrunStack(void* varAddress)
{
	printf("Stack around Overrun() function\n");

	void** slot = (void**)varAddress;
	for (int i = 0; i < 14; i++)
	{
		// Pretty print stack slots:
		//   stack address: slot value (hex) 'slot value (ansi)'"
		char* ch = (char*)slot;
		printf("0x%.8X: 0x%.8X '%c%c%c%c'\n", (unsigned int)slot, 
			(unsigned int)(*slot), ch[0], ch[1], ch[2], ch[3]);
		++slot;
	}

	printf("\n");
}


void Overrun(char* text, char* command)
{
	// Local variables.
	char var0[4] = "ABC";
	char var1[4] = "DEF";
	
	// Make compiler happy and avoid warning, as 'var0' is not used 
	// elsewhere in this function but exists for demo purposes only.
	var1[3] = var0[3];

	// Print what's on the stack for this function.
	PrintOverrunStack(&var1);
	
	// This is what this exercise is all about! What could be the 
	// problem here?
	strcpy(var1, text);

	// Reexamine what this function's stack looks like now.
	PrintOverrunStack(&var1);
}


// Note that this function is not called from within this .cxx file!
void NotCalledExplicitly(char* command)
{
	// If you see this, you have successfuly completed this exercise.
	cout << "SUCCESS!!!" << endl;
	// Print command to be excuted.
	cout << "Executing '" << command << "':" << endl;
	// Execute command.
	system(command);
	// Quit this program.
	exit(0);
}


void CauseOverrun(int argc, char *argv[])
{
	// Get # of provided 'slots'.
	const int count = argc - 2;
	
	// Assemble binary data from hexadecimal values.
	char text[256] = {0};
	for (int n = 0; n < count; n++)
	{
		// Turn each clear text hexadecimal 'slot' into its binary 
		// format and put it at the right offset within the 'string'.
		char* pm = argv[2 + n];
		if ((strlen(pm) >= 2) && ('0' == pm[0]) && ('x' == pm[1]))
		{
			sscanf(pm, "0x%x", (unsigned int*)&text[n * 4]);
		}
		else
		{
			sscanf(pm, "%x", (unsigned int*)&text[n * 4]);
		}
	}

	// Call test function that can cause an overrun. Pass in both the
	// text string (built from the passed in parameters) along with the
	// command to execute if the buffer overrun is done correctly.
	char* command = argv[1];
	Overrun(text, command);
}


// You can call 'lab' without any parameters to see the program's stack
// or you can call 'lab' with parameters to potentially cause a buffer 
// overrun:
//   lab [command-to-run [1st-value [2nd-value [3rd-value [...]]]]]
// Since it is difficult to enter binary data via the keyboard, we chose
// to represent the data as a sequence of hexadecimal values, each re-
// presenting 4 bytes or the size of a pointer (or address) if run as a
// 32 bit application. This will come in handy as each parameter value
// you add will occupy/overwrite 1 slot on the stack.
// Example (Examine what's on the stack):
//   lab
// Example (Try executing the 'ls' command. (Example does not work!)):
//   lab ls 0x6863694d 0x006c6561
int main(int argc, char *argv[])
{
	// Are 'slot' replacements provided?
	if (argc > 2)
	{
		CauseOverrun(argc, argv);
	}
	else
	{
		// Print vital information needed to complete this exercise 
		// successfully. You will need to know how many slots to
		// overwrite on the stack and what values they should take on.
		// The output of the code below will give you that information.

		// Print the NotCalledExplicitly() function's entry point.
		cout << "NotCalledExplicitly() resides at address: " <<
			(void*)&NotCalledExplicitly << endl << endl;

		// General stack layout.
		cout << "Stack layout:" << endl;
		cout << "  Variables ..." << endl;
		cout << "  Caller's frame pointer" << endl;
		cout << "  Function return address" << endl;
		cout << "  Parameters ..." << endl << endl;

		// Call Overrun() with dummy values.
		char text[4] = "txt";
		char command[4] = "cmd";

		Overrun(text, command);
	}

	return 0;
}
