//
// Created by root on 11/7/17.
//

#include <fstream>
#include "Translator.h"

void Translator::translateToCpp(const string &sourceFileName) {
    SyntaxAnalyzer syntaxAnalyzer;
    ifstream file(sourceFileName);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            cout << line << endl;
            syntaxAnalyzer.translateLine(line);
        }
        file.close();
    } else {
        string errorMessage;
        errorMessage = "Could not read source file " + sourceFileName;
        throw runtime_error(errorMessage);
    }
}
