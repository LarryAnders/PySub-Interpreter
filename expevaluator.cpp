#include <iostream>
#include <stack>
#include "expevaluator.h"
#include "lexanalyzer.h"
#include <string.h>

using namespace std;



void ExpressionEvaluator::infixToPostfix(LexicalAnalyzer lexanalysis)
{
	if (checkPar(lexanalysis.equationtokenInfo) == false)
	{
		cout << "The input equation does not have balanced parentheses, please correct this and re-enter"
			<< "\n equation.\n\n";
		return;
	}

	else if (checkExpression(lexanalysis) == false)
	{
		cout << "This equation contains unknown characters. Please remove them ansd re-enter equation.\n\n";
		return;
	}

	else
	{
		for (int j = 0; j < lexanalysis.equationtokenInfo[0].size(); j++)
		{
			if (lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) == "NUMERIC_LITERAL")
			{
				//cout << " This is a number\n\n";
				lexanalysis.postfixVect.push_back(lexanalysis.equationtokenInfo[0][j]);
			}

			else if (lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) == "LEFT_PAREN")
			{
				lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
			}

			else if (lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) == "RIGHT_PAREN")
			{
				while (lexanalysis.tempstack.top().first != "(")
				{
					lexanalysis.postfixVect.push_back(lexanalysis.tempstack.top());
					lexanalysis.tempstack.pop();
				}
				lexanalysis.tempstack.pop();
			}

			else if (lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) == "ARITH_OP"
				|| lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) == "LOGICAL_OP"
				|| lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) == "RELATIONAL_OP")
			{
				if (!lexanalysis.tempstack.empty() && lexanalysis.tempstack.top().first != "(")
				{

					if (lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) == "LOGICAL_OP")
					{
						if (lexanalysis.equationtokenInfo[0][j].first == "or")
						{
							lexanalysis.postfixVect.push_back(lexanalysis.tempstack.top());
							lexanalysis.tempstack.pop();
							lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
						}

						else if (lexanalysis.equationtokenInfo[0][j].first == "and")
						{
							if (lexanalysis.tempstack.top().first != "or")
							{
								lexanalysis.postfixVect.push_back(lexanalysis.tempstack.top());
								lexanalysis.tempstack.pop();
								lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
							}
							else
							{
								lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
							}
						}

						else if (lexanalysis.equationtokenInfo[0][j].first == "not")
						{
							if (lexanalysis.tempstack.top().first != "and" || lexanalysis.tempstack.top().first != "or")
							{
								lexanalysis.postfixVect.push_back(lexanalysis.tempstack.top());
								lexanalysis.tempstack.pop();
								lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
							}
							else
							{
								lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
							}
						}
					} // logical

					else if (lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) == "ARITH_OP")
					{
						if (lexanalysis.equationtokenInfo[0][j].first == "*" || lexanalysis.equationtokenInfo[0][j].first == "/"
							|| lexanalysis.equationtokenInfo[0][j].first == "%")
						{
							if (lexanalysis.tempstack.top().first == "*" || lexanalysis.tempstack.top().first == "/" || lexanalysis.tempstack.top().first == "%")
							{
								lexanalysis.postfixVect.push_back(lexanalysis.tempstack.top());
								lexanalysis.tempstack.pop();
								lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
							}

							else
							{
								lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
							}
						}

						else if (lexanalysis.equationtokenInfo[0][j].first == "+" || lexanalysis.equationtokenInfo[0][j].first == "-")
						{
							if (lexanalysis.tempstack.top().first == "*" || lexanalysis.tempstack.top().first == "/" || lexanalysis.tempstack.top().first == "%" 
								|| lexanalysis.tempstack.top().first == "+" || lexanalysis.tempstack.top().first == "-")
							{

								lexanalysis.postfixVect.push_back(lexanalysis.tempstack.top());
								lexanalysis.tempstack.pop();
								lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
							}

							else
							{
								lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
							}
						}
					} // arith ops

					else if (lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) == "RELATIONAL_OP")
					{
						if (lexanalysis.tempstack.top().first == "*" || lexanalysis.tempstack.top().first == "/" || lexanalysis.tempstack.top().first == "%" ||
							lexanalysis.tempstack.top().first == "+" || lexanalysis.tempstack.top().first == "-" || lexanalysis.tempstack.top().first == "<" ||
							lexanalysis.tempstack.top().first == "<=" || lexanalysis.tempstack.top().first == ">" || lexanalysis.tempstack.top().first == ">=" 
							|| lexanalysis.tempstack.top().first == "!=" || lexanalysis.tempstack.top().first == "==")
						{
							lexanalysis.postfixVect.push_back(lexanalysis.tempstack.top());
							lexanalysis.tempstack.pop();
							lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
						}

						else
						{
							lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
						}
					}
				} 

				else
				{
					lexanalysis.tempstack.push(lexanalysis.equationtokenInfo[0][j]);
				} //end op check
			}
		}
		while (!lexanalysis.tempstack.empty())
		{
			lexanalysis.postfixVect.push_back(lexanalysis.tempstack.top());
			lexanalysis.tempstack.pop();
		}
	}
	

	PostfixtoAnswer(lexanalysis);
}

bool ExpressionEvaluator::checkPar(vector<vector<pair<string, categoryType>>> equationtokenInfo)
{
	stack<string> checkPar;

	for (int j = 0; j < equationtokenInfo[0].size(); j++)
	{
		if (equationtokenInfo[0][j].first == "(")
		{
			checkPar.push(equationtokenInfo[0][j].first);
		}

		else if (equationtokenInfo[0][j].first == ")")
		{
			if (checkPar.empty() || checkPar.top() != "(")
			{
				return false;
			}
			checkPar.pop();
		}
	}
	if (!checkPar.empty())
	{
		return false;
	}
	return true;
}

