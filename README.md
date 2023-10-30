# PySub-Interpreter
An interpreter for a subset of the Python programming language to C++.
The interpreter also calculates mathmatical expressions that are input into the terminal.

This program allows for the following commands:

**help or help(<command>)**
When no parameter is given, then “help” or “help()” will enter the help utility.  When in the help utility, the prompt will be “help>” instead of “>>>”.  The following are the commands that can be entered at the “help>” prompt:

**read(filename.py)**
Clears any lines that are stored in the program data structure, and then reads program lines from the python file given as a parameter (<filename.py>) and stores the lines into the program data structure.

**show or show()**
Shows the lines of the program that are stored in program data structure.  Include line number when displaying each line of code in the program

**show(tokens)**
Generates token and category pairs for each line of code and stores the data into the tokenInfo data structure. The token and category pairs are then displayed to the terminal. The possible category types for a token are:	
  KEYWORD
	IDENTIFIER
	STRING_LITERAL
	NUMERIC_LITERAL
	ASSIGNMENT_OP
	ARITH_OP
	LOGICAL_OP
	RELATIONAL_OP
  LEFT_PAREN
	RIGHT_PAREN
	COLON
	COMMA
	COMMENT
	INDENT
	UNKNOWN

**clear or clear()**
Clears out or deletes any lines that are stored in the program data structure

**quit or quit()**
Exits the interpreter interface

**exit**
Exits the help utility

The Pysub Interpreter also calculates expressions that are input directly into the terminal. It does so by converting the expression from infix to postfix and then evaluating the postfix expression.

