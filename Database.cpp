#include <iostream>
#include <stdlib.h>
#include <string>
#include "Database.h"
#include "Student.h"
#include "Faculty.h"
#include "BinaryTree.h"
#include "GenStack.h"
#include <fstream>
#include "listnode.h"

using namespace std;

Database::Database() {
	studentTable = new BinarySearchTree<Student>();
	studentRollStack = new GenStack<BinarySearchTree<Student>*>(5);
	facultyTable = new BinarySearchTree<Faculty>();
	facultyRollStack = new GenStack<BinarySearchTree<Faculty>*>(5);
}


Database::~Database() {
	//Destroys BST
}

void Database::PrintAllStu() {
	if (studentTable->getSize() == 0) {
		cout << "There are no students in the table." << endl;
	}
	else {
		studentTable->print();
	}
}

void Database::PrintAllFac() {
	// Runs through and prints faculty in order of ID# least to greatest
	if (facultyTable->getSize() == 0) {
		cout << "This is mayhem there are no advisors" << endl;
	}
	else {
		facultyTable->print();
	}
}

Student Database::FindStu(int stuID) {
	// Finds a student by their ID #
	if(studentTable->getSize() == 0) {
		cout << "There are no students" << endl;
	}
	else {
		Student s; 
		s.setID(stuID);
		Student S = studentTable->search(s);
		cout << S << endl; 
		return S;
	}
	
}

Faculty Database::FindFac(int facID) {
	//Finds a Faculty by their ID#
	if(facultyTable->getSize() == 0) {
		cout << "Faculty table is empty." << endl;
	}
	else {
		Faculty f;
		f.setID(facID);
		Faculty F = facultyTable->search(f);
		cout << F << endl; 
		return F;
	}
	
}

Faculty Database::FindFacByStu(int stuID) {
	if(facultyTable->getSize() == 0) {
		cout << "Faculty table is empty." << endl;
	}
	if(studentTable->getSize() == 0) {
		cout << "Student table is empty." << endl;
	}
	if(!studentTable->isEmpty() && !facultyTable->isEmpty()) {
		Student s; 
		s.setID(stuID);
		Student S = studentTable->search(s);
		return FindFac(S.getAdvisor());
	}
}

void Database::FindStusByFac(int facID) {
	if(facultyTable->getSize() == 0) {
		cout << "Faculty table is empty." << endl;
	}
	if(studentTable->getSize() == 0) {
		cout << "Student table is empty." << endl;
	}

	if(!studentTable->isEmpty() && !facultyTable->isEmpty()) {
		Faculty f;
		f.setID(facID);
		Faculty F = facultyTable->search(f);

		for (int j =0; j<F.getAdviseeListSize(); j++) {
			int i = F.deleteFromAdviseeList();
			if( i!=0){	
				FindStu(i);
			}
			else{
				cout << "there is an issue, that faculty has no advisees" << endl;
			}
			F.addToAdviseeList(i);
		}
	}
}

void Database::AddStu() {
	//creates a new student and adds them to the BST
	studentRollStack->push(studentTable);
	facultyRollStack->push(facultyTable); // rollback

	string holder, stuName, stuYear, stuMajor;
	int stuID, advID;
	double stuGPA;

	cout<< "What is the student's name? (Please type a string)" << endl;
	getline(cin,stuName);
	
	cout<< "What is the student's ID number? (Please type an int) " << endl;
	getline(cin,holder);
	stuID = atoi(holder.c_str());

	bool checkID = true;
	while(checkID) {
		Student tempS;
		tempS.setID(stuID);
		if(studentTable->contains(tempS)) {
			cout << "That ID number already exists in the system. Please choose another." << endl;
			getline(cin, holder);
			stuID = atoi(holder.c_str());
		}
		else {
			checkID = false;
		}
	}
	
	cout << "What is the student's GPA?" << endl;
	getline(cin,holder);
	stuGPA = atof(holder.c_str());

	cout << "What year is the student?" << endl;
	getline(cin,stuYear);

	cout << "What is the student's major" << endl;
	getline(cin,stuMajor);

	cout << "What is the student's advisor's ID number?" << endl;
	getline(cin,holder);
	advID = atoi(holder.c_str());
	
	//Student *s = new Student(stuName, stuID, stuGPA, stuYear, stuMajor, advID);
	Student s(stuName, stuID, stuGPA, stuYear, stuMajor, advID); // because cant be a BST of pointers anymore
	studentTable->add(s);
	//ChangeStuAdvisor(stuID, advID);
	//Rollback

	//find advisor using id#, add student to advisee list
	if(!facultyTable->isEmpty()) {
		Faculty temp;
		temp.setID(advID);
		if(facultyTable->contains(temp)) {
			Faculty f = FindFac(advID);
			f.addToAdviseeList(stuID);

			cout << "Print faculty advisee list: " << endl;
			f.adviseeList->print();
		}
		else {
			cout << "No faculty member with that ID in the system." << endl;
			cout << "Would you like to create a faculty member with that ID (" << advID << "?" << endl;
			string answer;
			getline(cin, answer);
			if(answer == "yes") {
				AddFac();
			}
			if(answer == "no") {
				cout << "You will now be redirected to main menu." << endl;
			}
			else {
				cout << "Please type 'yes' or 'no'." << endl; 
			}
		}
	}
	else {
		cout << "No faculty members yet." << endl;
		cout << "Would you like to create a faculty member with that ID (" << advID << ")?" << endl;
		string answer;
		getline(cin, answer);
		if(answer == "yes") {
			AddFac();
		}
		if(answer == "no") {
			cout << "You will now be redirected to main menu." << endl;
		}
		else {
			cout << "Please type 'yes' or 'no'." << endl; 
		}
	}
	
}

