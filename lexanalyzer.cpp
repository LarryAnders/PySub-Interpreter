#include <iostream>
#include <cctype>
#include "lexanalyzer.h"
#include "expevaluator.h"
#include "interface.h"

using namespace std;


void LexicalAnalyzer::makeTokenLineType(Interface::programType programCode)
{
	if (!programCode.empty())
	{
		if (tokenInfo.empty())
		{
			for (int i = 0; i < programCode.size(); i++)
			{
				tokenInfo.push_back(readProgram(programCode, i));
			}
		}
			cout << "\t\t\t*****TOKEN INFORMATION*****\n";
			for (int i = 0; i < tokenInfo.size(); i++)
			{

				cout << "Line #" << i << ":\n";

				for (int j = 0; j < tokenInfo[i].size(); j++)
				{
					cout << "Token[" << j << "]:\t";
					cout << tokenInfo[i][j].first << "\t\t - \t\t";
					cout << getCategoryString(tokenInfo[i][j].second) << "\n";
				}

				cout << "-----------------------------------------------------------------------------\n";
			}
		
	}
	else
		cout << "Please read a file to display its tokens\n";
}

void LexicalAnalyzer::makeTokenLineTypeEquation(Interface::EquationType equationString)
{
	if (!equationString.empty())
	{
		if (equationtokenInfo.empty())
		{
			for (int i = 0; i < equationString.size(); i++)
			{
				equationtokenInfo.push_back(readProgram(equationString, i));
			}
		}
		//cout << "\t\t\t*****TOKEN INFORMATION*****\n";
		/*for (int i = 0; i < equationtokenInfo.size(); i++)
		{

			cout << "Line #" << i << ":\n";

			for (int j = 0; j < equationtokenInfo[i].size(); j++)
			{
				cout << "Token[" << j << "]:\t";
				cout << equationtokenInfo[i][j].first << "\t\t - \t\t";
				cout << getCategoryString(equationtokenInfo[i][j].second) << "\n";
			}

			cout << "-----------------------------------------------------------------------------\n";
		}*/
	}
	//ExpressionEvaluator* equation = new ExpressionEvaluator;
	//equation->infixtoPostfix(equationtokenInfo);

}

LexicalAnalyzer::tokenLineType LexicalAnalyzer::readProgram(Interface::programType programCode, int lineNumber)
{
	//cout << "Inside readProgram!\n\n";

	tokenLineType vectorOfTokenPairs;

	int i = lineNumber;

	for (int j = 0; j < programCode[i].size(); j++) //Reads a character in specific line in programCode vector.
	{
		//cout << "loop restarted\n";

		char c = programCode[i][j];
		//cout << i << "\n";
		//cout << "make j value is = " << programCode[i].size() << "\n";
		//if c is a digit, collect numeric literal as long as you read digits
		if (isdigit(c))
		{
			//cout << " found a digit \n";
			token.push_back(c);

			while (isdigit(programCode[i][j + 1]))
			{
				token.push_back(programCode[i][j + 1]);
				j++;
			}

			vectorOfTokenPairs.push_back(make_pair(token, categoryType::NUMERIC_LITERAL)); //insert digit(s) and categoryType into pair
			token.clear();
			//continue;
		}

		//if c is a letter, collect an identifier as long as you read alphabetic characters(also check for keywords and Logical operators)
		else if (isalpha(c))
		{
			//cout << " found an identifier\n";
			token.push_back(c);

			while (isalpha(programCode[i][j + 1]))
			{
				token.push_back(programCode[i][j + 1]);
				j++;
			}

			if (checkKeyword(token) == true)
			{
				//cout << "Letter was apart of a keyword \n";
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::KEYWORD));
			}
			else if (checkLogicalOp(token) == true)
			{
				//cout << "Letter was apart of a logical op\n";
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::LOGICAL_OP));
			}
			else
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::IDENTIFIER));

			token.clear();
			//continue;
		}


		//if c is a single or double quote, collect a string literal as long as you read characters other than a single or double quote

		else if (c == '"' || c == '\'')
		{
			//cout << " found a quote mark\n";
			token.push_back(c);

			if (c == '"')
			{
				while (programCode[i][j + 1] != '"')
				{
					token.push_back(programCode[i][j + 1]);
					j++;
					//cout << "j is currently = " << j << "\n";
				}
				token.push_back(programCode[i][j + 1]);
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::STRING_LITERAL));
				token.clear();
				j++;
				//continue;
			}

			else if (c == '\'')
			{
				while (programCode[i][j + 1] != '\'')
				{
					token.push_back(programCode[i][j + 1]);
					j++;
				}
				token.push_back(programCode[i][j + 1]);
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::STRING_LITERAL));
				token.clear();
				j++;
				//continue;
			}

		}

		//if c is #, collect comment to end of line

		else if (c == '#')
		{
			//cout << " found a comment\n";
			//token.push_back(c);

			for (string::iterator itr = (programCode[i].begin() + j); itr != programCode[i].end(); ++itr)
			{
				token.push_back(*itr);
				j++;
			}
			vectorOfTokenPairs.push_back(make_pair(token, categoryType::COMMENT));
			token.clear();
			//continue;
		}

		//if c is space character(i.e.space or tab), ignore it and read next character unless it is the beginning of the line, then store as INDENT

		else if (isspace(c))
		{
			//cout << "This is j currently = " << j << "\n";
			if (j != 0)
			{
				//cout << "Found a space \n";
				continue;
			}
			else
			{
				token.push_back(c);
				while (isspace(programCode[i][j + 1]))
				{

					j++;
					token.push_back(programCode[i][j]);

				}
				//	cout << "Found an indent\n";
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::INDENT));
				token.clear();
				continue;

			}
		}

		//if c is an operator, identify whether it is an Assignment, Relational, or Arithmetic operator

		else if (c == '=')
		{
			//cout << " found a equal sign\n";
			token.push_back(c);

			if (programCode[i][j + 1] == '=')
			{
				token.push_back(programCode[i][j + 1]);
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::RELATIONAL_OP));
				//cout << "was apart of a relational op\n";
				j++;
			}
			else
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::ASSIGNMENT_OP));
			token.clear();
		}

		else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
		{
			//cout << "found an arith op\n";
			token.push_back(c);
			if (c == '*' && programCode[i][j + 1] == '*')
			{
				token.push_back(programCode[i][j + 1]);
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::ARITH_OP));
				j++;
			}
			else
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::ARITH_OP));
			token.clear();
		}

		else if (c == '<' || c == '>' || c == '!')
		{
			//cout << "Found a relational op\n";
			token.push_back(c);

			if (programCode[i][j + 1] == '=')
			{
				token.push_back(programCode[i][j + 1]);
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::RELATIONAL_OP));
				j++;
			}
			else if (c != '!')
			{
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::RELATIONAL_OP));
			}
			else
				vectorOfTokenPairs.push_back(make_pair(token, categoryType::UNKNOWN));
			token.clear();
		}

		else if (c == '(')
		{
			//cout << "Found a open par\n";
			token.push_back(c);
			vectorOfTokenPairs.push_back(make_pair(token, categoryType::LEFT_PAREN));
			token.clear();
		}

		else if (c == ')')
		{
			//	cout << "Found a close par\n";
			token.push_back(c);
			vectorOfTokenPairs.push_back(make_pair(token, categoryType::RIGHT_PAREN));
			token.clear();
		}

		else if (c == ',')
		{
			//cout << "Found a comma\n";
			token.push_back(c);
			vectorOfTokenPairs.push_back(make_pair(token, categoryType::COMMA));
			token.clear();
		}

		else if (c == ':')
		{
			//cout << "Found a colon\n";
			token.push_back(c);
			vectorOfTokenPairs.push_back(make_pair(token, categoryType::COLON));
			token.clear();
		}

		//Otherwise, classify as UNKNOWN
		else
		{
			//cout << "found an UNKOWN \n";
			vectorOfTokenPairs.push_back(make_pair(token, categoryType::UNKNOWN));
			token.clear();
		}

	
	}

	return vectorOfTokenPairs;
}

