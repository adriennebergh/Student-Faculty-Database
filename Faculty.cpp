#include "Faculty.h"
#include <iostream>
#include <string>

using namespace std;

Faculty::Faculty() {
	name = "";
	ID = 0;
	level = "";
	department = "";
}

Faculty::Faculty(string n, int i, string l, string d, DLinkedList<int>* a) {
	name = n;
	ID = i;
	level = l;
	department = d;
	adviseeList = a;
}

Faculty::~Faculty() {
	
}

string Faculty::getName() {
	return name;
}

int Faculty::getID() {
	return ID;
}

string Faculty::getLevel() {
	return level;
}

string Faculty::getDepartment() {
	return department;
}

DLinkedList<int>* Faculty::getAdviseeList() {
	return adviseeList;
}

int Faculty::getAdviseeListSize() {
	return adviseeList->getSize();
}

void Faculty::setName(string n) {
	name = n;
}

void Faculty::setID(int id) {
	ID = id;
}

void Faculty::setLevel(string l) {
	level = l;
}

void Faculty::setDepartment(string d) {
	department = d;
}

void Faculty::addToAdviseeList(int id) {
	adviseeList->insertFront(id);
}

void Faculty::deleteFromAdviseeList(int id) {
	if(adviseeList->getSize()!=0){
		adviseeList->remove(id);
	}
}

int Faculty::deleteFromAdviseeList() {
	if(adviseeList->getSize()==0) {
		return 0;
	}
	else {
		return adviseeList->removeBack();
	}
}

//Operator Overloaders:
bool Faculty::operator <(const Faculty& fac) {
	if(ID > fac.ID) {
		return true;
	}
	return false;
}

bool Faculty::operator >(const Faculty& fac) {
	if(ID < fac.ID) {
		return true;
	}
	return false;
}

bool Faculty::operator ==(const Faculty& fac) {
	if(ID == fac.ID) {
		return true;
	}
	return false;
}

bool Faculty::operator !=(const Faculty& fac) {
	if(ID != fac.ID) {
		return true;
	}
	return false;
}

ostream& operator<<(ostream& os, Faculty obj) {
	cout << "Faculty Name: " << obj.getName() << "\n" << "Faculty ID: " << obj.getID() << "\n" << "Faculty Level: " << obj.getLevel() << "\n" << "Faculty Department: " << obj.getDepartment() << "\nFaculty Advisee ID List: ";
	obj.getAdviseeList()->print();
	return os;
}
