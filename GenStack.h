#ifndef GENSTACK_H_
#define GENSTACK_H_
#include <iostream>
using namespace std;

template<typename T>
class GenStack {
	public:
		GenStack(int maxSize);
		~GenStack();

		void push(T d);
		T pop();
		T peak();

		bool isFull();
		bool isEmpty();

		int top;
		int max;
		int size;
		T *myArray;
};

template<typename T>
GenStack<T>::GenStack(int maxSize) {
	myArray = new T[maxSize];
	max = maxSize;
	top = -1; //when we add something, it will be at 0
	size = 0;
}

template<typename T>
GenStack<T>::~GenStack(){
	delete [] myArray;
	cout << "object destroyed" << endl;
}

template<typename T>
void GenStack<T>::push(T d) {
	if(size != max) {
		myArray[++top] = d;
	}
	else {
		for(int i=0; i<top; ++i) {
			myArray[i] = myArray[i+1];
		}
		myArray[top] = d;
	}
	size++;
}

template<typename T>
T GenStack<T>::pop(){
	if(size == 0) {
		return NULL;
	}
	return myArray[top--];
}

template<typename T>
T GenStack<T>::peak() {
	if(size == 0) {
		return NULL;
	}
	return myArray[top];
}

template<typename T>
bool GenStack<T>::isEmpty(){
	return (top == -1);
}

template<typename T>
bool GenStack<T>::isFull() {
	return (top == (max-1));
}

#endif /* GENSTACK_H_ */
