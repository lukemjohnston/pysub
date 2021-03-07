
#include <iostream>
#include <stack>
#include <sstream> 
#include "expevaluator.h"
using namespace std;


string expToken;
vector<string> infixVect;
vector<string> postfixVect;
stack<string> stackVect;
stack<int> stackEval;
symbolTableType symbolTable;
int finalVal;
int leftPar = 0;
int rightPar = 0;




void expEvalulator::evaluateMain(string programCode)	//evaluate user input
{
	infixVect.clear();
	postfixVect.clear();

	convertPost(programCode);	//convert programCode to postfix
	if (leftPar != rightPar)
	{
		cout << "ERROR: Expression is not a valid expression. Fix parentheses\n\n";
		return;
	}
	/*for (int i = 0; i < postfixVect.size(); i++)
	{
		cout << postfixVect[i];
	} */
	evaluatePost();	//evaluate postfix
	cout << finalVal;	//display final result




}


void expEvalulator::evaluatePost()
{
	int op1 = 0;
	int op2 = 0;
	int op = 0;
	int tempVal = 0;
	bool temp = 0;


	for (size_t i = 0; i < postfixVect.size(); i++)
	{
		if ((postfixVect[i] == "(") || (postfixVect[i] == ")"))
		{
			continue;
		}
		else if ((postfixVect[i] == "+") || (postfixVect[i] == "-") || (postfixVect[i] == "*") || (postfixVect[i] == "/") || (postfixVect[i] == "%") ||
			(postfixVect[i] == "==") || (postfixVect[i] == "<") || (postfixVect[i] == ">") || (postfixVect[i] == ">=") || (postfixVect[i] == "<=") ||
			(postfixVect[i] == "!=") || (postfixVect[i] == "and") || (postfixVect[i] == "or") || (postfixVect[i] == "not"))
		{
			op2 = stackEval.top();
			stackEval.pop();
			op1 = stackEval.top();
			stackEval.pop();
			//cout << "op1:" << op1 << endl << "op2:" << op2 << endl;

			if (postfixVect[i] == "+") {
				tempVal = (op1 + op2);
				//cout << "temp:" << tempVal << endl;
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == "-") {
				tempVal = (op1 - op2);
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == "*") {
				tempVal = (op1 * op2);
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == "/") {
				tempVal = (op1 / op2);
				stackEval.push(tempVal);
			}
			if (postfixVect[i] == "%") {
				tempVal = (op1 % op2);
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == "<") {
				tempVal = (op1 < op2);
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == "<=") {
				tempVal = (op1 <= op2);
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == ">") {
				tempVal = (op1 > op2);
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == ">=") {
				tempVal = (op1 >= op2);
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == "!=") {
				tempVal = (op1 != op2);
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == "==") {
				tempVal = (op1 == op2);
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == "and") {
				tempVal = (op1 && op2);
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == "or") {
				tempVal = (op1 || op2);
				stackEval.push(tempVal);
			}

			if (postfixVect[i] == "not") {
				op = stackEval.top();
				stackEval.pop();
				tempVal = (!op);
				stackEval.push(tempVal);
			}

		}
		else
		{
			int s = 0;
			stringstream tempInt(postfixVect[i]);
			tempInt >> s;
			stackEval.push(s);
			//cout << "post:" << s << endl;
			tempInt.str("");
		}

	}
	finalVal = stackEval.top();
	stackEval.pop();
}

