template <class ItemType>
struct node {
	ItemType data;
	node<ItemType>* next;
	node<ItemType>* prev;
};

template <class ItemType>
void add_node(node<ItemType>*& head_ptr, node<ItemType>*& tail_ptr, 
	const ItemType& payload);

template <class ItemType>
bool remove_node(node<ItemType>*& head_ptr, node<ItemType>*& tail_ptr, const ItemType& target);

template <class ItemType>
void print_list(const node<ItemType>* head_ptr);

template <class ItemType>
void print_list_backwards (const node<ItemType>* tail_ptr);

template <class ItemType>
bool find_list(const node<ItemType>* head_ptr, const ItemType& target);

template <class ItemType>
void clear_list(node<ItemType>*& head_ptr, node<ItemType>*& tail_ptr);

template <class ItemType>
void copy_list(const node<ItemType>* source_head_ptr,
	node<ItemType>*& dest_head_ptr, node<ItemType>*& dest_tail_ptr);

template <class ItemType>
bool check_list(const node<ItemType>* head_ptr);

#include "doubly_linked_list.cpp"
