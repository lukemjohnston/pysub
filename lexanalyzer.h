
#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>


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

typedef std::vector<std::vector<std::pair<std::string, categoryType>>> tokenType;
typedef std::vector<std::pair<std::string, categoryType>> tokenLineType;
typedef std::pair<std::string, categoryType> pairType;


class lexicalAnalyzer
{
private:
    tokenType tokenInfo;
public:
    void genTokens(std::string programCode);
    void showTokens();
    void getCategory(categoryType);
    void clearTokens();

};



#endif