void expEvalulator::convertPost(string programCode)
{
	leftPar = 0;
	rightPar = 0;
	string identifier;
	string value;

	for (size_t i = 0; i < programCode.size(); i++)		//tokenize programCode
	{
		expToken.clear();
		if ((programCode[i] == '=') && (programCode[i + 1] != '='))
		{
			expToken.push_back(programCode[i]);
			infixVect.push_back(expToken);
			//cout << "TOKEN: " << token;
		}
		else if ((programCode[i] == '=') && (programCode[i + 1] == '='))
		{
			expToken.push_back(programCode[i]);
			i++;
			expToken.push_back(programCode[i]);
			infixVect.push_back(expToken);
			//cout << "TOKEN: " << token;
		}
		else if ((programCode[i] == '(') || (programCode[i] == ')') || (programCode[i] == '+') || (programCode[i] == '-')
			|| (programCode[i] == '*') || (programCode[i] == '/') || (programCode[i] == '%'))
		{
			if (programCode[i] == '(')
			{
				leftPar++;
			}
			if (programCode[i] == ')')
			{
				rightPar++;
			}
			expToken.push_back(programCode[i]);
			infixVect.push_back(expToken);
			//cout << "TOKEN: " << expToken;
		}
		else if ((programCode[i] == '<') || (programCode[i] == '>') || (programCode[i] == '!'))
		{
			if (programCode[i + 1] == '=')
			{
				expToken.push_back(programCode[i]);
				i++;
				expToken.push_back(programCode[i]);
			}
			else
				expToken.push_back(programCode[i]);

			infixVect.push_back(expToken);
			//cout << "TOKEN: " << token;
		}
		else if ((programCode[i] == 'a') || (programCode[i] == 'A'))		//token "and"
		{
			if ((programCode[i + 1] == 'n') && (programCode[i + 2] == 'd'))
			{
				for (int j = 0; j < 3; j++)
				{
					expToken.push_back(programCode[i]);
					i++;
				}
				infixVect.push_back(expToken);
				//cout << "TOKEN: " << token;
			}
		}
		else if ((programCode[i] == 'o') || (programCode[i] == 'O'))		//token "or"
		{
			if (programCode[i + 1] == 'r')
			{
				for (int j = 0; j < 2; j++)
				{
					expToken.push_back(programCode[i]);
					i++;
				}
				infixVect.push_back(expToken);
				//cout << "TOKEN: " << token;
			}
		}
		else if ((programCode[i] == 'n') || (programCode[i] == 'N'))		//token "not"
		{
			if ((programCode[i + 1] == 'o') && (programCode[i + 2] == 't'))
			{
				for (int j = 0; j < 3; j++)
				{
					expToken.push_back(programCode[i]);
					i++;
				}
				infixVect.push_back(expToken);
				//cout << "TOKEN: " << token;
			}
		}
		else if ((programCode[i] == '0') || (programCode[i] == '1') || (programCode[i] == '2') || (programCode[i] == '3') || (programCode[i] == '4')		//search programCode for NUMERIC_LITERAL
			|| (programCode[i] == '5') || (programCode[i] == '6') || (programCode[i] == '7') || (programCode[i] == '8') || (programCode[i] == '9'))
		{
			expToken.push_back(programCode[i]);
			while ((programCode[i + 1] == '0') || (programCode[i + 1] == '1') || (programCode[i + 1] == '2') || (programCode[i + 1] == '3') || (programCode[i + 1] == '4')
				|| (programCode[i + 1] == '5') || (programCode[i + 1] == '6') || (programCode[i + 1] == '7') || (programCode[i + 1] == '8') || (programCode[i + 1] == '9'))
			{
				i++;
				expToken.push_back(programCode[i]);
			}
			infixVect.push_back(expToken);
			//cout << "TOKEN: " << token;
		}
		else if (programCode[i] == ' ')
		{
			continue;
		}
		else if (isalpha(programCode[i])) {		//INDENTIFIER
			identifier.push_back(programCode[i]);
			while (isalpha(programCode[i + 1])) {
				i++;
				identifier.push_back(programCode[i]);
			}


			map<string, string>::iterator temp = symbolTable.find(identifier);
			if (temp != symbolTable.end()) {					//check if key is found in map
				string value = retrieveValue(identifier);
				infixVect.push_back(value);
			}
			else {

				cout << endl << "ERROR: identidier is not found\n" << "*****TERMINATING PROGRAM*****\n";
				exit(1);
			}
			//cout << "ident: " << identifier << "  value: " << value << endl;
		}
		//cout << "TOKEN: " << expToken;
	}


	for (size_t i = 0; i < infixVect.size(); i++)		//convert tokens to postfix
	{
		if (infixVect[i] == "(")
		{
			//cout << "(";
			stackVect.push(infixVect[i]);	//move '(' to stack

		}
		else if (infixVect[i] == ")")
		{
			if (stackVect.top() != "(")
			{
				if (leftPar != rightPar)
				{
					return;
				}
				else
				{
					postfixVect.push_back(stackVect.top());		//move stack over to postifix until '(' is encountered
					stackVect.pop();
				}
			}
			else if (stackVect.top() == "(")
			{
				stackVect.pop();
			}
		}
		else if ((infixVect[i] == "+") || (infixVect[i] == "-") || (infixVect[i] == "*") || (infixVect[i] == "/") || (infixVect[i] == "%") || (infixVect[i] == "=")
			|| (infixVect[i] == "==") || (infixVect[i] == "<") || (infixVect[i] == ">") || (infixVect[i] == ">=") || (infixVect[i] == "<=") || (infixVect[i] == "!=")
			|| (infixVect[i] == "and") || (infixVect[i] == "or") || (infixVect[i] == "not"))
		{
			//string infixtemp(1, infixVect[i]);
			while ((!stackVect.empty()) && (stackVect.top() != "(") && (precedenceCheck(infixVect[i]) == true))
			{

				postfixVect.push_back(stackVect.top());
				stackVect.pop();

			}
			stackVect.push(infixVect[i]);
			//cout << "stack push";
		}
		else
		{
			postfixVect.push_back(infixVect[i]);
		}
	}

	while (!stackVect.empty())
	{
		if ((stackVect.top() == "(") || (stackVect.top() == ")"))
		{
			stackVect.pop();
		}
		else
		{
			//cout << "stack popped";
			postfixVect.push_back(stackVect.top());
			stackVect.pop();
		}

	}


}

