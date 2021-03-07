


#include <iostream>
#include <cctype>
#include "lexanalyzer.h"
using namespace std;


tokenLineType lineTokens;
string token;
int line = 0;
int tokenNum = 0;


void lexicalAnalyzer::genTokens(string programCode)		//generate tokens from line of programCode
{
	for (int i = 0; i < programCode.size(); i++)
	{
		token.clear();
		//cout << endl;
		if (programCode[i] == '#')		//search programCode for COMMENT
		{
			for (int i = 0; i < programCode.size(); i++)
			{
				token.push_back(programCode[i]);
			}
			lineTokens.push_back(make_pair(token, categoryType::COMMENT));
			tokenInfo.push_back(lineTokens);
			//cout << "TOKEN: " << token;
			return;
		}

		if ((programCode[i] == '=') && (programCode[i + 1] != '='))		//search programCode for ASSIGNMENT_OP
		{
			token.push_back(programCode[i]);
			lineTokens.push_back(make_pair(token, categoryType::ASSIGNMENT_OP));
			//cout << "TOKEN: " << token;
		}

		if ((programCode[i] == '=') && (programCode[i + 1] == '='))		//search programCode for RELATIONAL_OP ==
		{
			token.push_back(programCode[i]);
			i++;
			token.push_back(programCode[i]);
			lineTokens.push_back(make_pair(token, categoryType::RELATIONAL_OP));
			//cout << "TOKEN: " << token;
		}

		if (programCode[i] == '(')		//search programCode for LEFT_PAREN
		{
			token.push_back(programCode[i]);
			lineTokens.push_back(make_pair(token, categoryType::LEFT_PAREN));
			//cout << "TOKEN: " << token;
		}

		if (programCode[i] == ')')		//search programCode for RIGHT_PAREN
		{
			token.push_back(programCode[i]);
			lineTokens.push_back(make_pair(token, categoryType::RIGHT_PAREN));
			//cout << "TOKEN: " << token;
		}

		if (programCode[i] == ':')		//search programCode for COLON
		{
			token.push_back(programCode[i]);
			lineTokens.push_back(make_pair(token, categoryType::COLON));
			//cout << "TOKEN: " << token;
		}

		if (programCode[i] == ',')		//search programCode for COMMA
		{
			token.push_back(programCode[i]);
			lineTokens.push_back(make_pair(token, categoryType::COMMA));
			//cout << "TOKEN: " << token;
		}

		if (programCode[1] == '	')		//search programCode for INDENT
		{
			token.push_back(programCode[i]);
			lineTokens.push_back(make_pair(token, categoryType::INDENT));
			//cout << "TOKEN: " << token;
		}

		if ((programCode[i] == '+') || (programCode[i] == '-'))		//search programCode for ARITH_OP
		{
			token.push_back(programCode[i]);
			lineTokens.push_back(make_pair(token, categoryType::ARITH_OP));
			//cout << "TOKEN: " << token;
		}

		if ((programCode[i] == '<') || (programCode[i] == '>') || (programCode[i] == '!'))		//search programCode for RELATIONAL_OP
		{
			if (programCode[i + 1] == '=')
			{
				token.push_back(programCode[i]);
				i++;
				token.push_back(programCode[i]);
			}
			else
				token.push_back(programCode[i]);

			lineTokens.push_back(make_pair(token, categoryType::RELATIONAL_OP));
			//cout << "TOKEN: " << token;
		}

		if (programCode[i] == '"')		//search programCode for STRING_LITERAL
		{
			token.push_back(programCode[i]);
			i++;
			while (programCode[i] != '"')
			{
				token.push_back(programCode[i]);
				i++;
			}
			if (programCode[i] == '"') token.push_back(programCode[i]);

			lineTokens.push_back(make_pair(token, categoryType::STRING_LITERAL));
			//cout << "TOKEN: " << token;
		}

		if ((programCode[i] == 'a') || (programCode[i] == 'A'))		//search programCode for LOGICAL_OP and
		{
			if ((programCode[i + 1] == 'n') && (programCode[i + 2] == 'd'))
			{
				for (int j = 0; j < 3; j++)
				{
					token.push_back(programCode[i]);
					i++;
				}
				lineTokens.push_back(make_pair(token, categoryType::LOGICAL_OP));
				//cout << "TOKEN: " << token;
			}
		}

		if ((programCode[i] == 'o') || (programCode[i] == 'O'))		//search programCode for LOGICAL_OP or
		{
			if (programCode[i + 1] == 'r')
			{
				for (int j = 0; j < 2; j++)
				{
					token.push_back(programCode[i]);
					i++;
				}
				lineTokens.push_back(make_pair(token, categoryType::LOGICAL_OP));
				//cout << "TOKEN: " << token;
			}
		}

		if ((programCode[i] == 'n') || (programCode[i] == 'N'))		//search programCode for LOGICAL_OP not
		{
			if ((programCode[i + 1] == 'o') && (programCode[i + 2] == 't'))
			{
				for (int j = 0; j < 3; j++)
				{
					token.push_back(programCode[i]);
					i++;
				}
				lineTokens.push_back(make_pair(token, categoryType::LOGICAL_OP));
				//cout << "TOKEN: " << token;
			}
		}

		if ((programCode[i] == 'p') || (programCode[i] == 'P'))		//search programCode for KEYWORD print
		{
			if ((programCode[i + 1] == 'r') && (programCode[i + 2] == 'i'))
			{
				for (int j = 0; j < 5; j++)
				{
					token.push_back(programCode[i]);
					i++;
				}
				lineTokens.push_back(make_pair(token, categoryType::IDENTIFIER));
				//cout << "TOKEN: " << token;
			}
		}

		if ((programCode[i] == '0') || (programCode[i] == '1') || (programCode[i] == '2') || (programCode[i] == '3') || (programCode[i] == '4')		//search programCode for NUMERIC_LITERAL
			|| (programCode[i] == '5') || (programCode[i] == '6') || (programCode[i] == '7') || (programCode[i] == '8') || (programCode[i] == '9'))
		{
			token.push_back(programCode[i]);
			i++;
			while ((programCode[i] == '0') || (programCode[i] == '1') || (programCode[i] == '2') || (programCode[i] == '3') || (programCode[i] == '4')
				|| (programCode[i] == '5') || (programCode[i] == '6') || (programCode[i] == '7') || (programCode[i] == '8') || (programCode[i] == '9'))
			{
				token.push_back(programCode[i]);
				i++;
			}
			lineTokens.push_back(make_pair(token, categoryType::NUMERIC_LITERAL));
			//cout << "TOKEN: " << token;
		}

		if ((programCode[i] == 'a') || (programCode[i] == 'b') || (programCode[i] == 'c') || (programCode[i] == 'd') || (programCode[i] == 'e')		//search programCode for IDENTIFIER
			|| (programCode[i] == 'f') || (programCode[i] == 'g') || (programCode[i] == 'h') || (programCode[i] == 'i') || (programCode[i] == 'j')
			|| (programCode[i] == 'k') || (programCode[i] == 'l') || (programCode[i] == 'm') || (programCode[i] == 'n') || (programCode[i] == 'o')
			|| (programCode[i] == 'p') || (programCode[i] == 'q') || (programCode[i] == 'r') || (programCode[i] == 's') || (programCode[i] == 't')
			|| (programCode[i] == 'u') || (programCode[i] == 'v') || (programCode[i] == 'w') || (programCode[i] == 'x') || (programCode[i] == 'y') || (programCode[i] == 'z')	//lowercase letters
			|| (programCode[i] == 'A') || (programCode[i] == 'B') || (programCode[i] == 'C') || (programCode[i] == 'D') || (programCode[i] == 'E')
			|| (programCode[i] == 'F') || (programCode[i] == 'G') || (programCode[i] == 'H') || (programCode[i] == 'I') || (programCode[i] == 'J')
			|| (programCode[i] == 'K') || (programCode[i] == 'L') || (programCode[i] == 'M') || (programCode[i] == 'N') || (programCode[i] == 'O')
			|| (programCode[i] == 'P') || (programCode[i] == 'Q') || (programCode[i] == 'R') || (programCode[i] == 'S') || (programCode[i] == 'T')
			|| (programCode[i] == 'U') || (programCode[i] == 'V') || (programCode[i] == 'W') || (programCode[i] == 'X') || (programCode[i] == 'Y') || (programCode[i] == 'Z'))	//uppercase letters
		{
			token.push_back(programCode[i]);
			while ((programCode[i + 1] == 'a') || (programCode[i + 1] == 'b') || (programCode[i + 1] == 'c') || (programCode[i + 1] == 'd') || (programCode[i + 1] == 'e')
				|| (programCode[i + 1] == 'f') || (programCode[i + 1] == 'g') || (programCode[i + 1] == 'h') || (programCode[i + 1] == 'i') || (programCode[i + 1] == 'j')
				|| (programCode[i + 1] == 'k') || (programCode[i + 1] == 'l') || (programCode[i + 1] == 'm') || (programCode[i + 1] == 'n') || (programCode[i + 1] == 'o')
				|| (programCode[i + 1] == 'p') || (programCode[i + 1] == 'q') || (programCode[i + 1] == 'r') || (programCode[i + 1] == 's') || (programCode[i + 1] == 't')
				|| (programCode[i + 1] == 'u') || (programCode[i + 1] == 'v') || (programCode[i + 1] == 'w') || (programCode[i + 1] == 'x') || (programCode[i + 1] == 'y') || (programCode[i] == 'z')	//lowercase letters
				|| (programCode[i + 1] == 'A') || (programCode[i + 1] == 'B') || (programCode[i + 1] == 'C') || (programCode[i + 1] == 'D') || (programCode[i + 1] == 'E')
				|| (programCode[i + 1] == 'F') || (programCode[i + 1] == 'G') || (programCode[i + 1] == 'H') || (programCode[i + 1] == 'I') || (programCode[i + 1] == 'J')
				|| (programCode[i + 1] == 'K') || (programCode[i + 1] == 'L') || (programCode[i + 1] == 'M') || (programCode[i + 1] == 'N') || (programCode[i + 1] == 'O')
				|| (programCode[i + 1] == 'P') || (programCode[i + 1] == 'Q') || (programCode[i + 1] == 'R') || (programCode[i + 1] == 'S') || (programCode[i + 1] == 'T')
				|| (programCode[i + 1] == 'U') || (programCode[i + 1] == 'V') || (programCode[i + 1] == 'W') || (programCode[i + 1] == 'X') || (programCode[i + 1] == 'Y') || (programCode[i] == 'Z'))	//uppercase letters
			{
				i++;
				token.push_back(programCode[i]);
			}
			lineTokens.push_back(make_pair(token, categoryType::IDENTIFIER));
			//cout << "TOKEN: " << token;
		}

	}

	tokenInfo.push_back(lineTokens);
	lineTokens.clear();
}

