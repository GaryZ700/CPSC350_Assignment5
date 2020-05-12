/* Gary Zeri
 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#include "student_record.h"

using namespace std;

StudentRecord::StudentRecord(){
	this->id = -1;
	this->name = "";
	this->level = "";
	this->major = "";
	this->gpa = -1;
	this->advisor = -1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

StudentRecord::StudentRecord(int id, string name, string level, string major, double gpa, int advisor){
	this->id = id;
	this->name = name;
	this->level = level;
	this->major = major;
	this->gpa = gpa;
	this->advisor = advisor;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StudentRecord::Serialize(fstream &outputFile) const {

	DatabaseRecord::Serialize(outputFile);
	
	SerializationHelper::SerializeString(outputFile, major);
	SerializationHelper::Serialize<double>(outputFile, gpa);
	SerializationHelper::Serialize<int>(outputFile, advisor);

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void StudentRecord::Deserialize(fstream &inputFile){

	DatabaseRecord::Deserialize(inputFile);

	SerializationHelper::DeserializeString(inputFile, major);
	SerializationHelper::Deserialize<double>(inputFile, gpa);
	SerializationHelper::Deserialize<int>(inputFile, advisor);
}
