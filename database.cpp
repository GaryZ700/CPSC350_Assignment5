/* Gary Zeri

 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#include "database.h"

using namespace std;

Database::Database(){		
	masterFaculty = LoadDataTable<FacultyRecord>("facultyTable");
	masterStudent = LoadDataTable<StudentRecord>("studentTable");	
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Database::~Database(){
	SaveData();	
	delete masterFaculty;
	delete masterStudent;
}

//---------------------------------------------------------------------------------

bool Database::SaveData(){
	
	//save the faculty data table
	try{
		SaveDataTable<FacultyRecord>("facultyTable", masterFaculty);	
	}
	catch(exception e){
		cout << "Warning! Could not save the faculty data table!" << endl;
		cout << "Please make sure that the masterFaculty file is acessible and not open in another application." << endl; 
		return false;
	}

	//save the student data table
	try{
		SaveDataTable<StudentRecord>("studentTable", masterStudent);	
	} 
	catch(exception e){	
		cout << "Warning! Could not save the student data table!" << endl;
		cout << "Please make sure that the masterStudent file is acessible and not open in another application." << endl; 
		return false;
	}
	
	return true;
}

//---------------------------------------------------------------------------------

template <class record>
BST<int, record>* Database::LoadDataTable(string fileName){

	try{	
		fstream loadFile(fileName, ios::binary | ios::in);
		BST<int, record>* dataTable = new BST<int, record>;
		
		//check if a data table file exists
		if(loadFile.is_open()){

			//get the number of records that exist from the input file
			int numberOfRecords;
			SerializationHelper::Deserialize<int>(loadFile, numberOfRecords);


			//load all of the records from the file into the DataTable
			for(int i=0; i<numberOfRecords; ++i){
				record recordData;
				recordData.Serialize(loadFile);
				dataTable->Put(recordData.id, recordData);
			}
		}
		
		loadFile.close();
		return dataTable;
	}
	catch(exception e){
		cout << "Warning! Unable to read '" << fileName << "' to load the database data table. Please ensure that the file is not being used by another process or that the file has not currupted." << endl;
	}	

	return NULL;
}

//---------------------------------------------------------------------------------

template <class record>
void Database::SaveDataTable(string fileName, BST<int, record>* dataTable){

	try{	
		fstream saveFile;
		saveFile.open(fileName, ios::binary | ios::out);

		DoublyLinkedList<record>* records = dataTable->Positions();

		//first line of the file will be the total number of records stored in this tree
		SerializationHelper::Serialize<int>(saveFile, records->Size());
		
		while(!records->Empty()){

			//serialize each record one by one
			records->Front().Serialize(saveFile);
			records->RemoveFront();	
		}

		delete records;
		saveFile.close();
	}
	catch(exception e){
		cout << "Warning!! Unable to save the database! Check that the output file '" << fileName << "' is not currently in use and is free for writing." << endl;
	}
}