void lexicalAnalyzer::showTokens()		//display tokens and their categoryType
{
	tokenNum = 0;
	line = 0;
	int n = 0;

	cout << "***** TOKEN INFO *****" << endl;
	for (int i = 0; i < tokenInfo.size(); i++)
	{
		cout << "Line #" << line << endl;
		n = 0;
		for (int j = 0; j < tokenInfo[line].size(); j++)
		{
			if ((line == 1) && (tokenNum == 0))
			{

			}
			else
			{
				cout << "Token[" << n << "]:  " << tokenInfo[line][tokenNum].first << " - ";
				getCategory(tokenInfo[line][tokenNum].second);
				n++;
			}
			tokenNum++;
		}
		cout << "----------------------------------------------------\n";
		tokenNum = 0;
		line++;
	}


}

void lexicalAnalyzer::getCategory(categoryType getCat)	//get categoryType per token
{
	for (int i = 0; i < 1; i++)
	{
		switch (getCat)
		{
		case categoryType::KEYWORD:
			cout << "KEYWORD\n";
			break;

		case categoryType::IDENTIFIER:
			cout << "IDENTIFIER\n";
			break;

		case categoryType::STRING_LITERAL:
			cout << "STRING LITERAL\n";
			break;

		case categoryType::NUMERIC_LITERAL:
			cout << "NUMERIC LITERAL\n";
			break;

		case categoryType::ASSIGNMENT_OP:
			cout << "ASSIGNMENT OP\n";
			break;

		case categoryType::ARITH_OP:
			cout << "ARITHMETIC OP\n";
			break;

		case categoryType::LOGICAL_OP:
			cout << "LOGICAL OP\n";
			break;

		case categoryType::RELATIONAL_OP:
			cout << "RELATIONAL OP\n";
			break;

		case categoryType::LEFT_PAREN:
			cout << "LEFT PARENTHESIS\n";
			break;

		case categoryType::RIGHT_PAREN:
			cout << "RIGHT PARENTHESIS\n";
			break;

		case categoryType::COLON:
			cout << "COLON\n";
			break;

		case categoryType::COMMA:
			cout << "COMMA\n";
			break;

		case categoryType::COMMENT:
			cout << "COMMENT\n";
			break;

		case categoryType::INDENT:
			cout << "INDENT\n";
			break;

		case categoryType::UNKNOWN:
			cout << "UNKNOWN\n";
			break;

		}
	}
}

void lexicalAnalyzer::clearTokens()		//clear stored tokens
{
	tokenInfo.clear();
}


