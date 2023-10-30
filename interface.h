#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <string>


using namespace std;



class Interface
{
private:
	
	typedef vector<string> programType;
	typedef vector<string> EquationType;

	programType programCode;
	EquationType equationString;



public:
	Interface() = default;
	
//	Class Functions
	
	void startInterface();
	void readFile(string choice);
	void show();
	void mapMenu();
	void clear();
	void help(string choice);
	//void displayTokens(LexicalAnalyzer lexAnalysis);
	//void readProgram(LexicalAnalyzer& lexAnalysis,programType programCode);

	friend class LexicalAnalyzer;
	friend class ExpressionEvaluator;
};

#endif
