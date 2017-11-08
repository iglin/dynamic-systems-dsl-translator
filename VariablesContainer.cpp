//
// Created by root on 11/8/17.
//

#include "VariablesContainer.h"

VariablesContainer::VariablesContainer() = default;

VariablesContainer::VariablesContainer(const map<string, Type> &identifiers) : identifiers(
        identifiers) {}

const map<string, Type> &VariablesContainer::getIdentifiers() const {
    return identifiers;
}

void VariablesContainer::setIdentifiers(const map<string, Type> &identifiers) {
    VariablesContainer::identifiers = identifiers;
}

void VariablesContainer::addIdentifier(const string &name, const Type type) {
    identifiers.insert(pair<string, Type>(name, type));
}

void VariablesContainer::removeIdentifier(const string &name) {
    identifiers.erase(name);
}

bool VariablesContainer::containsIdentifier(const string &name, Type type) {
    for (const auto& id : identifiers) {
        if (id.first == name && id.second == type) return true;
    }
    return false;
}
