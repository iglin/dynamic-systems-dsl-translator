//
// Created by root on 11/8/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TRANSLATOR_METHOD_H
#define DYNAMIC_SYSTEMS_DSL_TRANSLATOR_METHOD_H

#include <iostream>
#include "SyntaxAnalyzer.h"

using namespace std;

class Method {
private:
    string name;
    list<SyntaxAnalyzer::Type> arguments;
    SyntaxAnalyzer::Type returnType = SyntaxAnalyzer::VOID;

public:
    Method();

    explicit Method(const string &name);

    Method(const string &name, const list<SyntaxAnalyzer::Type> &arguments, SyntaxAnalyzer::Type returnType);

    const string &getName() const;

    void setName(const string &name);

    const list<SyntaxAnalyzer::Type> &getArguments() const;

    void setArguments(const list<SyntaxAnalyzer::Type> &arguments);

    SyntaxAnalyzer::Type getReturnType() const;

    void setReturnType(SyntaxAnalyzer::Type returnType);
};

#endif //DYNAMIC_SYSTEMS_DSL_TRANSLATOR_METHOD_H
