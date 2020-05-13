/* Gary Zeri
   ID: 2321569 
   zeri@chapman.edu
   CPSC 350-02
   Assignment 1
*/

#include "user_input.h"

using namespace std;

UserInput::UserInput(){}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Pause Function
//Will pause program execution until the user presses enter
//msg: String message to display to the user
void UserInput::Pause(string msg){
	cout << msg << endl;
	cin.get();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*GetBool Function 
  return a bool based on user input
  msg: String to prompt the user with
  trueOption: String to display to the user for the true option
  falseOption: String to display to the user for the false optoin
  errorMsg: String to display the user if they enter an incorrect input
*/
bool UserInput::GetBool(string msg, string trueOption, string falseOption, string errorMsg){

	int input;

	cout << msg << endl;
	cout << "\t" << "1. " << trueOption << endl;
	cout << "\t" << "2. " << falseOption << endl << endl;
	
	cin >> input;

	while(!cin || (input != 1 && input != 2) ){

		cout << errorMsg << endl;
		CinUpdate();
		cin >> input;
		cout << input << endl;
	}

	CinUpdate();
	
	if(input == 1)
		return true;
	else 
		return false;	
} 

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*GetInt Function 
  return the int the user inputted
  msg: string to prompt the user with 
  errorMsg: string to display the user if the incorrect input is provided
  min: int that is the minimum value that the user can input
  max: int that is the maximum value that the user can input
  tooSmallError: string error to display to the user if the value that was inputted was less than the minimum
  tooLargeError: string error to display to the user if the value that was inputted was greater than the maximum
*/
int UserInput::GetInt(string msg, string errorMsg, int min, int max, string tooSmallError, string tooLargeError){

	int input;

	cout << msg; 
	
	cin >> input;

	//do while loop to ensure the user inputs the correct data type being requested		
	while(!cin || input > max || input < min){

		if(!cin)
			cout << errorMsg << endl;
		else if(input < min)
			cout << tooSmallError << endl;
		else
			cout << tooLargeError << endl;

		CinUpdate();
		cin >> input;
	};

	CinUpdate();

	return input;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//GetDouble Function 
//msg: string message that is to be displayed to the user to prompt for a double
//errorMsg: string meessage to display if the user does not enter a valid number
//min: double of the minimum number that is to be inputted
//max: double of the maximum number that is to be inputted
//tooSmallError: string error to display if the number inputted is smaller than the minimum
//tooLargeError: string error to display if the number inputted is larger than the maximum value
double UserInput::GetDouble(string msg, string errorMsg, double min, double max, string tooSmallError, string tooLargeError){
	
	double input;
	cout << msg;
	
	cin >> input;

	//do while loop to ensure the user inputs the correct data type being requested		
	while(!cin || input > max || input < min){
	
		if(!cin) 
			cout << errorMsg << endl;
		else if(input > max)
			cout << tooLargeError << endl;
		else
			cout << tooSmallError << endl;
		
		CinUpdate();
		cin >> input;
	};

	CinUpdate();

	return input;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*GetStr Function 
  return the string the user inputted
  msg: string to prompt the user with 
*/
string UserInput::GetStr(string msg){

	string input; 

	cout << msg;
	
	getline(cin, input);

	cout << endl;

	return input;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*GetFile Function 
  returns an fstream with an open file that the user provided
  msg: string of a message to display to the user to get a file name
  error_msg: string of a message to display to the user if the file name is invalid  
  mode: openmode that represents the mode that the file should be opened in 
*/
fstream UserInput::GetFile(string msg, string errorMsg, ios::openmode mode){
	
	string fileName;
	fstream file;	

	cout << msg; 
	GetLine(fileName);
	cout << endl;
	
	file.open(fileName, mode);
	
	//check to ensure that the file is open
	//if not, keep asking the user until a correct file name is provided
	while(!file.is_open()){
		cout << errorMsg;
		GetLine(fileName);
		file.open(fileName);
	}

	return file;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*StringIsNumber Function 
  returns a bool representing whether the given string is a valid number
  strongToTest: string to test to determine if it is a valid number
  number: reference to a float that allows for return of the number from the string
*/
bool UserInput::StringIsNumber(string stringToTest, double &number){
		
		try{
			number = stoi(stringToTest);			
		}
		catch(exception e){
			return false;
		}

		return true;
	}
  
//----------------------------------------------------------------------------------

/*GetLine Function 
  Wrapper Function for the getline function used with cin 
  inputString: reference to string outside function scope whose value should modified by getline
*/
void UserInput::GetLine(string& inputString){
	getline(cin, inputString);
} 

//----------------------------------------------------------------------------------

void UserInput::CinUpdate(){
	cin.clear();
	cin.ignore(numeric_limits<int>::max(), '\n');
}
