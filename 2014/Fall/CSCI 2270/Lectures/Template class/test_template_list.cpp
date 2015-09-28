#include "doubly_linked_list.h"

using namespace std;

int main()
{
	string name;
	node<string>* head_ptr1 = nullptr;      // This will be the list 1 head
	const node<string>* const_head_ptr1;	
	const node<string>* const_tail_ptr1;	
	const node<string>* const_tail_ptr2;	
	node<string>* tail_ptr1 = nullptr;
	node<double>* bobos_big_list = nullptr;
	node<double>* bobos_big_butt = nullptr;
	for (unsigned int k = 0; k < 10; ++k)
		add_node(bobos_big_list, bobos_big_butt, k * 0.7);
	print_list(bobos_big_list);
	 
	for (unsigned int k = 0; k < 10; ++k)
	{
		cout << "Enter a person to add: ";
		getline(cin, name);
		add_node(head_ptr1, tail_ptr1, name);	// add a nameber to the list
		const_head_ptr1 = head_ptr1;
		print_list(const_head_ptr1);
		if (!check_list(const_head_ptr1))
			cout << "List is out of order!" << endl;
	}

	node<string>* head_ptr2 = nullptr;
	node<string>* tail_ptr2 = nullptr;
	const_head_ptr1 = head_ptr1;
	copy_list(const_head_ptr1, head_ptr2, tail_ptr2);	// copy the list
	
	for (unsigned int k = 0; k < 3; ++k)
	{
		cout << "Enter a person to find: ";
		getline(cin, name);
		const_head_ptr1 = head_ptr1;
		if (find_list(const_head_ptr1, name))	// find things
			cout << "found " << name << endl;
		else
			cout << "did not find " << name << endl;
	}
	
	for (unsigned int k = 0; k < 10; ++k)
	{
		cout << "Enter a person to remove: ";
		getline(cin, name);
		remove_node(head_ptr1, tail_ptr1, name);	// remove things
		const_head_ptr1 = head_ptr1;
		
		print_list(const_head_ptr1);
		if (!check_list(const_head_ptr1))
			cout << "List is out of order!" << endl;
	}
	
	const_tail_ptr2 = tail_ptr2;
	print_list_backwards(const_tail_ptr2);
	cout << "Clearing" << endl;
	clear_list(head_ptr2, tail_ptr2);				// destroy list 2
	const_tail_ptr1 = tail_ptr1;
	print_list_backwards(const_tail_ptr1);
	cout << "Clearing" << endl;
	clear_list(head_ptr1, tail_ptr1);				// destroy list 1
	
}
