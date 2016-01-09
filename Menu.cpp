#include <iostream>
#include <stdlib.h>
#include "Menu.h"
#include "Database.h"
#include "Student.h"
#include "Faculty.h" 

using namespace std;

Menu::Menu() {
	d = new Database();
}

Menu::~Menu() {
	
}

int Menu::input() {
	string userIn;
	int i;
	getline(cin,userIn);
	i = atoi(userIn.c_str());
	return i;
}

void Menu::loadStu() {
	d->deserializeStudents("studentTable.bin");
}

void Menu::loadFac() {
	d->deserializeFaculty("facultyTable.bin");
}

void Menu::printOptions() {
	cout<< endl;
	cout << " 1. Print all student and their information " << endl;
	cout << " 2. Print all Faculty and their information " << endl;
	cout << " 3. Find student by ID # " << endl;
	cout << " 4. Find faculty by ID # " << endl;
	cout << " 5. Find student's faculty advisor " << endl;
	cout << " 6. Display advisor's students " << endl;
	cout << " 7. Add a new Student " << endl;
	cout << " 8. Delete a Student " << endl;
	cout << " 9. Add a faculty member " << endl;
	cout << " 10. Delete a faculty member " << endl;
	cout << " 11. Change a student's advisor " << endl;
	cout << " 12. Remove a student from an advisor " << endl;
	cout << " 13. Rollback " << endl;
	cout << " 14. Exit " << endl;
	cout << endl;

}


int Menu::UserInputs() {
	printOptions();
	cout << "choose an action from the above list" << endl;
	int i = input();
	if (i < 15 && i>0)
		return i;
	else {
		UserInputs();
	}	

}

void Menu::execute() {
	// each case refers to a different action, call appropriate methods
	
	int i = UserInputs();
	switch(i) {
		case 1:
		{ //print all students
			d->PrintAllStu();
			execute();
			break;
		}
		case 2: //print all fac
		{			
			d->PrintAllFac();
			execute();
			break;
		}		

		case 3: //find stu
		{
			cout<< "What is the ID number of the student you are looking for?" << endl;
			getline(cin,holder);
			int i = atoi(holder.c_str());
			d->FindStu(i);
			execute();
			break;
		}
		case 4:
		{
			cout<< "What is the ID number of the faculty you are looking for?" << endl;
			getline(cin,holder);
			int i = atoi(holder.c_str());
			d->FindFac(i);
			execute();
			break;
		}
		case 5:
		{
			cout<<"What is the student's ID number?"<<endl;
			getline(cin,holder);
			int i = atoi(holder.c_str());
			d->FindFacByStu(i);
			execute();
			break;
		}
		case 6:
		{
			cout << "What is the Faculty's ID number?" << endl;
			getline(cin,holder);
			int i = atoi(holder.c_str());
			d->FindStusByFac(i);
			execute();
			break;
		}
		case 7:	
		{
			d->AddStu();
			execute();
			break;
		}
		case 8:
		{
			cout << "What is the student's ID number?" << endl;
			getline(cin,holder);
			int i = atoi(holder.c_str());
			d->DeleteStu(i);
			execute();
			break;
		}
		case 9:
		{
			d->AddFac();
			execute();
			break;
		}
		case 10:
		{
			cout << "What is the ID number of the faculty?" << endl;
			string advTransfer;
			getline(cin,holder);
			int i = atoi(holder.c_str());
			cout << "What is the ID number of the faculty who is taking on the advisees?" << endl;
			getline(cin,advTransfer);
			int t = atoi(advTransfer.c_str());
			d->DeleteFac(i,t);
			execute();
			break;
		}
		case 11:
		{
			string facID;
			cout << "What is the ID number of the student?" << endl;
			getline(cin,holder);
			int i = atoi(holder.c_str());
			cout << "What is the ID number of their new advisor?" << endl;
			getline(cin,facID);
			int t = atoi(facID.c_str());
			d->ChangeStuAdvisor(i,t);
			execute();
			break;
		}
		case 12:	
		{
			cout << "What is the ID number of the student?" << endl;	
			getline(cin,holder);
			int i = atoi(holder.c_str());
			d->RemoveAdvisee(i);
			execute();
			break;
		}
		case 13:
		{
			d->Rollback();
			execute();
			break;
		}
		case 14:
		{
			cout << "Saving studentTable and facultyTable to disk." << endl;
			d->serializeStudents("studentTable.bin");
			d->serializeFaculty("facultyTable.bin");
			cout << "Exiting program." << endl;
			exit(0);
			break;
		}
		default:
		{
			execute();		
			break;
		}
	}

}

