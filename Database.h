#ifndef DATABASE_H_
#define DATABASE_H_
#include <iostream>
#include "BinaryTree.h"
#include "GenStack.h"
#include "Faculty.h"
#include "Student.h"
#include <string>

using namespace std;

class Database {
	public:
		Database();
		~Database();
		
		BinarySearchTree<Student> *studentTable;
		BinarySearchTree<Faculty> *facultyTable;
		GenStack<BinarySearchTree<Student>*> *studentRollStack;
		GenStack<BinarySearchTree<Faculty>*> *facultyRollStack;
	
		void PrintAllStu();
		void PrintAllFac();
		Student FindStu(int iD);
		Faculty FindFac(int iD);
		Faculty FindFacByStu(int stuID);
		void FindStusByFac(int facID);
		void AddStu();
		int DeleteStu(int iD);
		void AddFac();
		int DeleteFac(int iD, int advTransferID);
		int ChangeStuAdvisor(int stuID, int facID);
		int RemoveAdvisee(int stuID);
		void Rollback();
		void Exit();
		
		void serializeStudents(string outFile);
		void serializeFaculty(string outFile);
		void bfsS();
		void bfsF();
		BinarySearchTree<Student>* deserializeStudents(string inFile);
		BinarySearchTree<Faculty>* deserializeFaculty(string inFile);
};

#endif /* DATABASE_H_ */ 
