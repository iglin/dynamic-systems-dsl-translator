//
// Created by root on 11/7/17.
//

#include <fstream>
#include "Translator.h"
#include "StringUtils.h"

void Translator::translateToCpp(const string &sourceFileName) {
    auto syntaxAnalyzer = new SyntaxAnalyzer();
    ifstream file(sourceFileName);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            //cout << line << endl;
            translateLine(line, *syntaxAnalyzer);
        }
        file.close();
    } else {
        string errorMessage;
        errorMessage = "Could not read source file " + sourceFileName;
        throw runtime_error(errorMessage);
    }
}

string Translator::translatePows(const string &text, SyntaxAnalyzer &syntaxAnalyzer) {
    string result = text;
    int index;
    while ((index = StringUtils::indexOf(result, "^")) != -1) {
        int openedParentheses = 0;
        string leftOperand, rightOperand;
        int i, j;

        for (i = index - 1; i >= 0; i--) {
            if (openedParentheses == 0 && syntaxAnalyzer.isMathOperation(string(1, result.at(i)), i).isSuccessful()) break;
            if (result.at(i) == '(') openedParentheses++;
            else if (result.at(i) == ')') openedParentheses--;
            leftOperand = string(1, result.at(i)) + leftOperand;
        }
        i++;

        for (j = index + 1; j < result.length(); j++) {
            if (openedParentheses == 0 && syntaxAnalyzer.isMathOperation(string(1, result.at(j)), j).isSuccessful()) break;
            if (result.at(j) == '(') openedParentheses++;
            else if (result.at(j) == ')') openedParentheses--;
            rightOperand += string(1, result.at(j));
        }

        result = result.substr(0, i) + " pow(" + leftOperand + ", " + rightOperand + ") " + result.substr(j, result.length() - j);
    }
    return result;
}

CheckingResult Translator::translateLine(const string &line, SyntaxAnalyzer &syntaxAnalyzer) {
    if (StringUtils::trim_copy(line).empty()) return CheckingResult(true);

    string comment;
    string lineWithoutComment;
    unsigned int i = 0;
    while (line.at(i) == ' ') i++;
    int firstNonWhitespaceIdx = i;
    if (line.at(i) == SyntaxAnalyzer::COMMENT_CHAR) {
        comment = StringUtils::replaceFirst(line, "#", "//");
        mainLines.push_back(comment);
        return CheckingResult(true);
    }

    int commentStartIdx = StringUtils::indexOf(line, "#");
    if (commentStartIdx != -1) {
        comment = line.substr(commentStartIdx + 1, line.length() - (commentStartIdx + 1));
        comment = "//" + comment;
        lineWithoutComment = line.substr(0, commentStartIdx);
    } else {
        lineWithoutComment = line;
    }

    cout << "Comment: " << comment << endl;
    cout << "Line: " << lineWithoutComment << endl;

    string substring;
    bool assignment = false;
    for (i; i < lineWithoutComment.length(); i++) {
        if ((assignment = lineWithoutComment.at(i) == SyntaxAnalyzer::ASSIGNMENT_OPERATOR) || lineWithoutComment.at(i) == '(') break;
        substring += string(1, lineWithoutComment.at(i));
    }
    string restString = lineWithoutComment.substr(i + 1, lineWithoutComment.length() - (i + 1));

    CheckingResult check;
    if (assignment) {
        string trimmedId = StringUtils::trim_copy(substring);
        if (trimmedId == "dx") {
            check = syntaxAnalyzer.isFirstDerivativeX(restString, i + 1);
            if (!check.isSuccessful()) return check;

            syntaxAnalyzer.getIdentifiers().addIdentifier(trimmedId, DERIVATIVE);
            string outputString = "#define " + trimmedId + " (" + restString + ") " + comment;
            initLines.push_back(outputString);
            return CheckingResult(true);
        }

        check = syntaxAnalyzer.isIdentifier(trimmedId, firstNonWhitespaceIdx);
        if (!check.isSuccessful()) return check;

        lineWithoutComment = lineWithoutComment.substr(i + 1, lineWithoutComment.length() - (i + 1));

        if (isExpression(lineWithoutComment, i + 1).isSuccessful()) {
            if (!isExistingVariable(substring, 0, DOUBLE).isSuccessful()) {
                identifiers.insert(pair<string, Type>(substring, DOUBLE));
                lineWithoutComment = "double " + substring + " = " + lineWithoutComment + comment;
            } else {
                lineWithoutComment = substring + " = " + lineWithoutComment + comment;
            }
            mainLines.push_back(lineWithoutComment);
            return CheckingResult(true);
        } else {
            if (lineWithoutComment.find("eulers") != std::string::npos) {
                if (lineWithoutComment.find("dx") != std::string::npos) {
                    if (!isExistingVariable(substring, 0, TABLE).isSuccessful()) {
                        identifiers.insert(pair<string, Type>(substring, TABLE));
                        lineWithoutComment = "double " + substring + " = " + lineWithoutComment + comment;
                    } else {
                        lineWithoutComment = substring + " = " + lineWithoutComment + comment;
                    }
                }
            }
        }
    } else {

    }
    return CheckingResult();
}