void Database::bfsS() {
	studentTable->bfs();
}

void Database::bfsF() {
	facultyTable->bfs();
}


int Database::DeleteStu(int stuID) {
	// finds a student by their ID number and deletes them from the tree

	studentRollStack->push(studentTable);
	facultyRollStack->push(facultyTable); // rollback
	
	Student s; 
	s.setID(stuID);
	Student S = studentTable->search(s);

	if(S.getName().compare(".") == 1)
		return 0;

	studentTable->remove(S);
	RemoveAdvisee(stuID);
	return 1;
	// remove student from advisor
	//Rollback

}

void Database::AddFac() {
	//creates a new faculty and adds them to the BST

	studentRollStack->push(studentTable);
	facultyRollStack->push(facultyTable); // rollback

	string holder, facName, facLevel, facDepartment;
	int facID, adviseeID;
	DLinkedList<int> *adviseeList = new DLinkedList<int>(); //fixed size error by creating a new adviseeList instead of just declaring *adviseeList

	cout<< "What is the faculty member's name?" << endl;
	getline(cin,facName);
	
	cout<< "What is the faculty member's ID number?" << endl;
	getline(cin,holder);
	facID = atoi(holder.c_str());

	bool checkID = true;
	while(checkID) {
		Faculty tempF;
		tempF.setID(facID);
		if(facultyTable->contains(tempF)) {
			cout << "That ID number already exists in the system. Please choose another." << endl;
			getline(cin, holder);
			facID = atoi(holder.c_str());
		}
		else {
			checkID = false;
		}
	}
	
	cout << "What is the faculty member's level?" << endl;
	getline(cin,facLevel);

	cout << "What deparment is the faculty member in?" << endl;
	getline(cin,facDepartment);
	
	cout << "What are the ID numbers of the faculty member's advisees? (after each number hit enter). when done type 0." << endl;
	bool check = true;
	while(check) {
		getline(cin,holder);
		if(holder == "d") {
			check = false;
		}
		else {
			adviseeID = atoi(holder.c_str());
			Student s;
			s.setID(adviseeID);
			if(studentTable->contains(s)) {
				adviseeList->insertBack(adviseeID);//replaces list with the last id to be added instead of concatenating
			}
			else {
				cout << "The student you are trying to add to the advisee list (ID number: " << adviseeID << " ) does not exist in the system." << endl;
			}
		}		
	}
	
	adviseeList->print();
	//Faculty *f = new Faculty(facName, facID, facLevel, facDepartment, adviseeList);
	Faculty f(facName, facID, facLevel, facDepartment, adviseeList);
	facultyTable->add(f);
	//Rollback
}

int Database::DeleteFac(int facID, int advTransferID) {
	// finds a faculty by their ID # and deletes them from the tree, takes their advisees and gives
	// them to another faculty member
	studentRollStack->push(studentTable);
	facultyRollStack->push(facultyTable); // rollback

	Faculty f;
	f.setID(facID);
	Faculty F = facultyTable->search(f);

	if(F.getName().compare(".") == 1)
		return 0;

	facultyTable->remove(F);
	f.setID(advTransferID);
	Faculty advTransfer = facultyTable->search(f);

	while(F.getAdviseeListSize() != 0) {
		int frontID = F.deleteFromAdviseeList()	;	
		ChangeStuAdvisor( frontID, advTransferID);	
	}	

	facultyTable->remove(F);
	return 1;
	//Rollback
}

