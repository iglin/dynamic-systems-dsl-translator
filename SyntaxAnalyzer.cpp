//
// Created by root on 10/31/17.
//

#include "SyntaxAnalyzer.h"
#include "StringUtils.h"
#include <algorithm>

SyntaxAnalyzer::SyntaxAnalyzer() = default;

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
    if (find(RESERVED_IDENTIFIERS.begin(), RESERVED_IDENTIFIERS.end(), text) != RESERVED_IDENTIFIERS.end())
        return CheckingResult(false, startingPosition, "Identifier name is reserved");
    State state = State::START;
    for (unsigned int i = 0; i < text.length(); i++) {
        if (state == START) {
            if (text.at(i) == '_' || isalpha(text.at(i))) state = A;
            else return CheckingResult(false, startingPosition, "Identifier must start with a letter or \"_\"");
        } else {
            if (text.at(i) != '_' && !isalnum(text.at(i)))
                return CheckingResult(false, startingPosition + i, "Identifier must contain only letter, numbers or \"_\"");
        }
    }
    return CheckingResult(true);
}

CheckingResult SyntaxAnalyzer::isExistingVariable(const string &text, int startingPosition, Type type) {
    for (const auto& id : identifiers) {
        if (id.first == text && id.second == type) return CheckingResult(true);
    }
    return CheckingResult(false, startingPosition, "Identifier doesn't exist");
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
CheckingResult SyntaxAnalyzer::isNumericConstWithSign(const string &text, int startingPosition) {
    State state = START;
    for (unsigned int i = 0; i < text.length(); i++) {
        switch (state) {
            case START:
                if (isSign(string(1, text.at(i)), startingPosition).isSuccessful()) state = A;
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
    }
    if (state == C || state == D) return CheckingResult(true);
    return CheckingResult(false, startingPosition, "Invalid numeric constant");
}

/*
 * START - '.' -> A - '0..9 -> B - '0..9' -> B(r)
 *       |                       |
 *       |                       - $ -> FINAL
 *       |
 *       - '0..9' -> C - '0..9' -> C(r)
 *                     |
 *                     - '.' -> B
 *                     |
 *                     - $ -> FINAL
 */
CheckingResult SyntaxAnalyzer::isNumericConst(const string &text, int startingPosition) {
    State state = START;
    for (unsigned int i = 0; i < text.length(); i++) {
        switch (state) {
            case START:
                if (text.at(i) == '.') state = A;
                else if (isdigit(text.at(i))) state = C;
                else return CheckingResult(false, startingPosition,
                                           R"(Numeric constant must start with "." or digit)");
                break;
            case A:
                if (isdigit(text.at(i))) state = B;
                else return CheckingResult(false, startingPosition + i,
                                           R"(Numeric constant must contain at least one digit)");
                break;
            case B:
                if (isdigit(text.at(i))) continue;
                else return CheckingResult(false, startingPosition + i, "Invalid symbol in numeric constant");
            case C:
                if (isdigit(text.at(i))) continue;
                if (text.at(i) == '.') state = B;
                else return CheckingResult(false, startingPosition + i, "Invalid symbol in numeric constant");
                break;
        }
    }
    if (state == C || state == B) return CheckingResult(true);
    return CheckingResult(false, startingPosition, "Invalid numeric constant");
}

CheckingResult SyntaxAnalyzer::isMathFunction(const string &text, int startingPosition) {
    if (find(MATH_FUNCTIONS.begin(), MATH_FUNCTIONS.end(), text) != MATH_FUNCTIONS.end()) return CheckingResult(true);
    return CheckingResult(false, startingPosition, "Not a math function");
}

CheckingResult SyntaxAnalyzer::isMethodName(const string &text, int startingPosition) {
    if (find(METHODS.begin(), METHODS.end(), text) != METHODS.end()) return CheckingResult(true);
    return CheckingResult(false, startingPosition, "There is no such method");
}

CheckingResult SyntaxAnalyzer::isMathOperation(const string &text, int startingPosition) {
    if (find(MATH_OPERATIONS.begin(), MATH_OPERATIONS.end(), text) != MATH_OPERATIONS.end()) return CheckingResult(true);
    return CheckingResult(false, startingPosition, "There is no such math operation");
}

CheckingResult SyntaxAnalyzer::isMathConst(const string &text, int startingPosition) {
    if (find(MATH_CONSTS.begin(), MATH_CONSTS.end(), text) != MATH_CONSTS.end()) return CheckingResult(true);
    return CheckingResult(false, startingPosition, "There is no such math constant");
}

/*
 * START - 'MATH_CONST NUM_VS_SIGN EX_DOUBLE' -> FINAL
 *       |
 *       - 'MATH_FUNC' -> A -> 'WS' -> A(r)
 *                          |
 *                          - '(' -> B - 'WS' -> B(r)
 *                                     |
 *                                     - 'EXPR OPERAND' -> C - 'WS' -> C(r)
 *                                                           |
 *                                                           - ')' -> D -> $ -> FINAL
 */
CheckingResult SyntaxAnalyzer::isOperand(const string &text, int startingPosition) {
    if (isMathConst(text, startingPosition).isSuccessful()
        || isNumericConst(text, startingPosition).isSuccessful()
        || isExistingVariable(text, startingPosition, DOUBLE).isSuccessful()) return CheckingResult(true);

    State state = START;
    unsigned int i = 0;
    string substring;
    while (i < text.length() && isalnum(text.at(i))) {
        substring += string(1, text.at(i));
        i++;
    }
    if (!isMathFunction(substring, startingPosition).isSuccessful())
        return CheckingResult(false, startingPosition, "Invalid operand");
    else state = A;
    while (i < text.length()) {
        switch (state) {
            case A:
                if (text.at(i) == ' ') break;
                if (text.at(i) == '(') state = B;
                else return CheckingResult(false, startingPosition + i, "Expected \"(\" after the math function name");
                break;
            case B: {
                if (text.at(i) == ' ') break;
                substring = "";
                int newPosition = startingPosition + i;
                while (i < text.length() && text.at(i) != ')') {
                    substring += string(1, text.at(i));
                    i++;
                }
                // TODO: isExpression() is enough?
                if (i == text.length() || !isOperand(StringUtils::rtrim_copy(substring), newPosition).isSuccessful()
                    && !isExpression(substring, newPosition).isSuccessful())
                    return CheckingResult(false, newPosition, "Invalid math function argument");

                if (text.at(i) == ' ') state = C;
                else if (text.at(i) == ')') state = D;
                break;
            }
            case C:
                if (text.at(i) == ' ') break;
                if (text.at(i) == ')') state = D;
                break;
            case D:
                return CheckingResult(false, startingPosition + i, "Unexpected symbol after the math function call");
        }
        i++;
    }
    if (state == D) return CheckingResult(true);
    else return CheckingResult(false, startingPosition, "Invalid operand");
}

/*
 * START - '(' -> A -> 'WS' -> A(r)
 *       |          |
 *       |          - 'EXPR' -> D - 'WS' -> D(r)
 *       |                        |
 *       |                        - ')' -> E - '$' -> FINAL
 *       |                                   |
 *       - 'OPERAND' -> E                    - 'WS' -> F -> 'WS' -> F(r)
 *       |                                   |           |
 *       - '+ -' -> C - 'WS' -> C(r)         |           - 'MATH_OP' -> B
 *                    |                      |
 *                    - '(' -> A             - 'MATH_OP' -> B - 'WS' -> B(r)
 *                    |                                       |
 *                    - 'OPERAND' -> E                        - 'OPERAND' -> E
 *                                                            |
 *                                                            - '(' -> A
 */
CheckingResult SyntaxAnalyzer::isExpression(const string &text, int startingPosition) {
    State state = START;
    for (unsigned int i = 0; i < text.length(); i++) {
        switch (state) {
            case START:
                if (text.at(i) == '(') state = A;
                else if (text.at(i) == '+' || text.at(i) == '-') state = C;
                else {
                    string substring;
                    while (i < text.length() && text.at(i) != ' '
                           && isMathOperation(string(1, text.at(1)), i).isSuccessful()) {
                        substring += string(1, text.at(i));
                        i++;
                    }
                    if (!isOperand(substring, startingPosition).isSuccessful())
                        return CheckingResult(false, startingPosition, "Invalid expression");
                    state = E;
                    i--;
                }
                break;
            case A:
                if (text.at(i) == ' ') continue;
                else {
                    int newPosition = startingPosition + i;
                    string substring;
                    while (i < text.length() && text.at(i) != ' ' && text.at(i) != ')') {
                        substring += string(1, text.at(i));
                        i++;
                    }
                    if (!isExpression(substring, newPosition).isSuccessful())
                        return CheckingResult(false, newPosition, "Invalid expression");
                    state = D;
                    i--;
                }
                break;
            case B:
                if (text.at(i) == ' ') continue;
                if (text.at(i) == '(') state = A;
                else {
                    string substring;
                    int newPosition = startingPosition + i;
                    while (i < text.length() && text.at(i) != ' '
                           && isMathOperation(string(1, text.at(1)), newPosition).isSuccessful()) {
                        substring += string(1, text.at(i));
                        i++;
                    }
                    if (!isOperand(substring, newPosition).isSuccessful())
                        return CheckingResult(false, newPosition, "Invalid expression");
                    state = E;
                    i--;
                }
                break;
        }
    }
}

/*
 * START - 'ID RES_ID' -> A - 'WS' -> A(r)
 *       |                  |
 *       |                  - 'ASGN'
 *       |
 *       - 'METHOD' -> B - 'WS' -> B(r)
 */
CheckingResult SyntaxAnalyzer::validateLine(const string &text, int startingPosition) {
    // TODO: Trim
    return CheckingResult();
}


