/* Gary Zeri

 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#ifndef _UNIVERSITY_DB_CONSTANTS_H_
#define _UNIVERSITY_DB_CONSTANTS_H_

#include <string>

using namespace std;

namespace UniversityDBConstants{

	const string kRollBack = "Database was sucessfully rolled back to the last version.";	
	const string kNoRollBack = "There are no earlier versions of the database to roll back to.";
	const string kFacultyFile = "facultyTable";
	const string kStudentFile = "studentTable";
	const string kTempFacultyFile = "facultyRollBackData";
	const string kTempStudentFile = "studentRollBackData";

	const int numberOfOptions = 14;
	const string options[numberOfOptions] = {
		"1. Print all students and their information (sorted by ascending ID#)", 
		"2. Print all faculty and their information (sorted by ascending ID#)", 
		"3. Display student information based on provided id#.", 
		"4. Find and display faculty information based on ID#.", 
		"5. Print the name and info of a student's faculty advisor based on the student's ID#.",
		"6. Print all the names and information of a faculty member's advisees based on the faculty's ID#.",
		"7. Add a new student", 
		"8. Delete a student based on their ID#",
		"9. Add a new faculty member", 
		"10. Delete a faculty member based on their ID#",
		"11. Change a student's advisor based on the ID#s of the faculty and student.",
		"12. Remove an advisee from a faculty member based on the ID#s of the faculty and the student.",
		"13. Rollback", 
		"14. Exit"
	};

	const string kStudentID = "Please enter a student ID#: ";
	const string kStudentName = "Please enter the student's name: ";
	const string kStudentLevel = "Please enter the student's level, (EX. Sophomore, Senior): ";
	const string kStudentMajor = "Please enter the student's major: ";
	const string kStudentGpa = "Please enter the student's GPA: ";
	const string kValidGpa = "Please enter a valid GPA between 0.0 and 5.0: ";
	const string kStudentAdvisor = "Please enter the ID# for the student's faculty advisor. If the student does not have an advisor, then please enter -1: ";	

	const string kValidID = "Please enter a valid integer ID#, that is greater than or equal to 0.";
	const string kFacultyID = "Please enter a faculty ID#: ";
	const string kNoStudents = "No student records currently exist in the database.";
	const string kNoFaculty = "No faculty records currently exist in the database."; 
	const string kValIDID = "Please enter a valid id integer greater than or equal to 0.";
	const string kStudentNotFound = "Warning! Requested student does not exist in the database.";
	const string kFacultyNotFound = "Warning! Requested faculty does not exits in the database.";
	const string kAdviseeRemoveID = "Please enter the ID of the advisee to rmove from this faculty member.";
	const string kIntroduction = "Welcome to the Handy Dandy Happy Chapy University Database!\n\n";
	const string kAddStudent = "Please enter the ID# for a new student: ";
	const string kAddFaculty = "Please enter the ID# for a new faculty member: ";
	const string kRemoveStudent = "Please enter the ID# of a student to remove from the database: ";	
	const string kRemoveFaculty = "Please enter the ID# of a faculty member to remove from the database: ";
	const string kDuplicateStudentID = "The entered ID# matches another student currently in the database. Please enter a new ID#: ";

	const string kDuplicateFacultyID = "The entered ID# matches another faculty member currenty in the database. Please enter a new ID#: ";
	const string kFacultyName = "Please enter the faculty member's name: ";
	const string kFacultyLevel = "Please enter the faculty member's level, (EX. Dean, Associate Professor): ";
	const string kFacultyDepartment = "Please enter the faculty member's department: ";
	const string kAddFirstAdvisee = "Would you like to add an advisee to this faculty member?";
	const string kAddAdvisee = "Would you like to add another advisee to this faculty member?";
	const string kDuplicateAdvisee = "Can not add this student as an advisee to the faculty member since this student is alreadly listed as the member's advisee.";
	const string kAdviseeAdded = "Student added to this faculty member as an advisee.";

	const string kChangeStudentAdvisor = "Please enter the ID# of the student whose advisor is to be changed: ";
};

#endif //_UNIVERSITY_DB_CONSTANTS_H_
