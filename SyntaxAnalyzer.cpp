//
// Created by root on 10/31/17.
//

#include "SyntaxAnalyzer.h"

CheckingResult SyntaxAnalyzer::isSign(const string &text, int startingPosition) {
    if (text == "+" || text == "-") return CheckingResult(true);
    return CheckingResult(false, startingPosition, "Expected sign (+ or -)");
}

CheckingResult SyntaxAnalyzer::isAssignment(const string &text, int startingPosition) {
    if (text == "=") return CheckingResult(true);
    return CheckingResult(false, startingPosition, "Expected assignment operator \"=\"");
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

/*
 * START - '+ -' -> A - '.' -> B - '0..9 -> C - '0..9' -> C(r)
 *       |            |                       |
 *       |            - 'WS' -> A(r)          - $ -> FINAL
 *       |            |
 *       |            - '0..9' -> D
 *       |
 *       - '.' -> B
 *       |
 *       - '0..9' -> D - '0..9' -> D(r)
 *                     |
 *                     - '.' -> C
 *                     |
 *                     - $ -> FINAL
 */
CheckingResult SyntaxAnalyzer::isNumericConst(const string &text, int startingPosition) {
    State state = START;
    for (unsigned int i = 0; i < text.length(); i++) {
        switch (state) {
            case START:
                if (isSign(to_string(text.at(i)), startingPosition).isSuccessful()) state = A;
                else if (text.at(i) == '.') state = B;
                else if (isdigit(text.at(i))) state = D;
                else return CheckingResult(false, startingPosition,
                                           R"(Numeric constant must start with "+", "-", "." or digit)");
                break;
            case A:
                if (text.at(i) == ' ') continue;
                if (text.at(i) == '.') state = B;
                else if (isdigit(text.at(i))) state = D;
                else return CheckingResult(false, startingPosition + i,
                                           R"(Numeric constant must contain only one or zero "." and at least one digit)");
                break;
            case B:
                if (isdigit(text.at(i))) state = C;
                else return CheckingResult(false, startingPosition + i,
                                           R"(Numeric constant must contain at least one digit)");
                break;
            case C:
                if (isdigit(text.at(i))) continue;
                else return CheckingResult(false, startingPosition + i, "Invalid symbol in numeric constant");
            case D:
                if (isdigit(text.at(i))) continue;
                if (text.at(i) == '.') state = C;
                else return CheckingResult(false, startingPosition + i, "Invalid symbol in numeric constant");
                break;
        }
        if (state == C || state == D) return CheckingResult(true);
        return CheckingResult(false, startingPosition, "Invalid numeric constant");
    }
    return CheckingResult();
}
