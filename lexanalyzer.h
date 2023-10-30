#ifndef LEXANALYZER_H
#define LEXANALYZER_H
#include "interface.h"
//#include "expevaluator.h"
#include <string>
#include <vector>
#include <utility>
#include <stack>

class Interface;
class ExpressionEvaluator;

enum class categoryType
{
    KEYWORD,
    IDENTIFIER,
    STRING_LITERAL,
    NUMERIC_LITERAL,
    ASSIGNMENT_OP,
    ARITH_OP,
    LOGICAL_OP,
    RELATIONAL_OP,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COMMA,
    COMMENT,
    INDENT,
    UNKNOWN
};


class LexicalAnalyzer
{
private:

    typedef vector<vector<pair<string, categoryType>>> tokenType;
    typedef vector<pair<string, categoryType>> tokenLineType;
    typedef pair<string, categoryType> pairType;

    tokenType tokenInfo;
    tokenType equationtokenInfo;
    tokenLineType postfixVect;
    stack <pair<string, categoryType>> tempstack;
    string token;
    int ignore;
    pair<string, categoryType> temppair;
    
public:
    LexicalAnalyzer() = default;
    

    tokenLineType readProgram(Interface::programType programCode, int lineNumber);

    bool checkKeyword(string token);
    bool checkLogicalOp(string token);
    void makeTokenLineType(Interface::programType programCode);
    void makeTokenLineTypeEquation(Interface::EquationType equationString);
    string getCategoryString(categoryType);
    void clearTokens();
    void sendEquationData();

    friend class Interface;
    friend class ExpressionEvaluator;
};

#endif // !LEXANALYZER_H
