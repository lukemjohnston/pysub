
#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stack>

typedef std::map<std::string, std::string> symbolTableType;

class expEvalulator
{
private:
	symbolTableType symbolTable;

public:
	void evaluateMain(std::string programCode);
	bool validExp(std::string programCode);
	void convertPost(std::string programCode);
	void clearTable();
	bool precedenceCheck(std::string infix);
	void evaluatePost();
	void storeTable(std::string variable, std::string value);
	std::string retrieveValue(std::string variable);
	void displayTable();
	
};

#endif