int Database::ChangeStuAdvisor(int stuID, int facID) {
	//finds a student by ID, removes student from their advisor, finds a new advisor by ID,
	//adds the student to the new advisor 

	studentRollStack->push(studentTable); 
	facultyRollStack->push(facultyTable); // rollback

	Student s; 
	s.setID(stuID);
	Student S = studentTable->search(s);

	if(S.getName().compare(".") == 1)
		return 0;
	
	Faculty f;
	f.setID(S.getAdvisor());
	Faculty newF = facultyTable->search(f);
	if(newF.getName().compare(".") == 1)
		return 0;
	if(S.getAdvisor() != 0){
		S.setAdvisor(0);
		
	}
	
	S.setAdvisor(facID);
	newF.addToAdviseeList(stuID); //SEGMENTATION FAULT
	
	// if the student has no advisor, it skips the second step

	//Rollback
}

int Database::RemoveAdvisee(int stuID) {
	//finds a student by ID, removes them from their advisor

	studentRollStack->push(studentTable);
	facultyRollStack->push(facultyTable); // rollback

	Student s; 
	s.setID(stuID);
	Student S = studentTable->search(s);
	if(S.getName().compare(".") == 1)
		return 0;

	Faculty f;
	f.setID(S.getAdvisor());
	Faculty F = facultyTable->search(f);
	if(F.getName().compare(".") == 1)
		return 0;

	Faculty oldF = facultyTable->search(F);
	if(oldF.getName().compare(".") == 1)
		return 0;

	oldF.deleteFromAdviseeList(stuID);
	// is the faculty ID necessary?

	//Rollback
}

void Database::Rollback() {
	// takes back the last action that changed the tree up to five times
	if(!studentRollStack->isEmpty()) {
		studentTable = studentRollStack->pop();
		facultyTable = facultyRollStack->pop();
	}
	else {
		cout << "Rollback unavaialbe, either you haven't changed anything or you really screwed up" << endl;
	}
}


void Database::Exit() {
	//maybe not needed here, could do this in Menu with break
}


void Database::serializeStudents(string outFile) {
	ofstream myfile(outFile, ios::out | ios::trunc | ios::binary);

	if (!myfile.is_open()) {
		cout << "Error opening file." << endl;
	}
	else {
		GenQueue<TreeNode<Student>*> *q;
		q = studentTable->bfs();

		TreeNode<Student>* current;

		while(!q->isEmpty()) {
			//access first Node in queue
			current = q->remove();

			//write Student attributes from current node (from front of queue) to binary file
			//write string to match read string
			unsigned len;

			string n = current->data.getName();
			len = n.size();
			myfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
			myfile.write(n.c_str(), len);

			int i = current->data.getID();
			myfile.write(reinterpret_cast<const char*>(&i), sizeof(int));

			double g = current->data.getGPA();
			myfile.write(reinterpret_cast<const char*>(&g), sizeof(double));

			string l = current->data.getLevel();
			len = l.size();
			myfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
			myfile.write(l.c_str(), len);

			string m = current->data.getMajor();
			len = m.size();
			myfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
			myfile.write(m.c_str(), len);

			int a = current->data.getAdvisor();
			myfile.write(reinterpret_cast<const char*>(&a), sizeof(int));
		}
		
		myfile.close();
	}
}

void Database::serializeFaculty(string outFile) {
	ofstream myfile(outFile, ios::out | ios::trunc | ios::binary);

	if (!myfile.is_open()) {
		cout << "Error opening file." << endl;
	}

	GenQueue<TreeNode<Faculty>*> *q;
	q = facultyTable->bfs();

	TreeNode<Faculty>* current;

	while(!q->isEmpty()) {
		current = q->remove();

		unsigned len;

		string n = current->data.getName();
		len = n.size();
		myfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
		myfile.write(n.c_str(), len);

		int i = current->data.getID();
		myfile.write(reinterpret_cast<const char*>(&i), sizeof(int));

		string l = current->data.getLevel();
		len = l.size();
		myfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
		myfile.write(l.c_str(), len);

		string d = current->data.getDepartment();
		len = d.size();
		myfile.write(reinterpret_cast<const char*>(&len), sizeof(len));
		myfile.write(d.c_str(), len);
		
		//add a marker representing the length of the advisee list to binary file
		//when file is read in, this marker will tell it how many items to read in from file into the advisee list before moving to next node
		int marker = current->data.getAdviseeListSize();
		
		myfile.write(reinterpret_cast<const char*>(&marker), sizeof(int));

		//write in each advisee ID from advisee list
		DLinkedList<int>* a = current->data.getAdviseeList();

		while(!a->isEmpty()) {
			int i = a->removeFront();
			myfile.write(reinterpret_cast<const char*>(&i), sizeof(int));
		}
	}
	myfile.close();
}

