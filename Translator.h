//
// Created by root on 11/7/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TRANSLATOR_TRANSLATOR_H
#define DYNAMIC_SYSTEMS_DSL_TRANSLATOR_TRANSLATOR_H

#include <iostream>
#include "SyntaxAnalyzer.h"

using namespace std;

class Translator {
public:
    static void translateToCpp(const string &sourceFileName);
};


#endif //DYNAMIC_SYSTEMS_DSL_TRANSLATOR_TRANSLATOR_H
