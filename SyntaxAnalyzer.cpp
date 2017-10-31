//
// Created by root on 10/31/17.
//

#include "SyntaxAnalyzer.h"

CheckingResult SyntaxAnalyzer::isSign(const string &text, int startingPosition) {
    CheckingResult result;
    result = CheckingResult(text == "+" || text == "-");
    if (!result.isSuccessful()) {
        result.message = "Expected sign (+ or -)";
        result.position = startingPosition;
    }
    return result;
}

SyntaxAnalyzer::CheckingResult SyntaxAnalyzer::isAssignment(const string &text, int startingPosition) {
    CheckingResult result;
    result.successful = text == "=";
    if (!result.successful) {
        result.message = "Expected assignment operator \"=\"";
        result.position = startingPosition;
    }
    return result;
}

/*
 * START - '_ a..z A..Z' -> A - '_ a..z A..Z 0..9' -> A(r)
 *                            |
 *                            - $ -> FINAL
 * */
CheckingResult SyntaxAnalyzer::isIdentifier(const string &text, int startingPosition) {
    CheckingResult result;
    unsigned int i = 0;
    State state = State::START;
    while (i < text.length()) {
        if (state == START) {
            if (text.at(i) == '_' || isalpha(text.at(i))) state = A;
            else return CheckingResult(false, startingPosition, "Identifier must start with a letter or \"_\"");
        } else {
            if (text.at(i) != '_' && !isalnum(text.at(i)))
                return CheckingResult(false, startingPosition + i, "Identifier must contain only letter, numbers or \"_\"");
        }
        i++;
    }
    return CheckingResult(true);
}
