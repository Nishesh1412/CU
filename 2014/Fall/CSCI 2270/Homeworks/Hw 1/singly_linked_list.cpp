#include "singly_linked_list.h"

using namespace std;

void add_node(node*& head_ptr, const int& payload)
{
	node* nnode = new node;
	if (head_ptr == NULL) {
			nnode -> data = payload;
			nnode -> next = nullptr;
			head_ptr = nnode;
			return;
	}
	else if (payload < head_ptr->data){
		nnode -> data = payload;
		nnode -> next = head_ptr;
		head_ptr = nnode;
		return;
	}
	else {
		node* curr_ptr = new node;
		curr_ptr -> next = head_ptr -> next;
		while (curr_ptr!= nullptr){
			if (curr_ptr -> data <= payload){
				curr_ptr -> next = payload;
			}
		}

		//while (curr_ptr != nullptr){ //this runs it until the end!!
			//if (curr_ptr -> data < payload && curr_ptr -> next -> data > payload){
				//nnode -> data = payload;
				//nnode -> next = curr_ptr -> next;
				//curr_ptr -> next = nnode;
				//return;
				//here i need to figure out how to break it to the correct position!!
			//}
			//else
			//{
				//curr_ptr = curr_ptr -> next;
				//return;
			//}
	}
}
bool remove_node(node*& head_ptr, const int& target)
{
	if (head_ptr -> data == target){
		node* destructo = head_ptr;
		head_ptr = head_ptr -> next;
		delete destructo;
		return true;
	}
	node* curr_ptr = new node;
	curr_ptr -> next = head_ptr;
	while (curr_ptr != nullptr){
		if (curr_ptr -> next -> data == target){
			node* destructo = curr_ptr -> next;
			curr_ptr -> next = curr_ptr -> next -> next;
			delete destructo;
			return true;
		}
		else
		curr_ptr = curr_ptr -> next;
		}
	return false;
	}
}

bool find_list(const node*& head_ptr, const int& target)
{
	node* drek_ptr = new node;
	drek_ptr -> next = head_ptr;
	while (drek_ptr !=nullptr)
	{
		if (drek_ptr-> data == target){
		return true;
		}
		else
		{
			drek_ptr = drek_ptr -> next;
		}
	}
	return false;
}

void clear_list(node*& head_ptr)
{
	if (head_ptr == nullptr) return;
	clear_list(head_ptr->next);
	delete head_ptr;
	head_ptr = nullptr;
	return;
}

void print_list(const node*& head_ptr)
{
	const node* cursor = head_ptr;
	while (cursor != nullptr)
	{
		cout << cursor->data << " ";
		cursor = cursor->next;
	}
	cout << endl;
}

void copy_list(const node*& source_ptr, node*& dest_ptr)
{

}

