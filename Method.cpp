//
// Created by root on 11/8/17.
//

#include "Method.h"

Method::Method() = default;

Method::Method(const string &name) : name(name) {}

Method::Method(const string &name, const list<SyntaxAnalyzer::Type> &arguments, SyntaxAnalyzer::Type returnType) : name(
        name), arguments(arguments), returnType(returnType) {}

const string &Method::getName() const {
    return name;
}

void Method::setName(const string &name) {
    Method::name = name;
}

const list<SyntaxAnalyzer::Type> &Method::getArguments() const {
    return arguments;
}

void Method::setArguments(const list<SyntaxAnalyzer::Type> &arguments) {
    Method::arguments = arguments;
}

SyntaxAnalyzer::Type Method::getReturnType() const {
    return returnType;
}

void Method::setReturnType(SyntaxAnalyzer::Type returnType) {
    Method::returnType = returnType;
}
