/* Gary Zeri
 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#ifndef _FACULTY_RECORD_H_
#define _FACULTY_RECORD_H_

#include "serialization_helper.h"
#include "doubly_linked_list.h"
#include "database_record.h"

using namespace std;

class FacultyRecord : DatabaseRecord{

	friend class Database;

	public:
		FacultyRecord();
		FacultyRecord(int id, string name, string level, string department, DoublyLinkedList<int>* advisees);
		~FacultyRecord();
		void Serialize(fstream &outputFile) const;
		void Deserialize(fstream &inputFile);	
	private:	
		string department;
		DoublyLinkedList<int>* advisees;
};

#endif //FACULTY_RECORD_H_
