
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "interpreter.h"
using namespace std;

expEvalulator expEvaluation;


bool Interpreter::interpretLine(string programCode) {
	vector<char> variable;

	for (int i = 0; i < programCode.size(); i++) {

		if (programCode[i] == '#') {	//comment
			return 1;
		}

		if ((programCode[i] == 'p') || (programCode[i] == 'P')) {	//search programCode for KEYWORD print

			if ((programCode[i + 1] == 'r') && (programCode[i + 2] == 'i') && (programCode[i + 3] == 'n') && (programCode[i + 4] == 't')) {
				print(programCode);
				return 1;
			}
		}

		if (isalpha(programCode[i])) {		//variables
			while (programCode[i] != '=') {
				variable.push_back(programCode[i]);		//store variable
				i++;
			}
			assign(variable, programCode);	//assign variable a value
			return 1;
		}

	}
	return 1;
}


void Interpreter::assign(vector<char> variable, string programCode) {	//assign variable and its value
	string value;
	int val = 0;
	bool stop = false;
	for (int i = 0; !stop && i < programCode.size(); i++) {

		if (programCode[i] == '=') {
			while (i < programCode.size()) {
				if (isdigit(programCode[i])) {
					while (isdigit(programCode[i])) {
						value.push_back(programCode[i]);	//store identifer value
						i++;
					}
					continue;
				}
				
				if ((programCode[i] == 'i') || (programCode[i + 1] == 'n') || (programCode[i + 2] == 'p') && (programCode[i + 3] == 'u') && (programCode[i + 4] == 't')) {  //input indentifer value from user
					while (i < programCode.size())
					{
						if (programCode[i] == '"') {
							i++;
							
							while (programCode[i] != '"') {
								cout << programCode[i];
								i++;
							}
							cout << " ";
							getline(cin, value);
							stop = true;
								
						}

						i++;
					}
				}

				i++;
			}
				
		}
	}

	string var(variable.begin(), variable.end());
	//cout << "Var: " << var << "    Value: " << value << endl;

	expEvaluation.storeTable(var, value);	//store variable and value in map
	
}


void Interpreter::print(string programCode) {	//print function
	int i = 0;
	char x = '\'';

	for (i; i < programCode.size(); i++) {
		i + 5; // skip keyword print

		if (programCode[i] == '"') {	//print statement "
			i++;
			while (programCode[i] != '"') {
				cout << programCode[i];
				i++;
			}
		}

		if (programCode[i] == x) {		//print statement '
			i++;
			while (programCode[i] != x) {
				cout << programCode[i];
				i++;
			}
		}

		if (programCode[i] == ',') {
			if (programCode[i] == ',') {	
				i++;
				cout << " ";	//add space between two print statements
	
				if (isalpha(programCode[i])) {
					string temp;
					while (programCode[i] != ')') {

						temp.push_back(programCode[i]);		//store identifier
						i++;
					}
					//cout << "temp: " << temp << endl;
					expEvaluation.evaluateMain(temp);	//find identifier and evaluate
				}
			}
		}
	}

	cout << endl;
}

void Interpreter::showVariables() {

	expEvaluation.displayTable();	//display stored variables and values in map
}

void Interpreter::clear() {

	expEvaluation.clearTable();		//clear map
}

void Interpreter::evaluate(string programCode) {

	expEvaluation.evaluateMain(programCode);	//evaluate equations
}