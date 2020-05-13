/* Gary Zeri
 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#include "university_db_constants.h"
#include "menu.h"
#include "user_input.h"
#include "database.h"

using namespace std;

class UniversityDB{

	public:
		UniversityDB();
		~UniversityDB();
		
		void MainMenu();	
	private:
		bool SearchFaculty(FacultyRecord &record, int id);
		bool SearchStudents(StudentRecord &record, int id);
		bool SearchFaculty(FacultyRecord &record);
		bool SearchStudents(StudentRecord &record);
		void AddStudent();
		void AddFaculty();
		void ChangeStudentAdvisor();
		void AddAdvisor(int studentID, int newAdvisorID);
		void ChangeFacultyAdvisee();
		DoublyLinkedList<int>* GetFacultyAdvisees(int fID);
		void DeleteStudent();
		void DeleteFaculty();
		void SetRollBackPoint();	
		
		int rollBack;
		UserInput input;
		Menu menu;
		Database db;
};
