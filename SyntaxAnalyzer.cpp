//
// Created by root on 10/31/17.
//

#include "SyntaxAnalyzer.h"

CheckingResult SyntaxAnalyzer::isSign(const string &text, int startingPosition) {
    return text == "+" || text == "-";
}

CheckingResult SyntaxAnalyzer::isIdentifier(const string &text, int startingPosition) {
    for (int i = 0; i < text.length(); i++) {
        if (text.at(i))
    }
    return false;
}
