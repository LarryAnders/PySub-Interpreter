#include <iostream>
#include <fstream>
#include "interface.h"
#include <vector>
#include <string>
#include <map>
#include "lexanalyzer.h"
#include <ctype.h>
#include "expevaluator.h"

using namespace std;


//Function to show main menu interface
void Interface::startInterface()
{
	cout << "PySUB Interpreter 1.0 on Windows (September 2023)\n";
	cout << "Enter program lines or read(<filename>.py) at command line interface\n";
	cout << "Type 'help' for more information or 'quit' to exit\n\n";
	

	
	LexicalAnalyzer lexAnalysis;
	ExpressionEvaluator expressionEvaluation;
	mapMenu();
	

}

//Function to hold possible menu choices and maps to their respective functions
void Interface::mapMenu()
{
	
	
	string choice;
	
	bool menuLoop = true;

	//getline(cin, choice);
	

	map<string, char> menuOptions;


	menuOptions["quit"] = 'a';
	menuOptions["quit()"] = 'a';
	menuOptions["help"] = 'b';
	menuOptions["help()"] = 'b';
	menuOptions["help(exit)"] = 'b';
	menuOptions["help(quit)"] = 'b';
	menuOptions["help(help)"] = 'b';
	menuOptions["help(read)"] = 'b';
	menuOptions["help(show)"] = 'b';
	menuOptions["help(clear)"] = 'b';
	menuOptions["help(commands)"] = 'b';
	menuOptions["show"] = 'c';
	menuOptions["show()"] = 'c';
	menuOptions["clear"] = 'd';
	menuOptions["clear()"] = 'd';
	menuOptions["show(tokens)"] = 'e';

	
	do
	{
		ExpressionEvaluator* equation = new ExpressionEvaluator();
		//LexicalAnalyzer* lexAnalysis = new LexicalAnalyzer();
		LexicalAnalyzer lexAnalysis;
		ExpressionEvaluator expressionEvaluation;
		char switchChar = 'z';
		cout << ">>>";
		getline(cin, choice);
		menuLoop = true;
		auto checkInput = menuOptions.find(choice);
		if (checkInput != menuOptions.end())
		{
			switchChar = menuOptions.find(choice)->second;

		}

		if (isalpha(choice[0]) == 0 || choice.compare(0, 3, "not") == 0 || choice.compare(0, 3, "and") == 0 || choice.compare(0, 2, "or") == 0)
		{
			switchChar = 'y';
		}


		switch (switchChar) {
		case 'a':
			menuLoop = false;
			break;

		case 'b':
			help(choice);
			break;
		case 'c':
			show();
			break;

		case 'd':
			clear();
			expressionEvaluation.clearSymbolTable();
			break;
		case 'e':

			lexAnalysis.makeTokenLineType(programCode);

			break;
		case 'z':
			readFile(choice);

			checkInput = menuOptions.find(choice);
			if (checkInput != menuOptions.end())
			{
				break;
				//switchChar = menuOptions.find(choice)->second;

			}
			break;

		case 'y':
			equationString.push_back(choice);

				//cout << "Bananas 2 \n\n";
				lexAnalysis.makeTokenLineTypeEquation(equationString);
				//cout << "Bananas 3 \n\n";

				
				
				equation->infixToPostfix(lexAnalysis);
				
				

				equationString.clear();
				
			break;
		}
	
	} while (menuLoop != false);

}

