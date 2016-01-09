#include <iostream>
#include "Student.h"
#include "Faculty.h"
#include "BinaryTree.h"
#include "Database.h"
#include "Menu.h"

using namespace std;

bool exists(const string& name) {
	ifstream infile(name);
	return infile.good();
}

int main() {

	Menu *m = new Menu();

	if( exists("studentTable.bin") ) {
		cout << "Student table file already exists. Load studentTable data from previous use." << endl;
		m->loadStu();
		//deserialize studentTable into database
	}
	else {
		cout << "First time running program. Create new, empty studentTable." << endl;
		
	}
	if( exists("facultyTable.bin")) {
		cout << "Faculty table file already exists. Load facultyTable data from previous use." << endl;
		m->loadFac();
	}
	else {
		cout << "First time running program. Create new, empty facultyTable." << endl;
		//create new database
	}

	m->execute();
	
	return 0;
}
