#ifndef LISTNODE_H_
#define LISTNODE_H_

#include <iostream>

using namespace std;

template <typename T>
class ListNode {
	public:
		T data;
		ListNode *next;
		ListNode *prev;

		ListNode() {}

		ListNode(T d) {
			data = d;
			next = NULL;
			prev = NULL;
		}

		~ListNode() {
			if(next != NULL) {
				delete next;
			}
			prev = NULL;
			next = NULL;
		}				
};

template<typename T>
class DLinkedList {
public:

	DLinkedList();
	~DLinkedList();

	ListNode<T> *front;
	ListNode<T> *back;

	int size;

	bool isEmpty();
	void print();
	int getSize();
	void insertFront(T d);
	void insertBack(T d);
	T getFront();
	T removeFront();
	T removeBack();
	T remove(T d); //remove data item d, delete its node
	int find(T d); //return position of d
	T deleteAt(int pos); //return data at position pos, delete its node

};

template<typename T>
DLinkedList<T>::DLinkedList() {
	size = 0;
	front = NULL;
	back = NULL;
}

template<typename T>
DLinkedList<T>::~DLinkedList() {
	ListNode<T> *curr = front;
	while (size != 0) {
		front = front->next;
		delete curr;
		size--;
	}
}

template<typename T>
bool DLinkedList<T>::isEmpty() {
	return(size==0);
}

template<typename T>
int DLinkedList<T>::getSize() {
	return size;
}

template<typename T>
void DLinkedList<T>::print() {
	ListNode<T> *current = front;
	while(current != NULL) {
		cout << current->data << " ";
		current = current->next;
	}
}

template<typename T>
T DLinkedList<T>::getFront() {
	return front->data;
}

template<typename T>
void DLinkedList<T>::insertFront(T d) {
	ListNode<T> *node = new ListNode<T>(d);
	if(isEmpty()) {
		front = node;
		back = node;
	}
	else {
		node->next = front;
		front->prev = node;
		front = node;
	}
	size++;
}

template<typename T>
void DLinkedList<T>::insertBack(T d) {
	ListNode<T> *node = new ListNode<T>(d);
	if(size == 0) {
		front = node;
		back = node;
	}
	else {
		node->prev = back;
		back->next = node;
		back = node;
	}
	size++;
}

template<typename T>
T DLinkedList<T>::removeFront() {
	if(isEmpty()) {
		return NULL;
	}
	ListNode<T> *node = front;
	T temp = front->data;
	if(front->next != NULL) {
		front->next->prev = NULL;
		front = front->next;
	}
	node->next = NULL;
	delete node;
	size--;
	return temp;
}

template<typename T>
T DLinkedList<T>::removeBack() {
	if(isEmpty()) {
		return NULL;
	}
	ListNode<T> *node = back;
	T temp = back->data;
	back->prev->next = NULL;
	back = back->prev;
	node->prev = NULL;
	delete node;
	size--;
	return temp;
}

template<typename T>
T DLinkedList<T>::remove(T d) {
	if(isEmpty()) {
		return NULL;
	}
	ListNode<T> *current = front;
	while(current->data != d) {
		current = current->next;
		if(current == NULL) {
			return NULL;
		}
	}
	if(current == front) {
		front = current->next;
	}
	else {
		current->prev->next = current->next;
	}
	if(current == back) {
		back = current->prev;
	}
	else {
		current->next->prev = current->prev;
	}
	current->next = NULL;
	current->prev = NULL;
	T temp = current->data;
	size--;
	delete current;
	return(temp);
}

template<typename T>
T DLinkedList<T>::deleteAt(int pos) {
	ListNode<T> *current = front;

	int index = 0;

	while(index != pos) {
		current = current->next;
		if(current == NULL) {
			return NULL;
		}
		++index;
	}

	if(current == front) {
		front = current->next;
	}
	else {
		current->prev->next = current->next;
	}
	if(current == back) {
		back = current->prev;
	}
	else {
		current->next->prev = current->prev;
	}

	current->next = NULL;
	current->prev = NULL;
	T d = current->data;
	delete current;
	size--;
	return d;
}

template<typename T>
int DLinkedList<T>::find(T d) {
	int index = -1;
	ListNode<T> *current = front;

	while(current != NULL) {
		if (current->data == d) {
			return (++index);
		}

		current = current->next;
		++index;
	}
	return index;
}

#endif /* LISTNODE_H_ */
