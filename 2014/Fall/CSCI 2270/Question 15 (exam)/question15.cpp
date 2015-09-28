#include "bintree.h"
#include "binary_search_tree.h"
#include <iostream>

using namespace std;

// helper function to avoid duplicates
bool contains(const binary_tree_node* root_ptr, int target)
{
	if (root_ptr == nullptr) return false;
	if (root_ptr->data == target) return true;
	return contains(root_ptr->left, target) || contains(root_ptr->right, target);
}

// build a mirrored version of the input tree
binary_tree_node* mirror_tree(const binary_tree_node* root_ptr)
{
	if (root_ptr == NULL)//if it is empty, return null
	return NULL;
	else {
		binary_tree_node* new_root_ptr = new binary_tree_node;//creatign a new node
		new_root_ptr -> data = root_ptr->data; //transfering all the root_ptr data to the new node
		new_root_ptr -> right = mirror_tree(root_ptr -> left); // mirror the root pointer and set it to the right (mirroring it)
		new_root_ptr -> left= mirror_tree(root_ptr -> right);//mirror the right root pointer to the new one as the left one. 
		
		return new_root_ptr; // returning the new mirrored binary tree.
		/*binary_tree_node *temp = nullptr;
		temp -> data = root_ptr -> data;
		temp -> left = mirror_tree(root_ptr -> right);
		temp -> right = mirror_tree(temp);
		
		return temp;
		*/
	}
}

int main()
{
	// make a random binary_tree
	binary_tree_node* root_ptr1 = nullptr;
	/*for (unsigned int k = 0; k < 10; ++k)
	{
		int num = rand() % 20;
		if (!contains(root_ptr1, num))
			insert(root_ptr1, num);
	}
	*/
	insert(root_ptr1, 50);
	insert(root_ptr1, 20);
	insert(root_ptr1, 30);
	insert(root_ptr1, 35);
	insert(root_ptr1, 40);
	insert(root_ptr1, 45);
	insert(root_ptr1, 70);
	insert(root_ptr1, 75);
	insert(root_ptr1, 80);
	
	
	cout << "Binary search tree " << endl;
	print(root_ptr1, 0);
	
	binary_tree_node* root_ptr2 = mirror_tree(root_ptr1);

	cout << "Binary search tree mirrored" << endl;
	print(root_ptr2, 0);
	
	tree_clear(root_ptr1);
	tree_clear(root_ptr2);
}
