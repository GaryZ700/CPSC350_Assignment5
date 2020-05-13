/* Gary Zeri
 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#include "database_record.h"

using namespace std;

bool DatabaseRecord::operator==(const DatabaseRecord &dbr){
	return (this->id == dbr.id);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool DatabaseRecord::operator>(const DatabaseRecord &dbr){
	return (this->id > dbr.id);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool DatabaseRecord::operator<(const DatabaseRecord &dbr){
	return (this->id < dbr.id);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool DatabaseRecord::operator<=(const DatabaseRecord &dbr){
	return (this->id <= dbr.id);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool DatabaseRecord::operator>=(const DatabaseRecord &dbr){
	return (this->id >= dbr.id);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DatabaseRecord::Serialize(fstream &outputFile) const {
	
	SerializationHelper::Serialize<int>(outputFile, this->id);	
	SerializationHelper::SerializeString(outputFile, this->name);
	SerializationHelper::SerializeString(outputFile, this->level);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DatabaseRecord::Deserialize(fstream &inputFile){

	SerializationHelper::Deserialize<int>(inputFile, this->id);
	SerializationHelper::DeserializeString(inputFile, this->name);
	SerializationHelper::DeserializeString(inputFile, this->level);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void DatabaseRecord::Display() const {
	cout << "\tID#: " << id << endl;
	cout << "\tName: " << name << endl;
	cout << "\tLevel: " << level << endl; 
}
