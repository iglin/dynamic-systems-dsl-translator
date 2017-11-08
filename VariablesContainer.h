//
// Created by root on 11/8/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TRANSLATOR_VARIABLESCONTAINER_H
#define DYNAMIC_SYSTEMS_DSL_TRANSLATOR_VARIABLESCONTAINER_H

#include <iostream>
#include <map>
#include "Type.h"

using namespace std;

class VariablesContainer {
private:
    map<string, Type> identifiers;
public:
    VariablesContainer();

    explicit VariablesContainer(const map<string, Type> &identifiers);

    const map<string, Type> &getIdentifiers() const;

    void setIdentifiers(const map<string, Type> &identifiers);

    void addIdentifier(const string &name, Type type);

    void removeIdentifier(const string &name);

    bool containsIdentifier(const string &name, Type type);
};


#endif //DYNAMIC_SYSTEMS_DSL_TRANSLATOR_VARIABLESCONTAINER_H