bool LexicalAnalyzer::checkKeyword(string token)
{
	vector<string> keywords = { "print", "if", "elif", "else", "while", "int", "input"};
	for (string word : keywords)
	{
		if (token == word)
			return true;
	}

	return false;
}

bool LexicalAnalyzer::checkLogicalOp(string token)
{
	vector<string> operators = { "and", "or", "not" };
	for (string oper : operators)
	{
		if (token == oper)
			return true;
	}

	return false;

}

string LexicalAnalyzer::getCategoryString(categoryType e)
{
	if (e == categoryType::KEYWORD) { return "KEYWORD"; }
	else if (e == categoryType::IDENTIFIER) { return "INDENTIFIER"; }
	else if (e == categoryType::STRING_LITERAL) { return "STRING_LITERAL"; }
	else if (e == categoryType::NUMERIC_LITERAL) { return "NUMERIC_LITERAL"; }
	else if (e == categoryType::ASSIGNMENT_OP) { return "ASSIGNMENT_OP"; }
	else if (e == categoryType::ARITH_OP) { return "ARITH_OP"; }
	else if (e == categoryType:: LOGICAL_OP) { return "LOGICAL_OP"; }
	else if (e == categoryType:: RELATIONAL_OP) { return "RELATIONAL_OP"; }
	else if (e == categoryType::LEFT_PAREN) { return "LEFT_PAREN"; }
	else if (e == categoryType::RIGHT_PAREN) { return "RIGHT_PAREN"; }
	else if (e == categoryType::COLON) { return "COLON"; }
	else if (e == categoryType::COMMA) { return "COMMA"; }
	else if (e == categoryType::COMMENT) { return "COMMENT"; }
	else if (e == categoryType::INDENT) { return "INDENT"; }
	else { return "UNKOWN"; }
}


void LexicalAnalyzer::clearTokens()
{
	//for (int i = 0; i < tokenInfo.size(); i++)
	//{

	//	for (int j = 0; j < tokenInfo[i].size(); j++)
	//	{
	//		
	//		tokenInfo[i][j].second = {};
	//		tokenInfo[i][j].first = {};
	//	}
	//}
	
	tokenInfo = {};
	tokenInfo.clear();
	

}

void LexicalAnalyzer::sendEquationData()
{
	ExpressionEvaluator* equation = new ExpressionEvaluator();
	//equation->infixtoPostfix(equationtokenInfo);
	//tokenType equationtokenInfo
}