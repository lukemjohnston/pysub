
#ifndef INTERPRETER_H
#define	INTERPRETER_H

#include <stdint.h>
#include "expevaluator.h"
using namespace std;

class Interpreter
{
private:

public:
	bool interpretLine(std::string programCode);
	void print(std::string programCode);
	void showVariables();
	void assign(std::vector<char> variable, std::string programCode);
	void clear();
	void evaluate(std::string programCode);
};


#endif