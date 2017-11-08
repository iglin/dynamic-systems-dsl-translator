//
// Created by root on 11/7/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TRANSLATOR_TRANSLATOR_H
#define DYNAMIC_SYSTEMS_DSL_TRANSLATOR_TRANSLATOR_H

#include <iostream>
#include "SyntaxAnalyzer.h"

using namespace std;

class Translator {
private:
    list<string> initLines;
    list<string> mainLines;
public:
    void translateToCpp(const string &sourceFileName);

    string translatePows(const string &text, SyntaxAnalyzer &syntaxAnalyzer);

    CheckingResult translateLine(const string &line, SyntaxAnalyzer &syntaxAnalyzer);
};


#endif //DYNAMIC_SYSTEMS_DSL_TRANSLATOR_TRANSLATOR_H
