//
// Created by root on 10/31/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TRANSLATOR_SYNTAXANALYZER_H
#define DYNAMIC_SYSTEMS_DSL_TRANSLATOR_SYNTAXANALYZER_H

#include <iostream>
#include <utility>
#include "CheckingResult.h"

using namespace std;

class SyntaxAnalyzer {
private:
    enum State { START, ERROR, FINAL, A, B, C, D, E, F, G };

public:
    static CheckingResult isSign(const string &text, int startingPosition);

    static CheckingResult isAssignment(const string &text, int startingPosition);

    static CheckingResult isIdentifier(const string &text, int startingPosition);


};


#endif //DYNAMIC_SYSTEMS_DSL_TRANSLATOR_SYNTAXANALYZER_H
