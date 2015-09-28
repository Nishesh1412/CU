#include "doubly_linked_list.h"

using namespace std;

int main()
{
	int num;
	node<int>* head_ptr1 = nullptr;      // This will be the list 1 head
	const node<int>* const_head_ptr1;	
	const node<int>* const_tail_ptr1;	
	const node<int>* const_tail_ptr2;	
	node<int>* tail_ptr1 = nullptr;
	 
	for (unsigned int k = 0; k < 10; ++k)
	{
		cout << "Enter a number to add: ";
		cin >> num;
		add_node(head_ptr1, tail_ptr1, num);	// add a number to the list
		const_head_ptr1 = head_ptr1;
		print_list(const_head_ptr1);
		if (!check_list(const_head_ptr1))
			cout << "List is out of order!" << endl;
	}

	node<int>* head_ptr2 = nullptr;
	node<int>* tail_ptr2 = nullptr;
	const_head_ptr1 = head_ptr1;
	copy_list(const_head_ptr1, head_ptr2, tail_ptr2);	// copy the list
	
	for (unsigned int k = 0; k < 10; ++k)
	{
		cout << "Enter a number to find: ";
		cin >> num;
		const_head_ptr1 = head_ptr1;
		if (find_list(const_head_ptr1, num))	// find things
			cout << "found " << num << endl;
		else
			cout << "did not find " << num << endl;
	}
	
	for (unsigned int k = 0; k < 10; ++k)
	{
		cout << "Enter a number to remove: ";
		cin >> num;
		remove_node(head_ptr1, tail_ptr1, num);	// remove things
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
