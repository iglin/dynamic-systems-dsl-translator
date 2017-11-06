//
// Created by root on 10/31/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TRANSLATOR_SYNTAXANALYZER_H
#define DYNAMIC_SYSTEMS_DSL_TRANSLATOR_SYNTAXANALYZER_H

#include <iostream>
#include <utility>
#include <list>
#include <map>
#include "CheckingResult.h"

using namespace std;

class SyntaxAnalyzer {
private:
    enum State { START, ERROR, FINAL, A, B, C, D, E, F, G };
    enum Type { DOUBLE, TABLE, STRING, DERIVATIVE };

    const list<string> RESERVED_IDENTIFIERS = { "dx", "dy", "dz", "x", "y", "z", "x0", "y0", "z0", "t", "t0", "T" };
    const list<string> MATH_FUNCTIONS = { "sin", "cos", "tan", "asin", "acos", "atan", "log", "log10", "sqrt", "cbrt" };
    const list<string> METHODS = { "eulers", "rungekutta", "print", "println" };
    const list<string> MATH_OPERATIONS = { "+", "-", "*", "/", "^" };
    const list<string> MATH_CONSTS = { "e" };
    const string ASSIGNMENT_OPERATOR = "=";
    const string COMMENT_CHAR = "#";

    //list<string> identifiers;
    map<string, Type> identifiers;
    list<string> lines;

public:

    SyntaxAnalyzer();

    CheckingResult isSign(const string &text, int startingPosition);

    CheckingResult isAssignment(const string &text, int startingPosition);

    CheckingResult isIdentifier(const string &text, int startingPosition);

    CheckingResult isExistingVariable(const string &text, int startingPosition, Type type);

    CheckingResult isNumericConstWithSign(const string &text, int startingPosition);

    CheckingResult isNumericConst(const string &text, int startingPosition);

    CheckingResult isMathFunction(const string &text, int startingPosition);

    CheckingResult isMethodName(const string &text, int startingPosition);

    CheckingResult isMathOperation(const string &text, int startingPosition);

    CheckingResult isMathConst(const string &text, int startingPosition);

    CheckingResult isOperand(const string &text, int startingPosition);

    CheckingResult isExpression(const string &text, int startingPosition);

    CheckingResult validateLine(const string &text, int startingPosition);
};


#endif //DYNAMIC_SYSTEMS_DSL_TRANSLATOR_SYNTAXANALYZER_H
