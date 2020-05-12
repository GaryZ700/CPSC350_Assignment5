/* Gary Zeri
 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#ifndef STUDENT_RECORD_H_
#define STUDENT_RECORD_H_

#include "serialization_helper.h"
#include "database_record.h"

using namespace std;

class StudentRecord : DatabaseRecord{

	friend class Database;

	public:
		StudentRecord();
		StudentRecord(int id, string name, string level, string major, double gpa, int advisor);
		void Serialize(fstream &outputFile) const;
		void Deserialize(fstream &inputFile);
	private:	
		string major;
		double gpa;
		int advisor;
};

#endif //STUDENT_RECORD_H_
