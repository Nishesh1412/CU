//#include "doubly_linked_list.h"

#include <iostream>


template <class ItemType>
void add_node(node<ItemType>*& head_ptr, node<ItemType>*& tail_ptr, 
const ItemType& payload)
{
	node<ItemType>* added_node = new node<ItemType>();
	added_node->data = payload;
	// adding to an empty list
	if (head_ptr == nullptr)
	{
		head_ptr = added_node;
		added_node->next = nullptr;
		added_node->prev = nullptr;
		tail_ptr = head_ptr;
	}
	else
	{
		// adding a new head node
		if (head_ptr->data > payload)
		{
			added_node->next = head_ptr;
			added_node->prev = nullptr;
			head_ptr->prev = added_node; // missed this line
			head_ptr = added_node;
		}
		else
		{
			// adding a node after the head node
			node<ItemType>* cursor = head_ptr;
			while (cursor != nullptr && cursor->next != nullptr 
				&& cursor->next->data < payload)
				cursor = cursor->next;
			// adding to the end of the list
			if (cursor->next == nullptr)
			{	
				tail_ptr = added_node;
				cursor->next = added_node; 
				added_node->next = nullptr;
				added_node->prev = cursor;
			}	
			// adding before the end of the list
			else
			{
				added_node->next = cursor->next;
				added_node->prev = cursor;
				cursor->next->prev = cursor; // missed this line
				cursor->next = added_node;
			}
		}
	}		
}

template <class ItemType>
bool remove_node(node<ItemType>*& head_ptr, node<ItemType>*& tail_ptr, const ItemType& target)
{
	if (head_ptr == nullptr) return false;
	
	node<ItemType>* removed_node_ptr = head_ptr;	
	// check if we are removing the head node
	if (removed_node_ptr->data == target)
	{
		if (head_ptr->next == nullptr)
			tail_ptr = nullptr;
		head_ptr = head_ptr->next;
		
		if (head_ptr != nullptr)
			head_ptr->prev = nullptr;
		
		delete removed_node_ptr;
		removed_node_ptr = nullptr;
		return true;
	}
	
	// look for the node to remove after the head node
	while (removed_node_ptr != nullptr && 
		removed_node_ptr->next != nullptr &&
		removed_node_ptr->next->data != target)
		removed_node_ptr = removed_node_ptr->next;
		
	// stop here before the node to remove
	if (removed_node_ptr != nullptr &&
		removed_node_ptr->next != nullptr)
	{
		node<ItemType>* next_node_ptr = removed_node_ptr->next->next; 
		delete removed_node_ptr->next;
		removed_node_ptr->next = next_node_ptr;
		// removing a node other than the tail
		if (next_node_ptr != nullptr)
			next_node_ptr->prev = removed_node_ptr;
		// removing the tail node
		else
			tail_ptr = removed_node_ptr;
		return true;
	}
	else
		return false;	
}

template <class ItemType>
bool find_list(const node<ItemType>* head_ptr, const ItemType& target)
{
	const node<ItemType>* cursor = head_ptr;
	while (cursor != nullptr)
	{
		if (cursor->data == target)
			return true;
		cursor = cursor->next;
	}
	return false;
}

template <class ItemType>
void clear_list(node<ItemType>*& head_ptr, node<ItemType>*& tail_ptr)
{
	node<ItemType>* destroyed_node_ptr;
	while (head_ptr != nullptr)
	{
		destroyed_node_ptr = head_ptr;
		head_ptr = head_ptr->next;
		delete destroyed_node_ptr;
	}
	tail_ptr = nullptr;

}

template <class ItemType>
void print_list(const node<ItemType>* head_ptr)
{
	const node<ItemType>* cursor = head_ptr;
	while (cursor != nullptr)
	{
		std::cout << cursor->data << " ";
		cursor = cursor->next;
	}
	std::cout << std::endl;
}

template <class ItemType>
void print_list_backwards(const node<ItemType>* tail_ptr)
{
	const node<ItemType>* cursor = tail_ptr;
	while (cursor != nullptr)
	{
		std::cout << cursor->data << " ";
		cursor = cursor->prev;
	}
	std::cout << std::endl;
}

template <class ItemType>
void copy_list(const node<ItemType>* source_head_ptr,
	node<ItemType>*& dest_head_ptr, node<ItemType>*& dest_tail_ptr)
{
	clear_list(dest_head_ptr, dest_tail_ptr);
	if (source_head_ptr == nullptr)
		return;
	dest_head_ptr = new node<ItemType>();
	dest_head_ptr->data = source_head_ptr->data;
	dest_head_ptr->next = nullptr;
	// define the prev pointer for the destination's head
	dest_head_ptr->prev = nullptr;
	node<ItemType>* cursor = dest_head_ptr;
	dest_tail_ptr = dest_head_ptr;
	while (source_head_ptr->next != nullptr)
	{
		source_head_ptr = source_head_ptr->next;
		cursor->next = new node<ItemType>();
		cursor->next->data = source_head_ptr->data;
		cursor->next->next = nullptr;
		// set the previous pointer for the node we just made
		cursor->next->prev = cursor;
		cursor = cursor->next;
		dest_tail_ptr = cursor;
	}
}

template <class ItemType>
bool check_list(const node<ItemType>* head_ptr)
{
	for (const node<ItemType>* cursor = head_ptr; 
		cursor != nullptr && cursor->next != nullptr;
		cursor = cursor->next)
		if (cursor->data > cursor->next->data) return false;
	return true;
}


