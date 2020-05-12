/* Gary Zeri

 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "bst.h"
#include "faculty_record.h"
#include "student_record.h"
#include "serialization_helper.h"

using namespace std;

class Database{

	public:
		Database();
		~Database();
	private:
		bool SaveData();

		template <class record>
		BST<int, record>* LoadDataTable(string fileName);

		template <class record>
		void SaveDataTable(string fileName, BST<int, record>* dataTable);
	
		BST<int, FacultyRecord>* masterFaculty;
		BST<int, StudentRecord>* masterStudent;	
};

#endif //_DATABASE_H_
