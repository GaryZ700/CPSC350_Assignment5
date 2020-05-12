/* Gary Zeri
 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#include "faculty_record.h"

using namespace std;

FacultyRecord::FacultyRecord(){	
		this->id = -1;
		this->name = "";
		this->level = "";
		this->department = ""; 
		this->advisees = NULL;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

FacultyRecord::FacultyRecord(int id, string name, string level, string department, DoublyLinkedList<int>* advisees){
		this->id = id;
		this->name = name;
		this->level = level;
		this->department = department; 
		this->advisees = advisees;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

FacultyRecord::~FacultyRecord(){
	delete advisees;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FacultyRecord::Serialize(fstream &outputFile) const {

	DatabaseRecord::Serialize(outputFile);

	SerializationHelper::SerializeString(outputFile, department);
	SerializationHelper::Serialize<int>(outputFile, advisees->Size());

	int advisee;
	for(int i=0; i<advisees->Size(); ++i){
		advisees->SearchPosition(i, advisee);
		SerializationHelper::Serialize<int>(outputFile, advisee);
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void FacultyRecord::Deserialize(fstream &inputFile){

	DatabaseRecord::Deserialize(inputFile);	

	SerializationHelper::DeserializeString(inputFile, department);

	int adviseesSize;
	SerializationHelper::Deserialize<int>(inputFile, adviseesSize);

	if(advisees != NULL)
		delete advisees;
	advisees = new DoublyLinkedList<int>;

	int advisee;
	for(int i=0; i<adviseesSize; ++i){
		SerializationHelper::Deserialize<int>(inputFile, advisee);
		advisees->InsertFront(advisee); 
	}
}
