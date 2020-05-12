/* Gary Zeri
 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#ifndef _DATABASE_RECORD_H_
#define _DATABASE_RECORD_H_

#include <iostream>
#include "serialization_helper.h"

using namespace std;

//virtual class designed for other database records to inherit from 
class DatabaseRecord {

	friend class DataBase;

	public:
		bool operator==(const DatabaseRecord &dbr);
		bool operator>(const DatabaseRecord &dbr);
		bool operator<(const DatabaseRecord &dbr);
		bool operator<=(const DatabaseRecord &dbr);
		bool operator>=(const DatabaseRecord &dbr); 
		void Serialize(fstream &outputFile) const;
		void Deserialize(fstream &inputFile); 
	protected:
		int id;
		string name;

		//for students, will be the grade, freshman, sophomore, etc.
		//for faculty, will be their position in the university: lecturer, asistant prof, assoc. prof. etc.
		string level;
};

#endif //_DATABASE_RECORD_H_
