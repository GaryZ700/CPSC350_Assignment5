/* Gary Zeri
 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

/*#include "serialization_helper.h"

using namespace std;

void SerializationHelper::SerializeString(fstream &outputFile, string data){

	int stringLength = data.length();
	char* cData = new char[stringLength];

	strcpy(cData, data.c_str());

	outputFile.write((char*)&stringLength, sizeof(stringLength));
	outputFile.write((char*)cData, sizeof(char) * stringLength);	
	
	delete[] cData;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void SerializationHelper::DeserializeString(fstream &inputFile, string &data){
	
	int stringLength;
	char *cData;

	inputFile.read((char*)&stringLength, sizeof(stringLength));
	
	cData = new char[stringLength];

	inputFile.read((char*)cData, stringLength);

	string conversion(cData);
	data = conversion;

	delete[] cData;	
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class T>
void SerializationHelper::Serialize(fstream &outputFile, T data){		
	outputFile.write((char*)&data, sizeof(data));
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class T>
void SerializationHelper::Deserialize(fstream &inputFile, T &data){
	inputFile.read((char*)&data, sizeof(data));
}
*/
