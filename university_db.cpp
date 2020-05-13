/* Gary Zeri
 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#include "university_db.h"

using namespace std;
using namespace UniversityDBConstants;

UniversityDB::UniversityDB(){

	rollBack = 0;
	
	menu.AddText(kIntroduction);

	//set up the main menu
	for(int i=0; i<numberOfOptions; ++i)
		menu.AddOption(options[i], to_string(i+1));	

	MainMenu();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

UniversityDB::~UniversityDB(){
	
	//delete any temp files that are currently existing
	while(rollBack > 0){
		remove( (kTempStudentFile + to_string(rollBack)).c_str() );
		remove( (kTempFacultyFile + to_string(rollBack)).c_str() );
		
		--rollBack;
	}

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void UniversityDB::MainMenu(){

	menu.Display();
	string inputString = menu.ParseOption();
	while(inputString != "14"){
		
		switch(stoi(inputString)){
			
			//print out all students in ascending order
			case 1: 
			{ 
				DoublyLinkedList<StudentRecord>* students = db.masterStudent->InOrderTraversal();
				if(students->Size() == 0)
					cout << kNoStudents << endl;
				else
					while(students->Size() > 0){
						students->Tail().Display();
						students->RemoveTail();
					}
				break;
			}

			//print out all students in descending order
			case 2:
			{	
				DoublyLinkedList<FacultyRecord>* faculty = db.masterFaculty->InOrderTraversal();	
				if(faculty->Size() == 0)
					cout << kNoFaculty << endl;
				else{
					while(faculty->Size() > 0){
						faculty->Tail().Display();
						faculty->RemoveTail();
					}				
				}	

				break;
			}

			//display student from user provided id
			case 3: 
			{
				StudentRecord sr;

				if(SearchStudents(sr))
					sr.Display();
				break;
			}

			//display faculty information provided id
			case 4:
			{ 
				FacultyRecord fr;
				
				if(SearchFaculty(fr))
					fr.Display();
				break;
			}

			//given student's id, print their advisor's information
			case 5:
			{
				StudentRecord sr;
				
				if(SearchStudents(sr)){			

					if(sr.advisor != -1){				
						FacultyRecord fr; 
		
						if(SearchFaculty(fr, sr.advisor))				
							fr.Display();					
					}
					else
						cout << "Student id: " << sr.id << " does not have a faculty advisor." << endl;
				}
 				break;
			}

			//given a faculty member's id, print out all the advisees of the faculty member
			case 6:
			{ 
				FacultyRecord fr;
				StudentRecord sr;
				
				if(SearchFaculty(fr))
				{					
					if(fr.advisees->Size() == 0)
						cout << "Faculty ID#: " << fr.id << " does not have any student advisees." << endl;
					else{
						int advisee;
						for(int i=0; i<fr.advisees->Size(); ++i){
							fr.advisees->SearchPosition(i, advisee);
							SearchStudents(sr, advisee);
							sr.Display();
						}	
					}
				}
				break;
			}
			
			//add a new student
			case 7: 
				AddStudent();
				break;
			
			//delete a student
			case 8:
				DeleteStudent();
				break;

			//add a new faculty
			case 9: 
				AddFaculty();	
				break;

			//delete a faculty member
			case 10: 
				DeleteFaculty();
				break;

			//chagne student's advisor
			case 11:
				ChangeStudentAdvisor();
				break;	

			//remove advisees from a faculty member
			case 12:
				ChangeFacultyAdvisee(); 
				break;
			
			//roll the database back to an earlier version
			case 13:
			{	
				if(rollBack > 0){
					db.LoadData(kTempFacultyFile + to_string(rollBack), kTempStudentFile + to_string(rollBack));
					remove( (kTempFacultyFile + to_string(rollBack)).c_str() );
					remove( (kTempStudentFile + to_string(rollBack)).c_str() );	
					--rollBack;
					cout << kRollBack << endl;	
				}
				else
					cout << kNoRollBack << endl;	
			        break;
			}
		}

		input.Pause();
		menu.Display();
		inputString = menu.ParseOption();
	}	
}

//---------------------------------------------------------------------------------

//searches for the faculty specifed by the id, and returns the faculty record via the record paramter
//returns a bool representing whether or not the faculty in question was found in the database
bool UniversityDB::SearchFaculty(FacultyRecord &record, int id){
		
	if(!db.masterFaculty->Find(id, record)){
		cout << "Faculty ID#: " << id << " not found in the database." << endl;		
		return false;
	}
	
	return true;
}

//---------------------------------------------------------------------------------

//searches for the student specifed by the id, and returns the student record via the record paramter
//returns a bool representing whether or not the student in question was found in the database
bool UniversityDB::SearchStudents(StudentRecord &record, int id){
	
	if(!db.masterStudent->Find(id, record)){
		cout << "Student ID#: " << id << " not found in the database." << endl;		
		return false;
	}

	return true;
}

//---------------------------------------------------------------------------------


//prompts the user to enter an id of a faculty member to search for and returns the faculty record via the record paramter
//returns a bool representing whether or not the faculty member in question was found in the database
bool UniversityDB::SearchFaculty(FacultyRecord &record){
	
	if(db.masterFaculty->Size() == 0){
		cout << kNoFaculty << endl;
		return false;	
	}

	return SearchFaculty(record, input.GetInt("Please input a faculty ID#: ", kValidID, 0));
}

//---------------------------------------------------------------------------------

//prompts the user to enter an id of a student to search for and returns the student record via the record paramter
//returns a bool representing whether or not the faculty member in question was found in the database
bool UniversityDB::SearchStudents(StudentRecord &record){	

	if(db.masterStudent->Size() == 0){
		cout << kNoStudents << endl;
		return false;
	}

	return SearchStudents(record, input.GetInt("Please input a student ID#: ", kValidID,0));
}

//---------------------------------------------------------------------------------

void UniversityDB::AddStudent(){

	StudentRecord sr;
	StudentRecord tempSr;
	FacultyRecord fr;
		
	sr.id = input.GetInt(kAddStudent, kValidID, 0);
	while(db.masterStudent->Find(sr.id, tempSr))
		sr.id = input.GetInt(kDuplicateStudentID, kValidID, 0);	

	sr.name = input.GetStr(kStudentName);
	sr.level = input.GetStr(kStudentLevel);
	sr.major = input.GetStr(kStudentMajor);		
	sr.gpa = input.GetDouble(kStudentGpa, kValidGpa, 0, 5);

	sr.advisor = input.GetInt(kStudentAdvisor, "Please enter a valid greater than -1: ", -1);
	
	while(!db.masterFaculty->Find(sr.advisor, fr)){

		if(sr.advisor == -1)
			break;		
		sr.advisor = input.GetInt(kFacultyNotFound, "Please enter a valid greater than or equal to -1: ", -1);
	}
		
	SetRollBackPoint();	

	if(sr.advisor != -1)
		//add student as an advisee to the advisor
		fr.advisees->InsertFront(sr.id);	
	
	db.masterStudent->Put(sr.id, sr);
}

//---------------------------------------------------------------------------------

void UniversityDB::AddFaculty(){

	FacultyRecord fr;
	FacultyRecord temp;

	fr.id = input.GetInt(kAddFaculty, kValidID, 0);
	while(db.masterFaculty->Find(fr.id, temp)){
		fr.id = input.GetInt(kDuplicateFacultyID, "The id must be a valid integer greater than 0.", 0);	
	}

	fr.name = input.GetStr(kFacultyName);
	fr.level = input.GetStr(kFacultyLevel);
	fr.department = input.GetStr(kFacultyDepartment);
	
	SetRollBackPoint();

	//get the faculty member's list of advisees
	fr.advisees = GetFacultyAdvisees(fr.id);

	db.masterFaculty->Put(fr.id, fr);	
}


//---------------------------------------------------------------------------------

DoublyLinkedList<int>* UniversityDB::GetFacultyAdvisees(int fID){
		
	DoublyLinkedList<int>* advisees = new DoublyLinkedList<int>;
	StudentRecord sr;

	if(input.GetBool(kAddFirstAdvisee,"Yes", "No"))
		do{	
			//check to ensure that the entered advisee is a valid student in the database
			if(!db.masterStudent->Find(input.GetInt(kStudentID, kValidID, 0), sr))
				cout << kStudentNotFound << endl;
				
			//check to ensure that the student is not alreadly an advisee of the student
			else if(advisees->Search(sr.id) != -1)
				cout << kDuplicateAdvisee << endl;
			
			//check if the student alreadly has another advisor
			//if not, then add this student as an advise 
			//and also add this faculty member as an advisor to the student
			else if(sr.advisor == -1){
				cout << kAdviseeAdded << endl;
				sr.advisor = fID;
				advisees->InsertFront(sr.id);		
				AddAdvisor(sr.id, fID);
			}
			//if the student alreadly has another advisor, then do not add the student as an advisee to this faculty
			else
				cout << "Warning! Can not add this faculty as an advisor to student: " << sr.id << ". This student alreadly has an advisor: " << sr.advisor << endl;
	
		}while(input.GetBool(kAddAdvisee, "Yes", "No"));

	return advisees;
}

//---------------------------------------------------------------------------------

void UniversityDB::ChangeStudentAdvisor(){

	if(db.masterFaculty->Size() == 0){
		cout << kNoFaculty << endl;
		return;
	}
	else if(db.masterStudent->Size() == 0){
		cout << kNoStudents << endl;
		return;
	}
	
	FacultyRecord fr;
	StudentRecord sr;	

	if(!db.masterStudent->Find(input.GetInt(kChangeStudentAdvisor, kValidID, 0), sr)){
		cout << kStudentNotFound << endl;
		return;
	}		

	if(!db.masterFaculty->Find(input.GetInt(kStudentAdvisor, kValidID, -1), fr)){
		cout << kFacultyNotFound << endl;
		return;
	}	

	SetRollBackPoint();
	
	//add advisee to new advisor
	fr.advisees->InsertFront(sr.id);
	
	//check if student should be removed from old advisor
	if(sr.advisor != -1){
		db.masterFaculty->Find(sr.advisor, fr);
		fr.advisees->RemovePosition(fr.advisees->Search(sr.advisor));
		}
	
	AddAdvisor(sr.id, fr.id);
}

//--------------------------------------------------------------------------------

void UniversityDB::AddAdvisor(int studentID, int newAdvisorID){
	StudentRecord sr;
	StudentRecord newSr;

	db.masterStudent->Find(studentID, sr);

	newSr.id = sr.id;
	newSr.name = sr.name;
	newSr.level = sr.level;
	newSr.major = sr.major;
	newSr.gpa = sr.gpa;
	newSr.advisor = newAdvisorID;

	db.masterStudent->Erase(sr.id);
	db.masterStudent->Put(newSr.id, newSr);
}

//--------------------------------------------------------------------------------

void UniversityDB::ChangeFacultyAdvisee(){

	if(db.masterFaculty->Size() == 0){
		cout << kNoFaculty << endl;
		return;
	}
	else if(db.masterStudent->Size() == 0){
		cout << kNoStudents << endl;
		return;
	}

	 FacultyRecord fr;
	 if(!SearchFaculty(fr))
		return;
	 
	 int studentID = input.GetInt(kAdviseeRemoveID, kValidID, 0);
	 int adviseePosition = fr.advisees->Search(studentID);

	 if(adviseePosition == -1){
		cout << "Request to romove student " << studentID << " from the advisee list of " << fr.id << " could be performed since the specified student was not an adviseee of the specifeid faculty." << endl;
		return;
	}

	SetRollBackPoint();
	
	fr.advisees->RemovePosition(adviseePosition);	
			
	AddAdvisor(studentID, -1);
}

//--------------------------------------------------------------------------------

void UniversityDB::DeleteStudent(){

	if(db.masterStudent->Size() == 0){
		cout << kNoStudents << endl;
		return;
	}

	StudentRecord sr;
	
	if(!db.masterStudent->Find(input.GetInt(kRemoveStudent, kValidID, 0), sr)){
		cout << kStudentNotFound << endl;
		return;
	}

 	SetRollBackPoint();
	//check if there are advisor relationships that need to be delt with 
	if(sr.advisor != -1){
		FacultyRecord fr;
		db.masterFaculty->Find(sr.advisor, fr);
		cout << fr.advisees->Size() << endl;
		fr.advisees->RemovePosition(fr.advisees->Search(sr.id));
	}		

	db.masterStudent->Erase(sr.id);	
}

//--------------------------------------------------------------------------------

void UniversityDB::DeleteFaculty(){

	if(db.masterFaculty->Size() == 0){
		cout << kNoFaculty << endl;
		return;
	}

	FacultyRecord fr;	
	
	if(!db.masterFaculty->Find(input.GetInt(kRemoveFaculty, kValidID, 0), fr)){
		cout << kFacultyNotFound << endl;
		return;
	}		

	SetRollBackPoint();

	DoublyLinkedList<int>* advisees = fr.advisees;

	//check if there are any advisee relationships that need to be updated
	while(advisees->Size() > 0){
		AddAdvisor(advisees->Front(), -1);
		advisees->RemoveFront();
	}
	
	delete advisees;
	db.masterFaculty->Erase(fr.id);
	
}

//--------------------------------------------------------------------------------

void UniversityDB::SetRollBackPoint(){
	++rollBack;
	cout << rollBack << endl;
	db.SaveData(kTempFacultyFile + to_string(rollBack), kTempStudentFile + to_string(rollBack));
}
