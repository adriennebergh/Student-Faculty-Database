#ifndef BINARYTREE_H_
#define BINARYTREE_H_
#include <iostream>
#include "queue.h"
#include <fstream>

using namespace std;

//TreeNode
template<typename T>
class TreeNode {
public:
	T data;
	TreeNode<T> *left = NULL;
	TreeNode<T> *right = NULL;

	TreeNode() {}

	TreeNode(T d) {
		data = d;
		left = NULL;
		right = NULL;
	}

	~TreeNode() {
		delete left;
		delete right;
	}
};

template<typename T>
class BinarySearchTree {
public:
	TreeNode<T> *root;

	BinarySearchTree() {
		root = NULL;
		size = 0;
	}

	~BinarySearchTree() {
		delete root; 
	}

	int size;
	int getSize();
	bool isEmpty();
	bool contains(T d);
	T search(T d);
	void add(T d);
	void addHelper(T d, TreeNode<T>*& n);
	bool remove(T d);
	TreeNode<T>* getSuccessor(TreeNode<T>* d);
	T getMin();
	T getMax();
	void print();
	void printHelper(TreeNode<T> *node);
	GenQueue<TreeNode<T>*>* bfs(); //breadth-first search

};

template <typename T>
int BinarySearchTree<T>::getSize() {
	return size;
}

template <typename T>
bool BinarySearchTree<T>::isEmpty() {
	return (size==0);
}

template <typename T>
bool BinarySearchTree<T>::contains(T d) {
	bool containsD = false;
	TreeNode<T> *current = root;
	while(current != NULL) {
		if (d > current->data) {
			current = current->right;
		}
		else if(d < current->data) {
			current = current->left;
		}
		else {
			containsD = true;
			break;
		}
	}
	return containsD;
}

template <typename T>
T BinarySearchTree<T>::search(T d) {
	T item;
	TreeNode<T> *current = root;
	while(current != NULL) {
		if (d > current->data) {
			current = current->right;
		}
		else if(d < current->data) {
			current = current->left;
		}
		else {
			item = current->data;
			break;
		}
	}
	return item;
}

template <typename T>
void BinarySearchTree<T>::print() {
	if(root != NULL)
		printHelper(root);
}

template <typename T>
void BinarySearchTree<T>::printHelper(TreeNode<T>* node) {
	//cout << node->data << endl;
	if(node->left != NULL)
	{
		printHelper(node->left);
	}
	if(node != NULL) {
		cout << node->data << endl;
	}
	if(node->right != NULL) {
		printHelper(node->right);
	}
}

template <typename T>
T BinarySearchTree<T>::getMin() {
	TreeNode<T> *current = root;
	while(current->left != NULL) {
		current = current->left;
	}
	return current->data;
}

template <typename T>
T BinarySearchTree<T>::getMax() {
	TreeNode<T> *current = root;
	while(current->right != NULL) {
		current	= current->right;
	}
	return current->data;
}

template<typename T>
void BinarySearchTree<T>::add(T d) {
	size++;
	addHelper(d, root);
}

template <typename T>
void BinarySearchTree<T>::addHelper(T d, TreeNode<T>*& n) {
	if(n == NULL) {
		n = new TreeNode<T>(d);
	}
	else if(d > n->data) {
		addHelper(d, n->right);
	}
	else {
		addHelper(d, n->left);
	}
}

template <typename T>
bool BinarySearchTree<T>::remove(T d){
	if (root == NULL) 
		return false;
                            
	TreeNode<T> *current = root;
	TreeNode<T> *parent = root;
	bool isLeft = true;

	while(current->data != d) {    
		parent = current;
		if(d < current->data) {
			isLeft = true;
			current = current->left;
		}
		else {
			isLeft = false;
			current = current->right;
		}
		if(current == NULL)           
			return false;                
	}  

    //no children
	if(current->left==NULL && current->right==NULL) {
		if(current == root)
			root = NULL;                 
		else if(isLeft)
			parent->left = NULL;
		else                            
			parent->right = NULL;
	}
     
    //one child
    // no right child, replace with left subtree
	else if(current->right==NULL) {
		if(current == root) 
			root = current->left;
		else if(isLeft)
			parent->left = current->left;
		else
			parent->right = current->left;
	}
    // no left child, replace with right subtree
	else if(current->left==NULL){
		if(current == root)
			root = current->right;
		else if(isLeft)
			parent->left = current->right;
		else
			parent->right = current->right;
	}
	else {
		TreeNode<T>* successor = getSuccessor(current);

        // connect parent of current to successor
		if(current == root)
			root = successor;
		else if(isLeft)
			parent->left = successor;
		else
			parent->right = successor;

        // connect successor to current's left child
		successor->left = current->left;
	}
	size--;
	return true;  
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::getSuccessor(TreeNode<T>* d) {
	TreeNode<T>* successorParent = d;
	TreeNode<T>* successor = d;
	TreeNode<T>* current = d->right;
	while(current != NULL) {                             
		successorParent = successor;
		successor = current;
		current = current->left;
	}
	
	if(successor != d->right) {
		successorParent->left = successor->right;
		successor->right = d->right;
	}
	return successor;
}

//breadth-first search returns a queue of nodes within BST in hierarchical order
template <typename T>
GenQueue<TreeNode<T>*>* BinarySearchTree<T>::bfs() {

	GenQueue<TreeNode<T>*> *temp = new GenQueue<TreeNode<T>*>();
	GenQueue<TreeNode<T>*> *q = new GenQueue<TreeNode<T>*>();
	TreeNode<T>* current = root;

	temp->insert(current);

	while(!temp->isEmpty()) {
		current = temp->remove();
		//cout << "current data to add to q: " << current->data << endl;
		q->insert(current);

		if(current->left != NULL) {
			temp->insert(current->left);
		}
		if(current->right != NULL) {
			temp->insert(current->right);
		}
	}
	return q;
}

#endif /* BINARYTREE_H_ */
