#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H

#include "interface.h"
#include "lexanalyzer.h"

#include <vector>
#include <string>
#include <stack>
#include <map>

using namespace std;

class Interface;
class LexicalAnalyzer;

class ExpressionEvaluator
{
private:
	
	typedef map<string, string> symbolTableType;
	symbolTableType symbolTable;

public:
	ExpressionEvaluator() = default;

	void infixToPostfix(LexicalAnalyzer lexanalysis);
	bool checkPar(vector<vector<pair<string, categoryType>>> equationtokenInfo);
	void PostfixtoAnswer(LexicalAnalyzer lexanalysis);
	bool checkExpression(LexicalAnalyzer lexanalysis);
	bool isOperator(LexicalAnalyzer lexanalysis, int e);
	pair<string, categoryType> whichOp(LexicalAnalyzer lexanalysis, int e, double operand1, double operand2);
	bool isOperatorGus(LexicalAnalyzer lexanalysis, pair<string, categoryType>);
	void storeSymbolTable(string a, string b);
	void findSymbolTableElement();
	int findOperatorPrecedence(LexicalAnalyzer lexanalysis);
	void clearSymbolTable();

	friend class Interface;
	friend class LexicalAnalyzer;
};

#endif


