/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 3: Syntax Checker
*/

#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class Menu{

	public:
		Menu(int precision=2);

		void Display();
		void AddText(string textToDisplay);
		void AddOption(string option, string identifier);
		string ParseOption(string promptText="\n\nPlease select an option: ", string errMsg="\n\nPlease try again, that was not a correct option.\n");
	
		static const string CLR_SCR;

	private:
		int precision;
		vector<char> componetOrdering;
		vector <string> text;
	        struct option {
			string text;
			string identifier;
		};
		vector<option> options;
};

#endif //_MENU_H_
