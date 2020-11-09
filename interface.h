
#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "lexanalyzer.h"
//#include "expevaluator.h"
#include "interpreter.h"

using std::string;
typedef std::vector<std::string> programType;


class Interface
{
private:
	programType programCode;

public:
	void startInterface();
	void helpInterface(string command);
	//void readFile(string filename);
	void readProgram(lexicalAnalyzer& lexAnalysis, string filename);
	bool runLexer(lexicalAnalyzer& lexAnalysis);
	void clearCode();
	void showCode();
	

};

#endif