BinarySearchTree<Student>* Database::deserializeStudents(string inFile) {
	//initialize studentTable to empty before reading in stored copy of student bst
	studentTable = new BinarySearchTree<Student>();
	ifstream file(inFile, ios::in | ios::binary);

	if(!file.is_open()) {
		cout << "Error opening file." << endl;
	}
	else {
		// THE CODE REPEATS THE WHILE LOOP one extra time, without inputting any of the strings only numbers. while loop runs 4x
		int c = file.peek();
		while(c != EOF) { 
			string tName, tLevel, tMajor;
			int tID, tAdv;
			double tGPA;
			//get length of name string in file -- file.read((char*)&tName, sizeof(string));
			unsigned len;
			file.read(reinterpret_cast<char*>(&len), sizeof(len));
			if(len >0){
				char* buffer = new char[len];
				file.read(buffer, len);
				tName.append(buffer, len);
				delete[] buffer;
			}
			cout << tName << ", ";

			file.read((char*)&tID, sizeof(int));
			cout << tID << ", ";
			file.read((char*)&tGPA, sizeof(double));
			cout << tGPA << ", ";

			
			file.read(reinterpret_cast<char*>(&len), sizeof(len));
			if(len >0){
				char* buffer = new char[len];
				file.read(buffer, len);
				tLevel.append(buffer, len);
				delete[] buffer;
			}
			cout << tLevel << ", ";

			
			file.read(reinterpret_cast<char*>(&len), sizeof(len));
			if(len >0){
				char* buffer = new char[len];
				file.read(buffer, len);
				tMajor.append(buffer, len);
				delete[] buffer;
			}
			cout << tMajor << ", ";

			file.read((char*)&tAdv, sizeof(int));
			cout << tAdv << endl;

			Student s(tName, tID, tGPA, tLevel, tMajor, tAdv);
			//make sure that the program initializes studentTable to empty every time so that
			//this function does not just add the same students in again, but reloads the old table.
			studentTable->add(s);
			c = file.peek();
		}
	}
	studentTable->print();
	file.close();

	return studentTable;
}

BinarySearchTree<Faculty>* Database::deserializeFaculty(string inFile) {
	//initialize facultyTable to empty before reading in faculty from stored bst
	facultyTable = new BinarySearchTree<Faculty>();
	ifstream file(inFile, ios::in | ios::binary);

	if(!file.is_open()) {
		cout << "Error opening file." << endl;
	}
	else {
		string tName, tLevel, tDepartment;
		int tID, marker, tsID;
		DLinkedList<int>* taList = new DLinkedList<int>();

		int c = file.peek();
		while(c != EOF) { 
			//get length of name string in file -- file.read((char*)&tName, sizeof(string));
			unsigned len;
			file.read(reinterpret_cast<char*>(&len), sizeof(len));
			if(len >0){
				char* buffer = new char[len];
				file.read(buffer, len);
				tName.append(buffer, len);
				delete[] buffer;
			}
			cout << tName << ", ";

			file.read((char*)&tID, sizeof(int));
			cout << tID << ", ";

			file.read(reinterpret_cast<char*>(&len), sizeof(len));
			if(len >0){
				char* buffer = new char[len];
				file.read(buffer, len);
				tLevel.append(buffer, len);
				delete[] buffer;
			}
			cout << tLevel << ", ";
			
			file.read(reinterpret_cast<char*>(&len), sizeof(len));
			if(len >0){
				char* buffer = new char[len];
				file.read(buffer, len);
				tDepartment.append(buffer, len);
				delete[] buffer;
			}
			cout << tDepartment << ", ";

			//read in marker for number of IDs that will go into the advisee list

			file.read((char*)&marker, sizeof(int));

			if(marker != 0) {
				for(int i=0; i<marker; i++) {
					file.read((char*)&tsID, sizeof(int));
					taList->insertBack(tsID);
				}
			}
			
			taList->print();

			Faculty f(tName, tID, tLevel, tDepartment, taList);
			facultyTable->add(f);
			c = file.peek();
		}
	}
	file.close();

	facultyTable->print();

	return facultyTable;
}