void ExpressionEvaluator::PostfixtoAnswer(LexicalAnalyzer lexanalysis)
{
	

	stack<pair<string, categoryType>> gusstack;
	string operand1;
	string operand2;

	for (int i = 0; i < lexanalysis.postfixVect.size(); i++)
	{
		if (lexanalysis.getCategoryString(lexanalysis.postfixVect[i].second) == "NUMERIC_LITERAL")
		{
			gusstack.push(lexanalysis.postfixVect[i]);
		}

		else if (isOperator(lexanalysis, i) == true)
		{
			if (lexanalysis.postfixVect[i].first == "!" || lexanalysis.postfixVect[i].first == "not")
			{
				double op1 = stod(gusstack.top().first);
				op1 = !op1;
				
				
				lexanalysis.temppair.first = to_string(op1);

				
				lexanalysis.temppair.second = categoryType::NUMERIC_LITERAL;

				gusstack.push(lexanalysis.temppair);
			}

			else
			{
				if (!gusstack.empty() && gusstack.size() > 1 && isOperatorGus(lexanalysis, gusstack.top()) == false)
				{
					operand2 = gusstack.top().first;
						gusstack.pop();
						operand1 = gusstack.top().first;
						gusstack.pop();

						double num1 = stod(operand1);
						double num2 = stod(operand2);

						if (whichOp(lexanalysis, i, num1, num2).first != "inf")
						{
							gusstack.push(whichOp(lexanalysis, i, num1, num2));
						}

						else
						{
							cout << "You cannot divide by zero. Please correct your equation and try again.\n\n";
							return;
						}
				}

				else
				{
					cout << "This Lexical Analyzer does not compute this form of unary operations. Only 'not' is supported."
						<< "Please correct your equation and try again.\n\n";
					return;
				}
			}
		}


		
	}
	cout << gusstack.top().first <<"\n\n";
}

bool ExpressionEvaluator::checkExpression(LexicalAnalyzer lexanalysis)
{
	for (int j = 0; j < lexanalysis.equationtokenInfo[0].size(); j++)
	{
		if (lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) != "NUMERIC_LITERAL" 
			&& lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) != "ARITH_OP"
			&& lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) != "LOGICAL_OP"
			&& lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) != "RELATIONAL_OP"
			&& lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) != "INDENT"
			&& lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) != "LEFT_PAREN"
			&& lexanalysis.getCategoryString(lexanalysis.equationtokenInfo[0][j].second) != "RIGHT_PAREN")
		{
			return false;
		}
	}
	return true;
}

bool ExpressionEvaluator::isOperator(LexicalAnalyzer lexanalysis, int e)
{
		return (lexanalysis.getCategoryString(lexanalysis.postfixVect[e].second) == "ARITH_OP" ||
			lexanalysis.getCategoryString(lexanalysis.postfixVect[e].second) == "LOGICAL_OP" ||
			lexanalysis.getCategoryString(lexanalysis.postfixVect[e].second) == "RELATIONAL_OP");
	
}

pair<string, categoryType> ExpressionEvaluator::whichOp(LexicalAnalyzer lexanalysis, int e, double operand1, double operand2)
{
	pair<string, categoryType> answer;
	double temp = 0;

	if (lexanalysis.postfixVect[e].first == "*")
	{
		temp = operand1 * operand2;
		
		answer.first = to_string(temp);
		
		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == "/")
	{

		temp = operand1 / operand2;

		answer.first = to_string(temp);

		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == "%")
	{
		int a = operand1;
		int b = operand2;

		temp = a % b; 

		answer.first = to_string(temp);

		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == "+")
	{
		temp = operand1 + operand2;

		answer.first = to_string(temp);
		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == "-")
	{
		temp = operand1 - operand2;

		answer.first = to_string(temp);

		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == "<")
	{
		temp = operand1 < operand2;

		answer.first = to_string(temp);

		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == "<=")
	{
		temp = operand1 <= operand2;

		answer.first = to_string(temp);

		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == ">")
	{
		temp = operand1 > operand2;

		answer.first = to_string(temp);

		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == ">=")
	{
		temp = operand1 >= operand2;

		answer.first = to_string(temp);

		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == "!=")
	{
		temp = operand1 != operand2;

		answer.first = to_string(temp);

		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == "==")
	{
	temp = operand1 == operand2;

	answer.first = to_string(temp);

		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == "and")
	{
	temp = operand1 and operand2;

	answer.first = to_string(temp);

		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

	else if (lexanalysis.postfixVect[e].first == "or")
	{
	temp = operand1 or operand2;

	answer.first = to_string(temp);

		answer.second = categoryType::NUMERIC_LITERAL;
		return answer;
	}

}

bool ExpressionEvaluator::isOperatorGus(LexicalAnalyzer lexanalysis, pair<string, categoryType> g)
{
	return (lexanalysis.getCategoryString(g.second) == "ARITH_OP" ||
		lexanalysis.getCategoryString(g.second) == "LOGICAL_OP" ||
		lexanalysis.getCategoryString(g.second) == "RELATIONAL_OP");
}

void ExpressionEvaluator::storeSymbolTable(string a, string b)
{

}

void ExpressionEvaluator::findSymbolTableElement()
{

}

int ExpressionEvaluator::findOperatorPrecedence(LexicalAnalyzer lexanalysis)
{
	int x = 0;
	return x;
}

void ExpressionEvaluator::clearSymbolTable()
{
	symbolTable.clear();
}