// Function to hold possible menu options while in help utility
void Interface::help(string choice)
{
	//string choice;
	char switchChar = 'z';
	map<string, char> parameter;
	bool menuLooper = true;

	
	
	parameter["help(exit)"] = 'a';
	parameter["help"] = 'b';
	parameter["help(help)"] = 'b';
	parameter["help()"] = 'b';
	parameter["read"] = 'c';
	parameter["help(read)"] = 'c';
	parameter["read()"] = 'c';
	parameter["show"] = 'd';
	parameter["help(show)"] = 'd';
	parameter["show()"] = 'd';
	parameter["clear"] = 'e';
	parameter["help(clear)"] = 'e';
	parameter["clear()"] = 'e';
	parameter["commands"] = 'f';
	parameter["help(commands)"] = 'f';
	parameter["quit"] = 'g';
	parameter["help(quit)"] = 'g';
	parameter["quit()"] = 'g';
	parameter["exit"] = 'h';
	
	

	// while loop restart menu as long as user desires
	while(menuLooper != false)
	{
		
			//checks to see if user input is a valid menu option
			//If valid, converts input to switch case char
			auto checkInput = parameter.find(choice);
			if (checkInput != parameter.end())
			{
				switchChar = parameter.find(choice)->second;
				
			}

			else
			{
				cout << "This input is not valid. Please check input and try again.\n\n";
				switchChar = 'z';
			}
		

		switch (switchChar) {
		case 'a':
			cout << "\nThe 'exit' command exits the help utility.\n\n";
			break;

		case 'b':
			cout << "\nThis command enters help utility. Enter a command to learn its function\n";
			cout << "or enter 'commands' to see a list of possible commands.\n\n";
			cout << "Enter 'exit' to exit help utility.\n\n";
			break;

		case 'c':
			cout << "\nThis command clears any lines that are stored in the program data structure,\n";
			cout << "and then reads program lines from the file given as a parameter (<filename.py>)\n";
			cout << "and stores the lines into the program data structure\n\n";
			break;

		case 'd':
			cout << "\nThis command shows the lines of the program that are stored in program data structure.\n\n";
			break;

		case 'e':
			cout << "\nThis command clears out or deletes any lines that are stored in the program data structure.\n\n";
			break;

		case 'f':
			cout << "\n\nBelow are all possible commands. Enter any command for its description\n\n";
			cout << "clear\thelp\tquit\nread\tshow\n\nNOTE:\tAll commands can be entered as functions:\n\n";
			cout << "\nclear()\thelp()\tquit()\nread()\tshow()\n\n";
			break;

		case 'g':
			cout << "\nThis command exits the interpreter interface\n\n";
			break;

		case 'h':
			menuLooper = false;
			cout << "\n";
			return;
			break;
		
		case 'z':
			break;
		}
		

		if (menuLooper != false)
		{
			cout << "help>";
			getline(cin, choice);
			
		}
	} 
	
}

//Function to open and read data from a file and to into data structure
void Interface::readFile(string choice)
{
	//Checks to see if input likely starts with read(filename.py)
	if (choice.size() > 9 && choice.compare(0, 5, "read(") == 0 && choice.compare(choice.size() - 1, 1, ")") == 0)
	{
		//Following lines removes "read()" from around filename...ex: read(test.py) becomes test.py

		string stripped = choice;

		// Used to cut user input down to file name only
		stripped.erase(0, 5); //Removes first five char from user input "read("
		stripped.erase(stripped.end()-1); //Removes the final parenthesis from user input

		choice = stripped; //stores simplified user input into choice

			
		ifstream file(choice);

		if (file.is_open())
		{
				programCode.clear();
				string line;

				while (getline(file, line))
				{
					programCode.push_back(line);
				}

				return;
		}
		
		else
		{
			cout << "Invalid input. Check command spelling, or file name spelling\n\n";
			return;
		}

	}

	else
	{
		cout << "Invalid input. Check command spelling, or file name spelling\n\n";
		return;
	}
	
}

// Function to show contents of a data structure
void Interface::show()
{
	
	if (!programCode.empty())
	{
		int i = 0;
		for (auto item : programCode) {
			cout << "[" << i <<"]" << " " << item << endl;
			i++;
		}
	}
	else
	{
		cout << "Please read a file before attempting to show it.\n\n";
	}

}

// Function to clear a data structure of its contents
void Interface::clear()
{
	if (!programCode.empty())
	programCode.clear();

	else
		cout << "There is no data to clear\n\n";
}

//void Interface::readProgram(LexicalAnalyzer& lexAnalysis, programType programCode)
//{
//
//}


//void Interface::displayTokens(LexicalAnalyzer lexAnalysis)
//{
//	if (!programCode.empty())
//	{
//		cout << "So far so good!\n\n";
//	}
//	else
//		cout << "No file has been read. Please read a file to display its tokens\n\n";
//	
//}