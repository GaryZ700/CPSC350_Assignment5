/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 3: Syntax Checker
*/

#include "menu.h"

Menu::Menu(int precision){ this->precision = precision; }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Initalize the constant static variables of this class
//depending on the OS being run, decide on a clear screen command to use
#ifdef _WIN32
	const string Menu::CLR_SCR = "cls";
#else
	const string Menu::CLR_SCR = "clear";
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Display function
//displays the menu on the screen
void Menu::Display(){

	//clear the screen
	system(CLR_SCR.c_str());
	
	int textCounter = 0;
	int optionCounter = 0;
	
	//set decimal ponts to specifed amount of decimal points
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(precision);
	
	//loop over all the componets in the menu
	//and then depending on the componet type, display it on the screen
	for(int i=0; i < componetOrdering.size(); ++i){
	
		if(componetOrdering[i] == 't'){
			cout << text[textCounter];	
			textCounter += 1;
		}
		else{
			cout << options[optionCounter].text;
			optionCounter += 1;
		}
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//AddText Function
//text, takes string of text to display at current position in the menu
void Menu::AddText(string textToDisplay){	

	text.push_back(textToDisplay);	

	//add char to componet ordering to signify that the next componet to display on the screen is a text componet
	componetOrdering.push_back('t');
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//AddOption function
//void return 
//optionText, string that represents text to display for the option at this current point
//identifier, string that represents keyword or text that user must input to select this option
void Menu::AddOption(string optionText, string identifier){

	//declare and initialize a new option struct
	option structData = {optionText.append("\n"), identifier};
	options.push_back(structData);
	
	componetOrdering.push_back('o');
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//parse option function, get input from user based on option identifiers
//has a void return value
//promptText, string to ask user for option, default value is provided
//errorMessage, string that should be displayed if user does not provide the correct input
string Menu::ParseOption(string promptText, string errMsg){

	//prompt user for input and parse it
	string userInput;
	cout << promptText;	
	getline(cin, userInput);
	
	while(true){	

		//iterate through all possible valid input options, and execute coressponding action fucntion if identifiers match
		//if identifiers do not match, then print the error message and try again
		for(int i=0; i < options.size(); ++i){
			
			//check if input matches identifier, then execute an action
			if(options[i].identifier == userInput){
				return userInput;
			}
		}

		//if none of the inputs matched the option identifiers, then inform the user of their bad input
		cout << "\n" << errMsg;
		getline(cin, userInput);	
	}	
}
