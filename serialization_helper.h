/* Gary Zeri
 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#ifndef _SERIALIZATION_HELPER_H_
#define _SERIALIZATION_HELPER_H_

#include <fstream>
#include <cstring>
#include <string>

using namespace std;

class SerializationHelper{

	public:
		static void SerializeString(fstream &outputFile, string data){

			int stringLength = data.length();
			char* cData = new char[stringLength];

			strcpy(cData, data.c_str());

			outputFile.write((char*)&stringLength, sizeof(stringLength));
			outputFile.write((char*)cData, sizeof(char) * stringLength);	
			
			delete[] cData;
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		static void DeserializeString(fstream &inputFile, string &data){
			
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
		static void Serialize(fstream &outputFile, T data){
			outputFile.write((char*)&data, sizeof(data));
		}
	       
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		template <class T>
		static void Deserialize(fstream &inputFile, T &data){
			inputFile.read((char*)&data, sizeof(data));
		}
};

#endif //_SERIALIZATION_HELPER_H_
