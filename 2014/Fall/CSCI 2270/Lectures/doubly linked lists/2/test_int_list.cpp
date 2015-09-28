#include "doubly_linked_list.h"

using namespace std;

bool check_list(const node* head_ptr)
{
	for (const node* cursor = head_ptr; 
		cursor != nullptr && cursor->next != nullptr;
		cursor = cursor->next)
		if (cursor->data > cursor->next->data) return false;
	return true;
}

int main()
{
	node* head_ptr1 = nullptr;      // This will be the list 1 head
	const node* const_head_ptr1;	
	const node* const_tail_ptr1;	
	const node* const_tail_ptr2;	
	node* tail_ptr1 = nullptr;
	 
	for (unsigned int k = 0; k < 10; ++k)
	{
		add_node(head_ptr1, tail_ptr1, k);	// add a number to the list
		const_head_ptr1 = head_ptr1;
		print_list(const_head_ptr1);
		if (!check_list(const_head_ptr1))
			cout << "List is out of order!" << endl;
	}

	node* head_ptr2 = nullptr;
	node* tail_ptr2 = nullptr;
	const_head_ptr1 = head_ptr1;
	copy_list(const_head_ptr1, head_ptr2, tail_ptr2);	// copy the list
	
	for (unsigned int k = 0; k < 10; ++k)
	{
		remove_node(head_ptr1, tail_ptr1, k);	// remove things
		const_head_ptr1 = head_ptr1;
		const_tail_ptr1 = tail_ptr1;
		print_list(const_head_ptr1);
		print_list_backwards(const_tail_ptr1);
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
