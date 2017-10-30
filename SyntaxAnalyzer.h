//
// Created by root on 10/31/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TRANSLATOR_SYNTAXANALYZER_H
#define DYNAMIC_SYSTEMS_DSL_TRANSLATOR_SYNTAXANALYZER_H

#include <iostream>

using namespace std;

class SyntaxAnalyzer {
public:
    struct CheckingResult {
        bool result;
        int position;
        string message;
    };

    CheckingResult isSign(const string &text, int startingPosition);

    CheckingResult isIdentifier(const string &text, int startingPosition);


};


#endif //DYNAMIC_SYSTEMS_DSL_TRANSLATOR_SYNTAXANALYZER_H
