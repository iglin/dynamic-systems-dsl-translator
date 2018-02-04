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
#include "VariablesContainer.h"
#include "Type.h"

using namespace std;

class SyntaxAnalyzer {
public:
    struct Method {
        string name;
        list<Type> arguments;
        Type returnType = Type::VOID;

        Method(const string &name, const list<Type> &arguments, Type returnType);

        Method();
    };

private:
    enum State { START, ERROR, FINAL, A, B, C, D, E, F, G };

    const list<string> RESERVED_IDENTIFIERS = { "dx", "dy", "dz", "x", "y", "z", "x0", "y0", "z0", "t", "t0", "T" };
    const list<string> MATH_FUNCTIONS = { "sin", "cos", "tan", "asin", "acos", "atan", "log", "log10", "sqrt", "cbrt" };
    const list<string> METHOD_NAMES = { "eulers", "rungekutta", "print", "println" };
    const list<string> MATH_OPERATIONS = { "+", "-", "*", "/", "^" };
    const list<string> MATH_CONSTS = { "e" };

    list<Method> methods;

    VariablesContainer identifiers;

public:
    static const char ASSIGNMENT_OPERATOR = '=';
    static const char COMMENT_CHAR = '#';

    SyntaxAnalyzer();

    VariablesContainer &getIdentifiers();

    void setIdentifiers(const VariablesContainer &identifiers);

    CheckingResult isSign(const string &text, int startingPosition);

    CheckingResult isAssignment(const string &text, int startingPosition);

    CheckingResult isIdentifier(const string &text, int startingPosition);

    CheckingResult isExistingVariable(const string &text, int startingPosition, Type type);

    CheckingResult isNumericConstWithSign(const string &text, int startingPosition);

    CheckingResult isNumericConst(const string &text, int startingPosition);

    CheckingResult isMathFunction(const string &text, int startingPosition);

    CheckingResult isMethodName(const string &text, int startingPosition);

    CheckingResult isMethodReturningType(const string &text, int startingPosition, Type returnType);

    CheckingResult isMethodCall(const string &text, int startingPosition, const Method &method);

    CheckingResult isMathOperation(const string &text, int startingPosition);

    CheckingResult isMathConst(const string &text, int startingPosition);

    CheckingResult isOperand(const string &text, int startingPosition);

    CheckingResult isExpression(const string &text, int startingPosition);

    CheckingResult isStringExpression(const string &text, int startingPosition);

    CheckingResult isFirstDerivativeX(const string &text, int startingPosition);

    CheckingResult isFirstDerivativeY(const string &text, int startingPosition);

    CheckingResult isFirstDerivativeZ(const string &text, int startingPosition);

    CheckingResult isNumIntegrationCall(const string &text, int startingPosition);

    /*
     * TODO: Support overrided methods
     * Recognize method by name in the specified code line @text
     * Recognizing of overrided methods is not supported!
     *
     * Returns NULL if method is not recognized
     */
    Method recognizeMethod(const string &text);

};


#endif //DYNAMIC_SYSTEMS_DSL_TRANSLATOR_SYNTAXANALYZER_H