bool expEvalulator::precedenceCheck(string infix)
{
	int infixVal = 0;
	int stackVal = 0;

	if ((infix == "*") || (infix == "/") || (infix == "%"))		//infix precedence
		infixVal = 5;
	if ((infix == "+") || (infix == "-"))
		infixVal = 4;
	if ((infix == "=") || (infix == "!") || (infix == "<") || (infix == ">"))
		infixVal = 3;
	if (infix == "not")
		infixVal = 2;
	if (infix == "and")
		infixVal = 1;
	if (infix == "or")
		infixVal = 0;

	if ((stackVect.top() == "*") || (stackVect.top() == "/") || (stackVect.top() == "%"))		//stack precedence
		stackVal = 5;
	if ((stackVect.top() == "+") || (stackVect.top() == "-"))
		stackVal = 4;
	if ((stackVect.top() == "=") || (stackVect.top() == "==") || (stackVect.top() == "<") || (stackVect.top() == ">") ||
		(stackVect.top() == "<=") || (stackVect.top() == ">=") || (stackVect.top() == "!="))
		stackVal = 3;
	if (stackVect.top() == "not")
		stackVal = 2;
	if (stackVect.top() == "and")
		stackVal = 1;
	if (stackVect.top() == "or")
		stackVal = 0;

	if (stackVal < infixVal)
	{
		cout << "false";
		return 0;
	}
	else
	{
		cout << "true";
		return 1;
	}

}

bool expEvalulator::validExp(string programCode)	//check the expression is valid
{
	for (size_t i = 0; i < programCode.size(); i++)
	{
		if ((programCode[i] == '=') || (programCode[i] == '(') || (programCode[i] == ')') || (programCode[i] == '+') || (programCode[i] == '-') ||
			(programCode[i] == '/') || (programCode[i] == '*') || (programCode[i] == '%') || (programCode[i] == ' ') || (programCode[i] == '<') ||
			(programCode[i] == '>') || (programCode[i] == '!') || (programCode[i] == '0') || (programCode[i] == '1') || (programCode[i] == '2') ||
			(programCode[i] == '3') || (programCode[i] == '4') || (programCode[i] == '5') || (programCode[i] == '6') || (programCode[i] == '7') ||
			(programCode[i] == '8') || (programCode[i] == '9'))
		{
		}
		else if ((programCode[i] == 'a') || (programCode[i] == 'n') || (programCode[i] == 'd') || (programCode[i] == 'o') ||
			(programCode[i] == 'r') || (programCode[i] == 't'))
		{
		}
		else
		{
			return false;
		}

	}
	return true;
}

void expEvalulator::storeTable(string variable, string value)
{
	//cout << "Var2: " << variable << "    Value2: " << value << endl;

	symbolTable.insert(make_pair(variable, value));
	return;
}

string expEvalulator::retrieveValue(string variable)
{
	string value;

	value = symbolTable.find(variable)->second;
	//cout << value;

	return value;
}

void expEvalulator::displayTable() {
	cout << "****** Symbol Table Variables and Values ******\n";

	for (auto i = symbolTable.begin(); i != symbolTable.end(); i++) {

		cout << i->first << " = " << i->second << endl;
	}

	return;
}


void expEvalulator::clearTable()	//clear symbolTable
{
	symbolTable.clear();
}